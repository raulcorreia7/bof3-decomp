#!/usr/bin/env python3
"""Try every single small source edit on open drafts and report the ones that match or come closer.

    tools/sweep_edits.py [--worklist FILE | REF...] [--jobs N] [--out FILE] [--pairs]

REF is TARGET@0xADDRESS; `--worklist` reads `tools/worklist.py --jsonl` lines. For each draft the
body is tokenized and each edit class (CLASSES) proposes variants: one retyped local or parameter,
an increment or compound-assignment form, one cast, one swapped statement or declaration, one
swapped operand or comparison, one loop or if/else or ternary form, `break` for `return`, one local
split or two merged, one statement moved within its run of plain statements. Each variant is
compiled with `MATCH_SRC` into a private object and scored as `tools/match.sh --diff` scores it:
differing rows. `--classes a-type,j-move` limits the classes. The tree is never written. One JSON line per
variant that matches or has fewer rows than the draft goes to `--out`, with its class and diff;
a summary line per function (`"class": "summary"`) counts the variants tried and failed.
`--pairs` then tries pairs of a function's improving edits when none matched.

    tools/sweep_edits.py --worklist build/worklist.jsonl --jobs 20 --pairs
"""

from __future__ import annotations

import argparse
import difflib
import json
import os
import re
import subprocess
import sys
import tempfile
from concurrent.futures import ProcessPoolExecutor, as_completed
from itertools import combinations
from pathlib import Path

from bof3.core.paths import ROOT
from bof3.match import MatchResult
from check_markers import TOKEN
from try_variants import function_span

INTS = ("s8", "u8", "s16", "u16", "s32", "u32")
TYPES = set(INTS) | {"int", "short", "char", "long", "unsigned", "signed"}
KEYWORDS = {
    "if",
    "else",
    "for",
    "while",
    "do",
    "switch",
    "case",
    "default",
    "return",
    "break",
    "continue",
    "goto",
    "sizeof",
}
COMMUTATIVE = {"+", "*", "&", "|", "^", "==", "!="}
REVERSED = {"<": ">", ">": "<", "<=": ">=", ">=": "<="}
OPERATORS = (
    "<<=",
    ">>=",
    "+=",
    "-=",
    "*=",
    "/=",
    "%=",
    "&=",
    "|=",
    "^=",
    "<<",
    ">>",
    "->",
    "++",
    "--",
    "<=",
    ">=",
    "==",
    "!=",
    "&&",
    "||",
)
MACRO = re.compile(r"[A-Z][A-Z0-9_]+$")
CAP = 120  # variants per class per function


class Tok:
    __slots__ = ("text", "start", "end", "kind")

    def __init__(self, text: str, start: int, end: int, kind: str) -> None:
        self.text, self.start, self.end, self.kind = text, start, end, kind


def tokenize(text: str) -> list[Tok]:
    """Significant tokens with their spans; multi-character operators joined."""
    out: list[Tok] = []
    for m in TOKEN.finditer(text):
        kind = m.lastgroup
        if kind in ("space", "comment"):
            continue
        out.append(Tok(m.group(), m.start(), m.end(), kind))
    joined: list[Tok] = []
    i = 0
    while i < len(out):
        t = out[i]
        if t.kind == "punct":
            for op in OPERATORS:
                n = len(op)
                run = out[i : i + n]
                if (
                    len(run) == n
                    and all(r.kind == "punct" for r in run)
                    and "".join(r.text for r in run) == op
                    and all(run[k].end == run[k + 1].start for k in range(n - 1))
                ):
                    joined.append(Tok(op, t.start, run[-1].end, "punct"))
                    i += n
                    break
            else:
                joined.append(t)
                i += 1
        else:
            joined.append(t)
            i += 1
    return joined


def matching(toks: list[Tok], i: int) -> int:
    """Index of the bracket that closes toks[i]."""
    pairs = {"(": ")", "[": "]", "{": "}"}
    open_, close, depth = toks[i].text, pairs[toks[i].text], 0
    for j in range(i, len(toks)):
        if toks[j].text == open_:
            depth += 1
        elif toks[j].text == close:
            depth -= 1
            if depth == 0:
                return j
    return len(toks) - 1


Edit = tuple[tuple[int, int, str], ...]


def apply(text: str, edit: Edit) -> str:
    for start, end, new in sorted(edit, reverse=True):
        text = text[:start] + new + text[end:]
    return text


def disjoint(a: Edit, b: Edit) -> bool:
    return all(x[1] <= y[0] or y[1] <= x[0] for x in a for y in b)


class Function:
    """One definition's tokens and the facts the generators share."""

    def __init__(self, text: str) -> None:
        self.text = text
        self.toks = tokenize(text)
        t = self.toks
        self.body = next(i for i, x in enumerate(t) if x.text == "{")
        self.end = matching(t, self.body)
        self.paren = next(i for i, x in enumerate(t) if x.text == "(")
        self.name = t[self.paren - 1].text
        self.void = t[self.paren - 2].text == "void"
        self.close = matching(t, self.paren)
        self.statements = self._statements()
        self.decls = [s for s in self.statements if s[2] == "decl"]
        self.locals = {}  # name -> (type token index, declaration)
        for d in self.decls:
            for k in range(d[0], d[1]):
                if (
                    t[k].kind == "ident"
                    and t[k + 1].text in ("=", ";", ",", "[")
                    and (
                        t[k - 1].text in ("*", ",")
                        or k - 1 == d[0]
                        or t[k - 1].kind == "ident"
                    )
                ):
                    if k != d[0]:
                        self.locals[t[k].text] = (d[0], d)

    def _statements(self) -> list[tuple[int, int, str, int]]:
        """(first, last ';', kind, block depth) of every plain statement; kind decl or expr."""
        t, out, depth, i = self.toks, [], 0, self.body
        start = None
        while i <= self.end:
            x = t[i].text
            if x == "{":
                depth += 1
                start = i + 1
            elif x == "}":
                depth -= 1
                start = i + 1
            elif (
                x == "("
                and start is not None
                and t[start].text in ("if", "for", "while", "switch")
            ):
                i = matching(t, i)
                start = i + 1
            elif (
                x in ("else", "do")
                or (x in ("case", "default"))
                or (
                    t[i].kind == "ident"
                    and i + 1 <= self.end
                    and t[i + 1].text == ":"
                    and x not in KEYWORDS
                )
            ):
                if (
                    x in ("case", "default")
                    or t[i].kind == "ident"
                    and x not in ("else", "do")
                ):
                    while t[i].text != ":":
                        i += 1
                start = i + 1
            elif x == ";" and start is not None:
                first = t[start].text
                kind = None
                if first not in KEYWORDS and t[start].kind == "ident":
                    kind = "decl" if self._is_decl(start, i) else "expr"
                if kind:
                    out.append((start, i, kind, depth))
                start = i + 1
            i += 1
        return out

    def _is_decl(self, a: int, b: int) -> bool:
        t = self.toks
        k = a
        while k < b and (
            t[k].text in TYPES or t[k].text in ("const", "struct", "union", "enum")
        ):
            k += 1
        if k == a:
            k += 1  # a typedef name
        while k < b and t[k].text == "*":
            k += 1
        return (
            k < b
            and t[k].kind == "ident"
            and t[k + 1].text in ("=", ";", ",", "[")
            and (k > a and (t[k - 1].kind == "ident" or t[k - 1].text == "*"))
        )

    def span(self, i: int, j: int) -> str:
        return self.text[self.toks[i].start : self.toks[j].end]

    def uses(self, name: str) -> list[int]:
        return [i for i in range(self.body, self.end) if self.toks[i].text == name]

    def params(self) -> list[tuple[int, int]]:
        """(first, last) token index of each parameter declaration."""
        t, out, a = self.toks, [], self.paren + 1
        depth = 0
        for k in range(self.paren + 1, self.close + 1):
            if t[k].text in "([":
                depth += 1
            elif t[k].text in ")]" and k != self.close:
                depth -= 1
            elif (t[k].text == "," and depth == 0) or k == self.close:
                if k > a:
                    out.append((a, k - 1))
                a = k + 1
        return [p for p in out if self.span(*p) != "void"]


def expression_end(t: list[Tok], i: int, stops: set[str]) -> int:
    """Last index of the expression starting at i, ending before a stop at depth 0."""
    depth = 0
    for k in range(i, len(t)):
        x = t[k].text
        if x in "([{":
            depth += 1
        elif x in ")]}":
            if depth == 0:
                return k - 1
            depth -= 1
        elif depth == 0 and x in stops:
            return k - 1
    return len(t) - 1


def operand(t: list[Tok], i: int, forward: bool) -> tuple[int, int] | None:
    """A primary operand (name, number, member chain, call, index, parenthesis) at i."""
    if forward:
        k = i
        if t[k].text == "(":
            return (i, matching(t, k))
        if t[k].kind not in ("ident", "number"):
            return None
        while k + 1 < len(t):
            n = t[k + 1].text
            if n in ("(", "["):
                k = matching(t, k + 1)
            elif n in (".", "->") and t[k + 2].kind == "ident":
                k += 2
            else:
                break
        return (i, k)
    k = i
    while k >= 0:
        x = t[k].text
        if x in (")", "]"):
            depth = 0
            while k >= 0:
                if t[k].text in (")", "]"):
                    depth += 1
                elif t[k].text in ("(", "["):
                    depth -= 1
                    if depth == 0:
                        break
                k -= 1
            if k > 0 and t[k - 1].kind == "ident" and t[k].text in "([":
                k -= 1
                if t[k].text in KEYWORDS:
                    return None
        elif t[k].kind not in ("ident", "number"):
            return None
        if k >= 2 and t[k - 1].text in (".", "->"):
            k -= 2
            continue
        if (
            k >= 1
            and t[k - 1].text in ("&", "*", "-", "!", "~")
            and k >= 2
            and t[k - 2].text in ("(", ",", "=", "return")
        ):
            return None
        return (k, i)
    return None


# --- edit classes -------------------------------------------------------------------------


def g_retype(f: Function):
    t = f.toks
    for name, (ti, _) in f.locals.items():
        if t[ti].text in INTS:
            for new in INTS:
                if new != t[ti].text:
                    yield f"{name}: {new}", ((t[ti].start, t[ti].end, new),)
    params = f.params()
    for p in params:
        if t[p[0]].text in INTS and p[1] > p[0]:
            pname = t[p[1]].text
            for new in INTS:
                if new == t[p[0]].text:
                    continue
                yield f"param {pname}: {new}", ((t[p[0]].start, t[p[0]].end, new),)
                names = ", ".join(t[q[1]].text for q in params)
                decls = "".join(
                    f"    {new if q is p else f.span(q[0], q[1] - 1)} {t[q[1]].text};\n"
                    for q in params
                )
                yield (
                    f"param {pname}: {new} (old-style)",
                    (
                        (t[f.paren].end, t[f.close].start, names),
                        (t[f.close].end, t[f.body].start, "\n" + decls),
                    ),
                )


def g_increment(f: Function):
    t = f.toks
    for a, b, kind, _ in f.statements:
        if kind != "expr":
            continue
        s = [x.text for x in t[a : b + 1]]
        if len(s) == 4 and s[1] in ("+=", "-=") and s[2] == "1":
            yield "x op= 1 -> x op op", ((t[a].start, t[b].start, s[0] + s[1][0] * 2),)
        if len(s) == 3 and s[1] in ("++", "--"):
            yield "x++ -> x += 1", ((t[a].start, t[b].start, f"{s[0]} {s[1][0]}= 1"),)
            yield "x++ -> ++x", ((t[a].start, t[b].start, s[1] + s[0]),)
        if len(s) == 3 and s[0] in ("++", "--"):
            yield "++x -> x++", ((t[a].start, t[b].start, s[1] + s[0]),)
        if "=" in s:
            e = s.index("=")
            lhs = f.span(a, a + e - 1)
            n = a + e + 1
            stop = expression_end(
                t, n, {";", "+", "-", "*", "/", "&", "|", "^", "<<", ">>"}
            )
            if (
                stop < b - 1
                and f.span(n, stop) == lhs
                and t[stop + 1].text in ("+", "-", "*", "&", "|", "^", "<<", ">>", "/")
            ):
                op = t[stop + 1].text
                yield (
                    "a = a op b -> a op= b",
                    ((t[a + e].start, t[stop + 1].end, f"{op}="),),
                )
        for k in range(a, b):
            if (
                t[k].text in ("+=", "-=", "*=", "&=", "|=", "^=", "<<=", ">>=")
                and k > a
            ):
                lhs = f.span(a, k - 1)
                rhs = f.span(k + 1, b - 1)
                wrap = (
                    rhs
                    if len(t[k + 1 : b]) == 1
                    else f"({rhs})"
                    if t[k].text[:-1] in ("*", "<<", ">>", "&")
                    else rhs
                )
                yield (
                    "a op= b -> a = a op b",
                    ((t[k].start, t[b - 1].end, f"= {lhs} {t[k].text[:-1]} {wrap}"),),
                )
                break


def g_cast(f: Function):
    t = f.toks
    spots = []  # (first, last) of expressions to wrap
    for k in range(f.body, f.end):
        x = t[k].text
        if x in ("=", "return", "==", "!=", "<", ">", "<=", ">=") or (
            x in ("(", ",") and k > f.body and t[k - 1 if x == "(" else k].kind != "x"
        ):
            if x == "(" and not (
                t[k - 1].kind == "ident"
                and t[k - 1].text not in KEYWORDS
                and not MACRO.match(t[k - 1].text)
            ):
                continue
            if x == "," and not any(
                t[j].text == "(" for j in range(max(f.body, k - 30), k)
            ):
                continue
            stop = expression_end(
                t,
                k + 1,
                {";", ",", ")", "==", "!=", "<", ">", "<=", ">=", "&&", "||", "?", ":"},
            )
            if stop >= k + 1:
                spots.append((k + 1, stop))
            if x in ("==", "!=", "<", ">", "<=", ">="):
                left = operand(t, k - 1, False)
                if left:
                    spots.append(left)
    seen = set()
    for a, b in spots:
        if (
            (a, b) in seen
            or t[a].text == ";"
            or t[a].text in TYPES
            or t[a].text == "struct"
        ):
            continue
        seen.add((a, b))
        if t[a].text == "(" and t[a + 1].text in INTS and t[a + 2].text == ")":
            yield (
                f"drop ({t[a + 1].text}) on {f.span(a, b)[:40]}",
                ((t[a].start, t[a + 2].end, ""),),
            )
            continue
        inner = f.span(a, b)
        simple = a == b or operand(t, a, True) == (a, b)
        for c in INTS:
            yield (
                f"({c}) on {inner[:40]}",
                (
                    (
                        t[a].start,
                        t[b].end,
                        f"({c}){inner}" if simple else f"({c})({inner})",
                    ),
                ),
            )


def g_swap_statements(f: Function):
    t, st = f.toks, f.statements
    for x, y in zip(st, st[1:], strict=False):
        if x[2] == y[2] == "expr" and x[3] == y[3] and _adjacent(f, x, y):
            yield (
                f"swap {f.span(x[0], x[1])[:30]} / {f.span(y[0], y[1])[:30]}",
                (
                    (t[x[0]].start, t[x[1]].end, f.span(y[0], y[1])),
                    (t[y[0]].start, t[y[1]].end, f.span(x[0], x[1])),
                ),
            )
    exprs = [s for s in st if s[2] == "expr"]
    for d in f.decls:
        s = [z.text for z in t[d[0] : d[1] + 1]]
        if "=" not in s or "," in s or d[3] != 1:
            continue
        e = d[0] + s.index("=")
        name = t[e - 1].text
        use = next((u for u in f.uses(name) if u > d[1]), None)
        first = next((x for x in exprs if x[0] <= (use or 0) <= x[1]), None) or next(
            (x for x in exprs if x[0] > d[1]), None
        )
        if first is None:
            continue
        yield (
            f"split init of {name}",
            (
                (t[e - 1].end, t[d[1]].start, ""),
                (
                    t[first[0]].start,
                    t[first[0]].start,
                    f"{name} = {f.span(e + 1, d[1] - 1)};\n    ",
                ),
            ),
        )
    last = f.decls[-1] if f.decls else None
    if last:
        nxt = next((x for x in exprs if x[0] > last[1]), None)
        if nxt and t[nxt[0] + 1].text == "=" and t[nxt[0]].text in f.locals:
            name = t[nxt[0]].text
            d = f.locals[name][1]
            s = [z.text for z in t[d[0] : d[1] + 1]]
            if "=" not in s and "," not in s and d[3] == 1:
                yield (
                    f"join init of {name}",
                    (
                        (
                            t[d[1]].start,
                            t[d[1]].start,
                            " = " + f.span(nxt[0] + 2, nxt[1] - 1),
                        ),
                        (t[nxt[0]].start, t[nxt[1]].end, ""),
                    ),
                )


def _adjacent(f: Function, x, y) -> bool:
    """y follows x directly in the same block with nothing between and neither is a body."""
    t = f.toks
    if y[0] != x[1] + 1:
        return False
    for s in (x, y):
        prev = t[s[0] - 1].text
        if (
            prev in (")", "else", "do")
            or MACRO.match(t[s[0]].text)
            or any(z.text in ("{", "}") for z in t[s[0] : s[1]])
        ):
            return False
    return True


def g_move(f: Function):
    """Move one plain statement two or more places within a run of plain statements."""
    t, runs, run = f.toks, [], []
    for s in (s for s in f.statements if s[2] == "expr"):
        if run and _adjacent(f, run[-1], s) and run[-1][3] == s[3]:
            run.append(s)
        else:
            run = [s]
            runs.append(run)
    for run in (r for r in runs if len(r) >= 3):
        texts = [f.span(s[0], s[1]) for s in run]
        for i, j in (
            (i, j) for i in range(len(run)) for j in range(len(run)) if abs(i - j) >= 2
        ):
            order = texts[:i] + texts[i + 1 :]
            order.insert(j, texts[i])
            yield (
                f"move {texts[i][:40]} to {j - i:+d}",
                tuple(
                    (t[s[0]].start, t[s[1]].end, new)
                    for s, new in zip(run, order, strict=True)
                    if new is not None
                ),
            )


def g_swap_decls(f: Function):
    t, ds = f.toks, f.decls
    for x, y in zip(ds, ds[1:], strict=False):
        if y[0] == x[1] + 1 and x[3] == y[3]:
            yield (
                f"swap {f.span(x[0], x[1])[:30]} / {f.span(y[0], y[1])[:30]}",
                (
                    (t[x[0]].start, t[x[1]].end, f.span(y[0], y[1])),
                    (t[y[0]].start, t[y[1]].end, f.span(x[0], x[1])),
                ),
            )


def g_operands(f: Function):
    t = f.toks
    for k in range(f.body + 1, f.end):
        op = t[k].text
        if op not in COMMUTATIVE and op not in REVERSED:
            continue
        if (
            op in ("*", "&")
            and t[k - 1].text in ("(", ",", "=", "return")
            or t[k - 1].kind == "punct"
            and t[k - 1].text not in (")", "]")
        ):
            continue  # unary
        left, right = operand(t, k - 1, False), operand(t, k + 1, True)
        if not left or not right:
            continue
        if (
            left[0] > 0
            and t[left[0] - 1].text
            in ("*", "/", "%", "<<", ">>", ".", "->", "-", "~", "!")
            and op in COMMUTATIVE
        ):
            continue
        if (
            right[1] + 1 < len(t)
            and t[right[1] + 1].text in ("*", "/", "%", "<<", ">>", "[", "(")
            and op in COMMUTATIVE
        ):
            continue
        new = REVERSED.get(op, op)
        yield (
            f"{f.span(left[0], left[1])[:20]} {op} {f.span(right[0], right[1])[:20]}",
            (
                (
                    t[left[0]].start,
                    t[right[1]].end,
                    f"{f.span(*right)} {new} {f.span(*left)}",
                ),
            ),
        )


def g_control(f: Function):
    t = f.toks
    for k in range(f.body + 1, f.end):
        x = t[k].text
        if x == "if" and t[k - 1].text != "else":
            c = matching(t, k + 1)
            if t[c + 1].text != "{":
                continue
            b1 = matching(t, c + 1)
            if t[b1 + 1].text != "else" or t[b1 + 2].text != "{":
                continue
            b2 = matching(t, b1 + 2)
            yield (
                f"invert if ({f.span(k + 2, c - 1)[:30]})",
                (
                    (
                        t[k + 1].start,
                        t[b2].end,
                        f"(!({f.span(k + 2, c - 1)})) {f.span(b1 + 2, b2)} else {f.span(c + 1, b1)}",
                    ),
                ),
            )
        elif x == "for":
            c = matching(t, k + 1)
            semis = [j for j in range(k + 2, c) if t[j].text == ";"]
            if len(semis) != 2 or t[c + 1].text != "{":
                continue
            b = matching(t, c + 1)
            if any(t[j].text == "continue" for j in range(c, b)):
                continue
            init = f.span(k + 2, semis[0] - 1) if semis[0] > k + 2 else ""
            cond = (
                f.span(semis[0] + 1, semis[1] - 1) if semis[1] > semis[0] + 1 else "1"
            )
            step = f.span(semis[1] + 1, c - 1) if c > semis[1] + 1 else ""
            body = f.span(c + 2, b - 1) if b > c + 2 else ""
            pre = f"{init};\n    " if init else ""
            post = f"\n{step};\n" if step else "\n"
            yield (
                "for -> while",
                ((t[k].start, t[b].end, f"{pre}while ({cond}) {{\n{body}{post}}}"),),
            )
            yield (
                "for -> do-while",
                (
                    (
                        t[k].start,
                        t[b].end,
                        f"{pre}do {{\n{body}{post}}} while ({cond})" + ";",
                    ),
                ),
            )
        elif x == "while" and t[k - 1].text != "}":
            c = matching(t, k + 1)
            if t[c + 1].text != "{":
                continue
            b = matching(t, c + 1)
            if any(t[j].text == "continue" for j in range(c, b)):
                continue
            yield (
                "while -> do-while",
                (
                    (
                        t[k].start,
                        t[b].end,
                        f"do {f.span(c + 1, b)} while {f.span(k + 1, c)};",
                    ),
                ),
            )
            yield (
                "while -> for",
                ((t[k].start, t[k + 1].end, "for (;"), (t[c].start, t[c].end, ";)")),
            )
    for a, b, kind, _ in f.statements:
        s = [z.text for z in t[a : b + 1]]
        if kind == "expr" and "=" in s and "?" in s:
            e = a + s.index("=")
            q = next(j for j in range(e, b) if t[j].text == "?")
            colon = expression_end(t, q + 1, {":"}) + 1
            if t[colon].text != ":" or any(t[j].text == "?" for j in range(q + 1, b)):
                continue
            lhs = f.span(a, e - 1)
            cond = f.span(e + 1, q - 1)
            yield (
                "ternary -> if/else",
                (
                    (
                        t[a].start,
                        t[b].end,
                        f"if ({cond}) {{\n{lhs} = {f.span(q + 1, colon - 1)};\n}} else {{\n"
                        f"{lhs} = {f.span(colon + 1, b - 1)};\n}}",
                    ),
                ),
            )
    for k in range(f.body + 1, f.end):
        if t[k].text != "if" or t[k - 1].text == "else":
            continue
        c = matching(t, k + 1)
        arms = []
        j = c + 1
        for _ in range(2):
            if t[j].text == "{":
                close = matching(t, j)
                inner = (j + 1, close - 1)
            else:
                close = expression_end(t, j, {";"}) + 1
                inner = (j, close)
            arms.append((inner, close))
            j = close + 1
            if _ == 0:
                if t[j].text != "else":
                    break
                j += 1
        if len(arms) != 2:
            continue
        parts = []
        for (a, b), _ in arms:
            s = [z.text for z in t[a : b + 1]]
            if s.count(";") != 1 or s[-1] != ";" or "=" not in s or s[0] in KEYWORDS:
                break
            e = a + s.index("=")
            parts.append((f.span(a, e - 1), f.span(e + 1, b - 1)))
        if len(parts) == 2 and parts[0][0] == parts[1][0]:
            yield (
                "if/else -> ternary",
                (
                    (
                        t[k].start,
                        t[arms[1][1]].end,
                        f"{parts[0][0]} = {f.span(k + 2, c - 1)} ? {parts[0][1]} : {parts[1][1]};",
                    ),
                ),
            )


def g_return(f: Function):
    if not f.void:
        return
    t = f.toks
    for k in range(f.body + 1, f.end):
        if t[k].text == "switch":
            c = matching(t, k + 1)
            if t[c + 1].text != "{":
                continue
            b = matching(t, c + 1)
            if t[b + 1].text != "}" or b + 1 != f.end:
                continue
            for j in range(c + 2, b):
                if t[j].text in ("for", "while", "do", "switch"):
                    break
                if t[j].text == "return" and t[j + 1].text == ";":
                    yield "return -> break", ((t[j].start, t[j].end, "break"),)
                elif t[j].text == "break" and t[j + 1].text == ";":
                    yield "break -> return", ((t[j].start, t[j].end, "return"),)


def g_locals(f: Function):
    t = f.toks
    names = list(f.locals)
    for x, y in combinations(names, 2):
        dx, dy = f.locals[x], f.locals[y]
        tx, ty = f.span(dx[1][0], dx[0]), f.span(dy[1][0], dy[0])
        if (
            tx != ty
            or any("=" == z.text for z in t[dy[1][0] : dy[1][1]])
            or any(z.text == "," for z in t[dy[1][0] : dy[1][1]])
            or any(t[u - 1].text == "&" for u in f.uses(y))
        ):
            continue
        d = dy[1]
        edit = [(t[d[0]].start, t[d[1]].end, "")]
        edit += [(t[u].start, t[u].end, x) for u in f.uses(y) if u > d[1]]
        yield f"merge {y} into {x}", tuple(edit)
    stmts = [s for s in f.statements if s[2] == "expr" and s[3] == 1]
    for x in names:
        d = f.locals[x][1]
        if any(z.text == "," for z in t[d[0] : d[1]]) or any(
            t[u - 1].text == "&" for u in f.uses(x)
        ):
            continue
        assigns = [s for s in stmts if t[s[0]].text == x and t[s[0] + 1].text == "="]
        for s in assigns[1:]:
            new = x + "2"
            later = [u for u in f.uses(x) if u >= s[0]]
            if any(u in range(s[0] + 2, s[1]) for u in later):
                continue
            decl = f.span(d[0], f.locals[x][0]) + " " + new + ";\n    "
            edit = [(t[d[0]].start, t[d[0]].start, decl)]
            edit += [(t[u].start, t[u].end, new) for u in later]
            yield f"split {x} at {f.span(s[0], s[1])[:30]}", tuple(edit)


CLASSES = {
    "a-type": g_retype,
    "b-increment": g_increment,
    "c-cast": g_cast,
    "d-statement": g_swap_statements,
    "e-declaration": g_swap_decls,
    "f-operand": g_operands,
    "g-control": g_control,
    "h-return": g_return,
    "i-locals": g_locals,
    "j-move": g_move,
}


def variants(text: str, classes=None):
    """(class, label, edit) for every single edit the classes propose on one definition."""
    f = Function(text)
    for cls, gen in CLASSES.items():
        if classes and cls not in classes:
            continue
        seen = set()
        try:
            for label, edit in gen(f):
                if edit in seen:
                    continue
                seen.add(edit)
                if len(seen) > CAP:
                    break
                yield cls, label, edit
        except (IndexError, KeyError, RuntimeError, StopIteration, ValueError):
            continue


# --- measuring ----------------------------------------------------------------------------


def measure(ref: str, scratch: Path) -> int | None:
    """Differing rows of `match.sh --diff` on the scratch source: 0 match, None no compile."""
    env = {**os.environ, "MATCH_SRC": str(scratch)}
    run = subprocess.run(
        ["sh", "tools/match.sh", "--diff", ref],
        cwd=ROOT,
        env=env,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
        check=False,
    )
    result = MatchResult(run.returncode, run.stdout)
    if result.matched:
        return 0
    return len(result.differing) or None


def find_source(name: str) -> Path | None:
    pattern = re.compile(rf"^NON_MATCHING[^(\n]*[ *]{re.escape(name)}\(", re.M)
    for path in sorted((ROOT / "src").rglob("*.c")):
        text = path.read_text(errors="replace")
        if name in text and pattern.search(text):
            return path
    return None


def symbol_name(ref: str) -> str | None:
    target, addr = ref.split("@")
    link = ROOT / "build/symbols" / (target.replace("/", "+") + ".link")
    want = int(addr, 16)
    for line in link.read_text().splitlines():
        parts = line.split()
        if len(parts) == 2 and parts[1].startswith("0x") and int(parts[1], 16) == want:
            return parts[0]
    return f"func_{want:08X}"


def sweep(
    ref: str,
    name: str,
    source: Path,
    pairs: bool,
    judge=measure,
    workdir=None,
    classes=None,
):
    """Score every variant of one draft on private copies; return the result records."""
    base = source.read_text()
    start, end = function_span(base, name)
    text = base[start:end]
    records = []
    with tempfile.TemporaryDirectory(dir=workdir) as tmp:
        scratch = Path(tmp) / source.name

        def score(edit: Edit) -> int | None:
            scratch.write_text(base[:start] + apply(text, edit) + base[end:])
            return judge(ref, scratch)

        base_rows = score(())
        if base_rows is None or base_rows == 0:
            return [
                {
                    "ref": ref,
                    "class": "summary",
                    "base": base_rows,
                    "tried": 0,
                    "failed": 0,
                }
            ]
        tried = failed = 0
        better = []
        for cls, label, edit in variants(text, classes):
            rows = score(edit)
            tried += 1
            if rows is None:
                failed += 1
                continue
            if rows < base_rows:
                better.append((rows, cls, label, edit))
                records.append(_record(ref, base_rows, cls, label, text, edit, rows))
        if pairs and better and not any(b[0] == 0 for b in better):
            better.sort(key=lambda b: b[0])
            for x, y in combinations(better[:8], 2):
                if not disjoint(x[3], y[3]):
                    continue
                edit = x[3] + y[3]
                rows = score(edit)
                tried += 1
                if rows is None:
                    failed += 1
                elif rows < min(x[0], y[0]):
                    records.append(
                        _record(
                            ref,
                            base_rows,
                            f"{x[1]}+{y[1]}",
                            f"{x[2]} + {y[2]}",
                            text,
                            edit,
                            rows,
                        )
                    )
        records.append(
            {
                "ref": ref,
                "class": "summary",
                "base": base_rows,
                "tried": tried,
                "failed": failed,
                "source": str(source.relative_to(ROOT)),
            }
        )
    return records


def _record(ref, base_rows, cls, label, text, edit, rows):
    diff = "".join(
        difflib.unified_diff(
            text.splitlines(True), apply(text, edit).splitlines(True), n=1
        )
    )
    return {
        "ref": ref,
        "base": base_rows,
        "class": cls,
        "edit": label,
        "diff": diff,
        "rows": rows,
        "match": rows == 0,
    }


def _job(ref: str, name: str | None, pairs: bool, classes=None):
    name = name or symbol_name(ref)
    source = find_source(name) if name else None
    if source is None:
        return [{"ref": ref, "class": "summary", "error": f"no draft for {name}"}]
    try:
        return sweep(ref, name, source, pairs, classes=classes)
    except Exception as error:  # one bad draft must not stop the sweep
        return [{"ref": ref, "class": "summary", "error": repr(error)[:200]}]


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("refs", nargs="*", help="TARGET@0xADDRESS")
    parser.add_argument("--worklist", help="tools/worklist.py --jsonl output")
    parser.add_argument("--jobs", type=int, default=4)
    parser.add_argument(
        "--out", default="-", help="JSON lines file (appended), - for stdout"
    )
    parser.add_argument(
        "--pairs", action="store_true", help="also try pairs of improving edits"
    )
    parser.add_argument(
        "--classes", type=lambda v: v.split(","), help="comma list of CLASSES keys"
    )
    args = parser.parse_args()
    rows = [(r, None) for r in args.refs]
    if args.worklist:
        for line in Path(args.worklist).read_text().splitlines():
            item = json.loads(line)
            rows.append((item["ref"], item.get("name")))
    with (
        open(
            args.out if args.out != "-" else os.devnull, "a", encoding="utf-8"
        ) as sink,
        ProcessPoolExecutor(args.jobs) as pool,
    ):
        out = sys.stdout if args.out == "-" else sink
        futures = {
            pool.submit(_job, ref, name, args.pairs, args.classes): ref
            for ref, name in rows
        }
        for done in as_completed(futures):
            for record in done.result():
                out.write(json.dumps(record) + "\n")
            out.flush()
            summary = done.result()[-1]
            print(
                futures[done],
                {k: v for k, v in summary.items() if k != "ref"},
                file=sys.stderr,
                flush=True,
            )
    return 0


if __name__ == "__main__":
    sys.exit(main())
