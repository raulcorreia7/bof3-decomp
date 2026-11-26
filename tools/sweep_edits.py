#!/usr/bin/env python3
"""Try every single small source edit on open drafts and report the ones that match or come closer.

    tools/sweep_edits.py [--worklist FILE | REF...] [--jobs N] [--out FILE] [--pairs | --climb STEPS]

REF is TARGET@0xADDRESS; `--worklist` reads `tools/worklist.py --jsonl` lines. For each draft the
body is tokenized and each edit class (CLASSES) proposes variants: one retyped local or parameter,
an increment or compound-assignment form, one cast, one swapped statement or declaration, one
swapped operand or comparison, one loop or if/else or ternary form, `break` for `return`, one local
split or two merged, one statement moved within its run of plain statements, a member store moved
beside a store to the same record, every width combination of the integer parameters as an
old-style definition, a call argument passed straight or through a local, a value set in both arms
or once before the `if`, a shared tail hoisted after an if/else or switch or copied into each arm
or case, a local stored once with a constant or copy in its declaration, at the top of its block
or just above its first use, one local reused for a second such value, an argument group
`&X[0], &X[1]` or `&r.a, &r.b` through one pointer local and back, a separate local per loop that
sets it first, `c ? M : 0` for `-(c) & M`. Each variant is compiled with `MATCH_SRC` into a private object and scored on the
`tools/match.sh --diff` listing: the two instruction streams are aligned on their opcodes by a
longest common subsequence (branch targets as labels, call targets by name), and the score is the
instructions missing plus extra plus the aligned ones whose operands differ; 0 is a byte match.
`--classes a-type,j-move` limits the classes. The tree is never written. One JSON line per variant
that matches or scores lower than the draft goes to `--out`, with its class and diff; a summary
line per function (`"class": "summary"`) counts the variants tried and failed and lists the
`needs_type` sites (a global read as `G[i * N + k]` or `*(... G + off)`, which a typed table would
spell `G[i][k]`). `--pairs` then tries pairs of a function's improving edits when none matched.
`--climb STEPS` instead applies the best improving edit, sweeps the new text again, and repeats
until no edit improves or the row matches; one `"class": "climb"` line per function holds the path
of edits with each step's score. Only the climb tries class r-header: an s8/u8/s16/u16 global or
member of the image's own header, kept only while every other MATCH function that names it still
matches. No statement moves across one that stores what it reads or reads what it stores, and
edits that read a local before it is set are not generated; a merge of two locals whose names
differ, or a store moved across a call, carries `[needs-review]`.

    tools/sweep_edits.py --worklist build/worklist.jsonl --jobs 20 --pairs
    tools/sweep_edits.py --worklist build/worklist.jsonl --jobs 20 --climb 12
"""

from __future__ import annotations

import argparse
import difflib
import json
import os
import re
import resource
import subprocess
import sys
import tempfile
from concurrent.futures import ProcessPoolExecutor, as_completed
from itertools import combinations, product
from pathlib import Path

from bof3.core.paths import ROOT
from bof3.match import MatchResult, side_by_side
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
        self.old_style = self.body > self.close + 1
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
        """(first, last) token index of each parameter declaration, old-style ones included."""
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
        out = [p for p in out if self.span(*p) != "void"]
        if self.old_style:
            heads = {}
            a = self.close + 1
            for k in range(self.close + 1, self.body):
                if t[k].text == ";":
                    heads[t[k - 1].text] = (a, k - 1)
                    a = k + 1
            out = [heads.get(t[p[0]].text, p) for p in out]
        return out


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
                if f.old_style:
                    continue
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


def g_params(f: Function):
    """Every width combination of the integer parameters, as an old-style definition."""
    t, params = f.toks, f.params()
    ints = [p for p in params if t[p[0]].text in INTS and p[1] == p[0] + 1]
    if not ints:
        return
    names = ", ".join(t[q[1]].text for q in params)
    for widths in product(("s32", "u8", "s16", "u16"), repeat=len(ints)):
        chosen = dict(zip(ints, widths, strict=True))
        if all(chosen[p] == t[p[0]].text for p in ints):
            continue
        decls = "".join(
            f"    {chosen.get(q) or f.span(q[0], q[1] - 1)} {t[q[1]].text};\n"
            for q in params
        )
        label = ", ".join(f"{t[p[1]].text}: {w}" for p, w in chosen.items())
        if f.old_style:
            yield (
                f"old-style {label}",
                tuple((t[p[0]].start, t[p[0]].end, w) for p, w in chosen.items()),
            )
            continue
        yield (
            f"old-style {label}",
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
        if (
            x[2] == y[2] == "expr"
            and x[3] == y[3]
            and _adjacent(f, x, y)
            and not _depends(f, x, y)
        ):
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
    t = f.toks
    for run in (r for r in _runs(f) if len(r) >= 3):
        texts = [f.span(s[0], s[1]) for s in run]
        for i, j in (
            (i, j) for i in range(len(run)) for j in range(len(run)) if abs(i - j) >= 2
        ):
            crossed = range(j, i) if j < i else range(i + 1, j + 1)
            if any(_depends(f, run[i], run[k]) for k in crossed):
                continue
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


def _runs(f: Function) -> list[list[tuple[int, int, str, int]]]:
    runs, run = [], []
    for s in (s for s in f.statements if s[2] == "expr"):
        if run and _adjacent(f, run[-1], s) and run[-1][3] == s[3]:
            run.append(s)
        else:
            run = [s]
            runs.append(run)
    return runs


def _store(f: Function, s) -> tuple[str, str, str] | None:
    """(record, whole target, value) of a member store `rec->m = v` or `rec.m = v`."""
    t = f.toks
    e = next((k for k in range(s[0], s[1]) if t[k].text == "="), None)
    if e is None or e < s[0] + 2 or t[e - 2].text not in (".", "->"):
        return None
    return f.span(s[0], e - 3), f.span(s[0], e - 1), f.span(e + 1, s[1] - 1)


def g_sibling(f: Function):
    """Move a member store next to a store to the same record, across independent statements."""
    t = f.toks
    for run in _runs(f):
        texts = [f.span(s[0], s[1]) for s in run]
        stores = [_store(f, s) for s in run]
        for i, x in enumerate(stores):
            if not x:
                continue
            mine = {t[k].text for k in range(run[i][0], run[i][1])}
            for j, y in enumerate(stores):
                if not y or y[0] != x[0] or abs(i - j) < 2:
                    continue
                for to in (j, j + 1) if j < i else (j - 1, j):
                    if to == i:
                        continue
                    crossed = range(to, i) if to < i else range(i + 1, to + 1)
                    if any(
                        x[1] in texts[k]
                        or (stores[k] and stores[k][1] in texts[i])
                        or (t[run[k][0] + 1].text == "=" and t[run[k][0]].text in mine)
                        for k in crossed
                    ):
                        continue
                    call = any(
                        t[q].kind == "ident" and t[q + 1].text == "("
                        for k in crossed
                        for q in range(run[k][0], run[k][1])
                    )
                    order = texts[:i] + texts[i + 1 :]
                    order.insert(to, texts[i])
                    yield (
                        f"move {texts[i][:40]} {'after' if to > j or (to == j and j > i) else 'before'} {texts[j][:30]}"
                        + (" [needs-review]" if call else ""),
                        tuple(
                            (t[s[0]].start, t[s[1]].end, new)
                            for s, new in zip(run, order, strict=True)
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


def _same_meaning(x: str, y: str) -> bool:
    """The two names differ only by a number or one is the other's prefix."""
    a, b = (re.sub(r"[_\d]+$", "", n.lower()) for n in (x, y))
    return a == b or (min(len(a), len(b)) >= 3 and (a.startswith(b) or b.startswith(a)))


def unset_reads(f: Function) -> set[str]:
    """Locals whose first use after the declarations reads them before any store."""
    t, out = f.toks, set()
    inside = {k for d in f.decls for k in range(d[0], d[1] + 1)}
    for name, (_, d) in f.locals.items():
        s = [z.text for z in t[d[0] : d[1] + 1]]
        k = s.index(name)
        if k + 1 < len(s) and s[k + 1] in ("=", "["):
            continue  # initialized or an array
        first = next((u for u in f.uses(name) if u not in inside), None)
        if first is None or t[first - 1].text in ("&", ".", "->"):
            continue
        if t[first + 1].text not in ("=", ".", "["):
            out.add(name)
    return out


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
        ux = [u for u in f.uses(x) if u > dx[1][1]]
        uy = [u for u in f.uses(y) if u > d[1]]
        if not ux or not uy or (ux[0] < uy[-1] and uy[0] < ux[-1]):
            continue  # both live at once: one local would hold two values
        edit = [(t[d[0]].start, t[d[1]].end, "")]
        edit += [(t[u].start, t[u].end, x) for u in uy]
        review = "" if _same_meaning(x, y) else " [needs-review]"
        yield f"merge {y} into {x}{review}", tuple(edit)
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


ASSIGN = {"=", "+=", "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<=", ">>="}


def _writes(f: Function, s) -> list[list[str]]:
    """Token lists of what one statement stores: assignment targets and ++/-- operands."""
    t, out = f.toks, []
    for k in range(s[0], s[1]):
        if t[k].text in ASSIGN:
            a = k - 1
            while a > s[0] and t[a - 1].text not in ASSIGN | {",", "(", ";"}:
                a -= 1
            out.append([z.text for z in t[a:k]])
        elif t[k].text in ("++", "--"):
            side = operand(t, k - 1, False) if t[k - 1].kind == "ident" else None
            side = side or operand(t, k + 1, True)
            if side:
                out.append([z.text for z in t[side[0] : side[1] + 1]])
    return out


def _contains(toks: list[str], part: list[str]) -> bool:
    n = len(part)
    return any(toks[i : i + n] == part for i in range(len(toks) - n + 1))


def _depends(f: Function, x, y) -> bool:
    """x and y cannot trade places: one stores what the other reads or stores, through a name,
    a member, a pointer or an index, or both call."""
    t = f.toks
    tx = [z.text for z in t[x[0] : x[1] + 1]]
    ty = [z.text for z in t[y[0] : y[1] + 1]]

    def hits(writes, other):
        for w in writes:
            name = next((z for z in w if z not in ("*", "(", ")")), None)
            if _contains(other, w) or (
                name and ("*" in w or "[" in w) and name in other
            ):
                return True
        return False

    def calls(s):
        return any(
            t[k].kind == "ident" and t[k + 1].text == "(" and t[k].text not in KEYWORDS
            for k in range(s[0], s[1])
        )

    return (
        hits(_writes(f, x), ty)
        or hits(_writes(f, y), tx)
        or (calls(x) and (calls(y) or _writes(f, y)))
        or (calls(y) and _writes(f, x))
    )


def _block_statements(f: Function, a: int, b: int) -> list[tuple[int, int]]:
    """(first, last) token of each top-level statement in toks[a..b]; a compound is one."""
    t, out, k = f.toks, [], a
    while k <= b:
        start = k
        if t[k].text == "{":
            k = matching(t, k)
        elif t[k].text in ("if", "while", "for", "switch"):
            k = matching(t, k + 1) + 1
            k = matching(t, k) if t[k].text == "{" else expression_end(t, k, {";"}) + 1
            while t[k].text != "}" and k + 1 <= b and t[k + 1].text == "else":
                k += 2
                if t[k].text == "if":
                    k = matching(t, k + 1) + 1
                k = (
                    matching(t, k)
                    if t[k].text == "{"
                    else expression_end(t, k, {";"}) + 1
                )
        elif t[k].text == "do":
            k = matching(t, k + 1)
            k = expression_end(t, k + 1, {";"}) + 1
        else:
            k = expression_end(t, k, {";"}) + 1
        out.append((start, k))
        k += 1
    return out


def _arms(f: Function, k: int):
    """For `if` at k with braced arms: (cond close, then {..}, else {..} or None)."""
    t = f.toks
    c = matching(t, k + 1)
    if t[c + 1].text != "{":
        return None
    b1 = matching(t, c + 1)
    if t[b1 + 1].text == "else" and t[b1 + 2].text == "{":
        return c, (c + 1, b1), (b1 + 2, matching(t, b1 + 2))
    if t[b1 + 1].text == "else":
        return None
    return c, (c + 1, b1), None


def _plain(f: Function, s) -> bool:
    """A statement with no braces, labels, gotos or returns."""
    words = {z.text for z in f.toks[s[0] : s[1] + 1]}
    return (
        f.toks[s[1]].text == ";"
        and not words & {"{", "}", "goto", "return", "break", "continue", "case"}
        and f.toks[s[0]].text not in KEYWORDS
    )


def _set_only(f: Function, s, name: str) -> str | None:
    """The value of `name = value;` when value does not read name and calls nothing."""
    t = f.toks
    if not (t[s[0]].text == name and t[s[0] + 1].text == "=" and t[s[1]].text == ";"):
        return None
    value = t[s[0] + 2 : s[1]]
    if any(z.text == name or z.text in ASSIGN | {"++", "--"} for z in value) or any(
        value[q].kind == "ident" and value[q + 1].text == "("
        for q in range(len(value) - 1)
    ):
        return None
    return f.span(s[0] + 2, s[1] - 1)


def g_argument(f: Function):
    """A local set once and read once as a call argument becomes the argument, and back."""
    t = f.toks
    for x, y in zip(f.statements, f.statements[1:], strict=False):
        if x[2] != "expr" or x[3] != y[3] or not _adjacent(f, x, y):
            continue
        name = t[x[0]].text
        if name not in f.locals or t[x[0] + 1].text != "=":
            continue
        value = _set_only(f, x, name)
        uses = [u for u in f.uses(name) if u > f.locals[name][1][1]]
        if (
            value is None
            or len(uses) != 2
            or uses[0] != x[0]
            or not (y[0] < uses[1] < y[1])
        ):
            continue
        u = uses[1]
        if t[u - 1].text not in ("(", ",") or t[u + 1].text not in (")", ","):
            continue
        d = f.locals[name][1]
        edit = [(t[x[0]].start, t[x[1]].end, ""), (t[u].start, t[u].end, value)]
        if not any(z.text in (",", "=") for z in t[d[0] : d[1]]):
            edit.append((t[d[0]].start, t[d[1]].end, ""))
        yield f"pass {value[:30]} straight to the call", tuple(edit)
    used = set(f.locals) | {t[p[1]].text for p in f.params()}
    for s in f.statements:
        if s[2] != "expr" or s[3] != 1 or not _plain(f, s):
            continue
        for k in range(s[0], s[1]):
            if (
                not (t[k].kind == "ident" and t[k + 1].text == "(")
                or t[k].text in KEYWORDS
            ):
                continue
            if MACRO.match(t[k].text):
                continue
            close, a = matching(t, k + 1), k + 2
            while a < close:
                e = expression_end(t, a, {","})
                arg = t[a : e + 1]
                if (
                    len(arg) > 1
                    and not any(z.text in ASSIGN | {"++", "--", "&"} for z in arg)
                    and not any(
                        arg[q].kind == "ident" and arg[q + 1].text == "("
                        for q in range(len(arg) - 1)
                    )
                ):
                    new = next(
                        n for n in (f"arg{i}" for i in range(9)) if n not in used
                    )
                    text = f.span(a, e)
                    yield (
                        f"local {new} for argument {text[:30]}",
                        (
                            (t[f.body].end, t[f.body].end, f"\n    s32 {new};"),
                            (t[s[0]].start, t[s[0]].start, f"{new} = {text};\n    "),
                            (t[a].start, t[e].end, new),
                        ),
                    )
                a = e + 2


def g_both_arms(f: Function):
    """`x = a; if (c) { x = b; }` and `if (c) { x = b; } else { x = a; }`, both ways."""
    t = f.toks
    for x in f.statements:
        if x[2] != "expr" or not _plain(f, x):
            continue
        k = x[1] + 1
        if k >= f.end or t[k].text != "if":
            continue
        arms = _arms(f, k)
        if not arms or arms[2]:
            continue
        c, then, _ = arms
        name = t[x[0]].text
        value = _set_only(f, x, name)
        inner = _block_statements(f, then[0] + 1, then[1] - 1)
        if value is None or not inner or any(t[q].text == name for q in range(k, c)):
            continue
        if _set_only(f, inner[0], name) is None:
            continue
        yield (
            f"set {name} in both arms",
            (
                (t[x[0]].start, t[x[1]].end, ""),
                (t[then[1]].end, t[then[1]].end, f" else {{\n{name} = {value};\n}}"),
            ),
        )
    for k in range(f.body + 1, f.end):
        if t[k].text != "if" or t[k - 1].text == "else":
            continue
        arms = _arms(f, k)
        if not arms or not arms[2]:
            continue
        c, then, other = arms
        a = _block_statements(f, then[0] + 1, then[1] - 1)
        b = _block_statements(f, other[0] + 1, other[1] - 1)
        cond = f.span(k + 2, c - 1)
        for keep, drop, test in ((a, b, cond), (b, a, f"!({cond})")):
            if len(drop) != 1 or not keep:
                continue
            name = t[drop[0][0]].text
            value = _set_only(f, drop[0], name)
            if value is None or _set_only(f, keep[0], name) is None:
                continue
            if any(t[q].text == name for q in range(k, c)):
                continue
            body = f.span(keep[0][0], keep[-1][1])
            yield (
                f"set {name} once before the if",
                (
                    (
                        t[k].start,
                        t[other[1]].end,
                        f"{name} = {value};\n    if ({test}) {{\n{body}\n}}",
                    ),
                ),
            )


def g_tail(f: Function):
    """A statement both arms end with moves after the if/else, and back."""
    t = f.toks
    for k in range(f.body + 1, f.end):
        if t[k].text != "if" or t[k - 1].text == "else":
            continue
        arms = _arms(f, k)
        if not arms:
            continue
        c, then, other = arms
        last = other[1] if other else then[1]
        a = _block_statements(f, then[0] + 1, then[1] - 1)
        if other:
            b = _block_statements(f, other[0] + 1, other[1] - 1)
            if (
                len(a) > 1
                and b
                and _plain(f, a[-1])
                and f.span(*a[-1]) == f.span(*b[-1])
            ):
                tail = f.span(*a[-1])
                edit = [
                    (t[a[-1][0]].start, t[a[-1][1]].end, ""),
                    (t[last].end, t[last].end, f"\n    {tail}"),
                ]
                if len(b) > 1:
                    edit.append((t[b[-1][0]].start, t[b[-1][1]].end, ""))
                else:
                    edit.append((t[then[1]].end, t[other[1]].end, ""))
                yield f"hoist {tail[:30]} after the if/else", tuple(edit)
        nxt = last + 1
        if nxt >= f.end:
            continue
        s = _block_statements(f, nxt, f.end - 1)[0]
        if not _plain(f, s) or t[nxt - 1].text == ":":
            continue
        ends = [a[-1] if a else None]
        if other:
            b = _block_statements(f, other[0] + 1, other[1] - 1)
            ends.append(b[-1] if b else None)
        if any(
            e and t[e[0]].text in ("return", "break", "continue", "goto") for e in ends
        ):
            continue
        tail = f.span(*s)
        edit = [
            (t[s[0]].start, t[s[1]].end, ""),
            (t[then[1]].start, t[then[1]].start, f"{tail}\n"),
        ]
        if other:
            edit.append((t[other[1]].start, t[other[1]].start, f"{tail}\n"))
        else:
            edit.append((t[then[1]].end, t[then[1]].end, f" else {{\n{tail}\n}}"))
        yield f"duplicate {tail[:30]} into both arms", tuple(edit)


def _switch_breaks(f: Function, open_: int, close: int) -> list[int]:
    """`break` tokens that leave this switch (not a nested loop or switch)."""
    t, out, k = f.toks, [], open_ + 1
    while k < close:
        if t[k].text in ("for", "while", "switch", "do"):
            k = matching(t, k + 1) if t[k].text != "do" else matching(t, k + 1)
            if t[k].text == ")" and t[k + 1].text == "{":
                k = matching(t, k + 1)
        elif t[k].text == "break":
            out.append(k)
        k += 1
    return out


def g_switch_tail(f: Function):
    """The statements after a switch copied into each case before its break, and back."""
    t = f.toks
    for k in range(f.body + 1, f.end):
        if t[k].text != "switch":
            continue
        c = matching(t, k + 1)
        if t[c + 1].text != "{":
            continue
        close = matching(t, c + 1)
        breaks = _switch_breaks(f, c + 1, close)
        block_end = next(
            (j for j in range(close + 1, f.end + 1) if t[j].text == "}"), f.end
        )
        rest = t[close + 1 : block_end]
        words = {z.text for z in rest}
        has_default = any(t[j].text == "default" for j in range(c, close))
        if (
            rest
            and not words & {"{", "goto", "case", ":", "if", "for", "while", "switch"}
            and sum(z.text == ";" for z in rest) <= 3
            and breaks
            and not any(t[j].text == "}" for j in range(close + 1, block_end))
        ):
            tail = f.span(close + 1, block_end - 1)
            ends = any(z.text == "return" for z in rest)
            edit = [
                (t[b].start, t[b + 1].end, tail if ends else f"{tail}\nbreak;")
                for b in breaks
            ]
            end = "" if t[close - 2].text == "break" else f"{tail}\n"
            if not has_default:
                end += f"default:\n{tail}\n"
            if end:
                edit.append((t[close].start, t[close].start, end))
            edit.append((t[close + 1].start, t[block_end - 1].end, ""))
            yield f"copy {tail[:30]} into each case", tuple(edit)
        if breaks and has_default:
            stmts = []
            for b in breaks:
                prev = b - 1
                if t[prev].text != ";":
                    break
                a = prev - 1
                while t[a].text not in (";", ":", "{", "}"):
                    a -= 1
                s = (a + 1, prev)
                if not _plain(f, s):
                    break
                stmts.append(s)
            else:
                texts = {f.span(*s) for s in stmts}
                if (
                    len(texts) == 1
                    and t[close - 1].text == ";"
                    and t[close - 2].text == "break"
                ):
                    tail = texts.pop()
                    edit = [(t[s[0]].start, t[s[1]].end, "") for s in stmts]
                    edit.append((t[close].end, t[close].end, f"\n    {tail}"))
                    yield f"hoist {tail[:30]} after the switch", tuple(edit)


TABLE = re.compile(
    r"\b([A-Za-z_]\w*)\s*\[([^\[\]]*\*\s*(?:0x[0-9A-Fa-f]+|\d+)[^\[\]]*)\]"
)
OFFSET = re.compile(
    r"\*\s*\([^;]*?\b([A-Za-z_]\w*)\s*\)?\s*\+\s*(0x[0-9A-Fa-f]+|\d+)\s*\)"
)


def _address_taken(f: Function, name: str) -> bool:
    """`&name` appears with no member or index after it."""
    t = f.toks
    return any(
        t[u - 1].text == "&" and t[u + 1].text not in ("[", ".", "->")
        for u in f.uses(name)
    )


def _block_open(f: Function, k: int) -> int:
    """Index of the `{` that opens the innermost block holding token k."""
    t, depth = f.toks, 0
    for j in range(k - 1, f.body, -1):
        if t[j].text == "}":
            depth += 1
        elif t[j].text == "{":
            if depth == 0:
                return j
            depth -= 1
    return f.body


def _decl_type(f: Function, name: str) -> tuple[str, bool] | None:
    """(type text, is an array) of a single-declarator local or a parameter."""
    t = f.toks
    if name in f.locals:
        d = f.locals[name][1]
        if any(z.text == "," for z in t[d[0] : d[1]]):
            return None
        k = next(k for k in range(d[0], d[1]) if t[k].text == name)
        return f.span(d[0], k - 1), t[k + 1].text == "["
    for p in f.params():
        if t[p[1]].text == name and p[1] > p[0]:
            return f.span(p[0], p[1] - 1), False
    return None


GLOBAL_DECL = re.compile(
    r"^\s*extern\s+((?:const\s+)?(?:struct\s+)?\w+(?:\s*\*)*)\s*(\w+)\s*(\[[^;]*\])?\s*;",
    re.M,
)
_globals: dict[str, tuple[str, bool] | None] = {}


def global_type(name: str) -> tuple[str, bool] | None:
    """(type, is an array) of a global declared once in the tree's headers, else None."""
    if not _globals:
        for header in sorted(ROOT.glob("include/**/*.h")) + sorted(
            ROOT.glob("src/**/*.h")
        ):
            for m in GLOBAL_DECL.finditer(header.read_text(errors="replace")):
                got = (re.sub(r"\s+", " ", m[1]).strip(), bool(m[3]))
                if _globals.get(m[2], got) != got:
                    got = None
                _globals[m[2]] = got
        _globals.setdefault("", None)
    return _globals.get(name)


def _writes_name(f: Function, name: str, a: int, b: int) -> bool:
    """A store to `name` (assignment, ++ or --) between tokens a and b, or its address taken."""
    t = f.toks
    if _address_taken(f, name):
        return True
    return any(
        t[k].text == name
        and (t[k + 1].text in ASSIGN | {"++", "--"} or t[k - 1].text in ("++", "--"))
        for k in range(a, b)
    )


def _stable(f: Function, value: str, a: int, b: int) -> bool:
    """A constant, or a local or parameter not stored between tokens a and b."""
    if re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)[uUlL]*", value):
        return True
    params = {f.toks[p[1]].text for p in f.params()}
    return (value in f.locals or value in params) and not _writes_name(f, value, a, b)


def _single_assignment(f: Function, x: str):
    """(statement, value) of a local stored once, by `x = value;` or its initialiser, the value
    a constant or a plain copy; the statement is None for an initialiser."""
    t = f.toks
    d = f.locals[x][1]
    if any(z.text == "," for z in t[d[0] : d[1]]) or _address_taken(f, x):
        return None
    k = next(k for k in range(d[0], d[1]) if t[k].text == x)
    writes = [
        u
        for u in f.uses(x)
        if u > d[1]
        and (t[u + 1].text in ASSIGN | {"++", "--"} or t[u - 1].text in ("++", "--"))
    ]
    if t[k + 1].text == "=":
        value = f.span(k + 2, d[1] - 1)
        return (
            (None, value)
            if not writes
            and d[1] == k + 3
            or (not writes and d[1] == k + 4 and t[k + 2].text == "-")
            else None
        )
    if len(writes) != 1:
        return None
    s = next((s for s in f.statements if s[0] == writes[0] and s[2] == "expr"), None)
    if s is None or t[s[0] + 1].text != "=" or s[1] - s[0] not in (3, 4):
        return None
    value = f.span(s[0] + 2, s[1] - 1)
    if s[1] - s[0] == 4 and t[s[0] + 2].text != "-":
        return None
    return s, value


def _statement_at(f: Function, k: int):
    return next((s for s in f.statements if s[0] <= k <= s[1]), None)


def g_sched(f: Function):
    """A local stored once with a constant or copy: its store in the declaration, as the first
    statement of its block, or just above its first use; and one local reused for a second
    such value in a disjoint range [needs-review]."""
    t = f.toks
    for x in list(f.locals):
        got = _single_assignment(f, x)
        if got is None or _decl_type(f, x) is None:
            continue
        s, value = got
        d = f.locals[x][1]
        blk = _block_open(f, d[0])
        decls = [e for e in f.decls if _block_open(f, e[0]) == blk]
        top = decls[-1][1]
        reads = [
            u for u in f.uses(x) if u > d[1] and (s is None or not s[0] <= u <= s[1])
        ]
        if not reads or any(e[0] <= reads[0] <= e[1] for e in f.decls):
            continue
        first = _statement_at(f, reads[0])
        k = next(k for k in range(d[0], d[1]) if t[k].text == x)
        plain = f.span(d[0], k) + ";" if s is None else None
        here = s[0] if s else d[1]
        targets = []
        if s is not None:
            if _block_open(f, s[0]) != blk or not _stable(f, value, d[1], s[0]):
                continue
            targets.append(("in its declaration", None))
            if s[0] != top + 1:
                targets.append(("at the top of its block", top))
        elif top != d[1] and _stable(f, value, d[1], top):
            targets.append(("at the top of its block", top))
        if (
            first is not None
            and _block_open(f, first[0]) == blk
            and (s is None or first[0] > s[1] + 1)
            and _stable(f, value, here, first[0])
        ):
            targets.append(("just above its first use", first[0] - 1))
        for where, after in targets:
            edit = []
            if s is not None:
                edit.append((t[s[0]].start, t[s[1]].end, ""))
            if after is None:
                edit.append((t[d[1]].start, t[d[1]].start, f" = {value}"))
            else:
                if s is None:
                    edit.append((t[d[0]].start, t[d[1]].end, plain))
                edit.append((t[after].end, t[after].end, f"\n    {x} = {value};"))
            yield f"store {x} = {value[:20]} {where}", tuple(edit)
    for x, y in combinations(list(f.locals), 2):
        for a, b in ((x, y), (y, x)):
            got = _single_assignment(f, b)
            ta, tb = _decl_type(f, a), _decl_type(f, b)
            if got is None or got[0] is not None or not ta or ta != tb or ta[1]:
                continue
            da, db = f.locals[a][1], f.locals[b][1]
            if _block_open(f, da[0]) != f.body or _address_taken(f, a):
                continue
            ua = [u for u in f.uses(a) if u > da[1]]
            ub = [u for u in f.uses(b) if u > db[1]]
            first = _statement_at(f, ub[0]) if ub else None
            if (
                not ua
                or first is None
                or ua[-1] >= first[0]
                or _block_open(f, first[0]) != _block_open(f, db[0])
                or not _stable(f, got[1], db[1], first[0])
                or _in_loop_with(f, first[0], ua)
            ):
                continue
            edit = [(t[db[0]].start, t[db[1]].end, "")]
            edit.append(
                (t[first[0]].start, t[first[0]].start, f"{a} = {got[1]};\n    ")
            )
            edit += [(t[u].start, t[u].end, a) for u in ub]
            yield f"reuse {a} for {b} [needs-review]", tuple(edit)


def _loops(f: Function) -> list[tuple[int, int, int]]:
    """(keyword, body open, end) of each braced for, while and do loop."""
    t, out = f.toks, []
    for k in range(f.body + 1, f.end):
        if t[k].text in ("for", "while") and t[k - 1].text != "}":
            c = matching(t, k + 1)
            if t[c + 1].text == "{":
                out.append((k, c + 1, matching(t, c + 1)))
        elif t[k].text == "do" and t[k + 1].text == "{":
            b = matching(t, k + 1)
            out.append((k, k + 1, expression_end(t, b + 1, {";"}) + 1))
    return out


def _in_loop_with(f: Function, k: int, uses: list[int]) -> bool:
    """k sits in a loop that also holds one of uses."""
    return any(a < k < e and any(a < u < e for u in uses) for _, a, e in _loops(f))


NEG_MASK_BEFORE = {
    "(",
    ",",
    "=",
    "|",
    "^",
    "&",
    "&&",
    "||",
    "?",
    ":",
    "return",
} | ASSIGN
NEG_MASK_AFTER = {")", ";", ",", "|", "^", "&", "&&", "||", "?", ":"}


def g_alloc(f: Function):
    """Allocation forms: an argument group `&X[0], &X[1]` or `&r.a, &r.b` taken through one
    pointer local set before the call, and back; a separate local per loop for a value each loop
    sets first; `c ? M : 0` for `-(c) & M`."""
    t = f.toks
    used = set(f.locals) | {t[p[1]].text for p in f.params()}
    fresh = next(n for n in ("rec", "base", "ptr", "rec2", "base2") if n not in used)
    for s in f.statements:
        if s[2] != "expr" or not _plain(f, s):
            continue
        for k in range(s[0], s[1]):
            if (
                not (t[k].kind == "ident" and t[k + 1].text == "(")
                or t[k].text in KEYWORDS
            ):
                continue
            close, a, groups = matching(t, k + 1), k + 2, {}
            while a < close:
                e = expression_end(t, a, {","})
                if (
                    t[a].text == "&"
                    and t[a + 1].kind == "ident"
                    and t[a + 2].text in ("[", ".", "->")
                ):
                    groups.setdefault((t[a + 1].text, t[a + 2].text), []).append(a + 1)
                a = e + 2
            for (n, op), at in groups.items():
                if len(at) < 2:
                    continue
                known = _decl_type(f, n) or global_type(n)
                if not known:
                    continue
                kind, array = known
                if op == "[" and (array or kind.endswith("*")):
                    ptype, value = (kind if array else kind[:-1].rstrip()) + " *", n
                elif op == "." and not array and not kind.endswith("*"):
                    ptype, value, op = kind + " *", "&" + n, "->"
                elif op == "->" and kind.endswith("*"):
                    ptype, value = kind, n
                else:
                    continue
                edit = [(t[f.body].end, t[f.body].end, f"\n    {ptype}{fresh};")]
                edit.append((t[s[0]].start, t[s[0]].start, f"{fresh} = {value};\n    "))
                for u in at:
                    tail = "" if op == t[u + 1].text else op
                    edit.append(
                        (t[u].start, t[u + 1].end if tail else t[u].end, fresh + tail)
                    )
                yield f"argument group through {fresh} = {value}", tuple(edit)
    for p in list(f.locals):
        known = _decl_type(f, p)
        if not known or not known[0].endswith("*") or known[1]:
            continue
        got = _single_assignment_any(f, p)
        if got is None:
            continue
        s, value = got
        uses = [u for u in f.uses(p) if u > s[1]]
        stmt = _statement_at(f, uses[0]) if uses else None
        if (
            stmt is None
            or any(not stmt[0] <= u <= stmt[1] for u in uses)
            or any(
                t[u - 1].text != "&" or t[u + 1].text not in ("->", "[") for u in uses
            )
            or not re.fullmatch(r"&?\w+", value)
            or not _stable(f, value.lstrip("&"), s[1], stmt[0])
            and value.lstrip("&") in used
        ):
            continue
        name = value.lstrip("&")
        edit = [(t[s[0]].start, t[s[1]].end, "")]
        d = f.locals[p][1]
        edit.append((t[d[0]].start, t[d[1]].end, ""))
        ok = True
        for u in uses:
            if value.startswith("&"):
                if t[u + 1].text != "->":
                    ok = False
                    break
                edit.append((t[u].start, t[u + 1].end, name + "."))
            else:
                edit.append((t[u].start, t[u].end, name))
        if ok:
            yield f"argument group straight from {value}", tuple(edit)
    loops = _loops(f)
    for x in list(f.locals):
        known = _decl_type(f, x)
        if not known or known[1] or _address_taken(f, x):
            continue
        d = f.locals[x][1]
        if any(t[k].text == "=" for k in range(d[0], d[1])):
            continue
        uses = [u for u in f.uses(x) if u > d[1]]
        regions = []
        for kw, open_, end in loops:
            if t[open_ + 1].text == x and t[open_ + 2].text == "=":
                regions.append((open_ + 1, end))
            else:
                prev = _statement_at(f, kw - 1)
                if (
                    prev
                    and prev[1] == kw - 1
                    and t[prev[0]].text == x
                    and t[prev[0] + 1].text == "="
                ):
                    regions.append((prev[0], end))
        regions = sorted(set(regions))
        if (
            len(regions) < 2
            or any(not any(a <= u <= e for a, e in regions) for u in uses)
            or any(r[1] >= q[0] for r, q in zip(regions, regions[1:], strict=False))
        ):
            continue
        new = next(n for n in (f"{x}2", f"{x}_2", f"{x}3") if n not in used)
        for a, e in regions[1:]:
            edit = [
                (
                    t[f.body].end,
                    t[f.body].end,
                    f"\n    {known[0]}{'' if known[0].endswith('*') else ' '}{new};",
                )
            ]
            edit += [(t[u].start, t[u].end, new) for u in uses if a <= u <= e]
            yield (
                f"local {new} for {x} in the loop at {f.span(a, a + 2)[:20]}",
                tuple(edit),
            )
    for k in range(f.body + 1, f.end - 3):
        if t[k].text != "-" or t[k - 1].text not in NEG_MASK_BEFORE:
            continue
        if t[k + 1].text == "(":
            c = matching(t, k + 1)
            cond = f.span(k + 2, c - 1)
        elif t[k + 1].kind == "ident" and t[k + 2].text == "&":
            c, cond = k + 1, t[k + 1].text
        else:
            continue
        if t[c + 1].text != "&" or t[c + 2].kind not in ("ident", "number"):
            continue
        if t[c + 3].text not in NEG_MASK_AFTER:
            continue
        inner = t[k + 2 : c] if t[k + 1].text == "(" else []
        boolean = any(
            z.text in ("==", "!=", "<", ">", "<=", ">=", "&&", "||") for z in inner
        ) or (inner and inner[0].text == "!")
        review = "" if boolean else " [needs-review]"
        yield (
            f"({cond[:20]}) ? {t[c + 2].text} : 0 for the negate-and-mask{review}",
            ((t[k].start, t[c + 2].end, f"(({cond}) ? {t[c + 2].text} : 0)"),),
        )


def _single_assignment_any(f: Function, x: str):
    """(statement, value) of a local stored once by a `x = value;` statement, no initialiser."""
    t = f.toks
    d = f.locals[x][1]
    if any(t[k].text == "=" for k in range(d[0], d[1])) or any(
        z.text == "," for z in t[d[0] : d[1]]
    ):
        return None
    writes = [
        u
        for u in f.uses(x)
        if u > d[1]
        and (t[u + 1].text in ASSIGN | {"++", "--"} or t[u - 1].text in ("++", "--"))
    ]
    if len(writes) != 1:
        return None
    s = next((s for s in f.statements if s[0] == writes[0] and s[2] == "expr"), None)
    if s is None or t[s[0] + 1].text != "=":
        return None
    return s, f.span(s[0] + 2, s[1] - 1)


def needs_type(text: str) -> list[str]:
    """Table reads on a global spelled as offset math: `G[i * N + k]` or `*(... G + off)`."""
    try:
        f = Function(text)
    except (IndexError, KeyError, RuntimeError, StopIteration, ValueError):
        return []
    mine = set(f.locals) | {f.toks[p[1]].text for p in f.params()}
    body = text[f.toks[f.body].start :]
    out = []
    for m in list(TABLE.finditer(body)) + list(OFFSET.finditer(body)):
        if m[1] not in mine and m[1] not in TYPES:
            out.append(re.sub(r"\s+", " ", m[0])[:80])
    return sorted(set(out))


HEADER_INT = re.compile(
    r"^(\s*(?:extern\s+)?)(s8|u8|s16|u16)(\s+)(\w+)(\s*(?:\[[^;]*\])?;)", re.M
)


def header_variants(source: Path, text: str):
    """(label, header, new header text, other users) for each s8/u8/s16/u16 global or member of
    the image's own header that the function names; users are the other files that name it."""
    folder = source.parent
    names = {x.text for x in tokenize(text) if x.kind == "ident"}
    for m in re.finditer(r'^#include "([^"/]+\.h)"', source.read_text(), re.M):
        header = folder / m[1]
        if not header.exists():
            continue
        body = header.read_text()
        siblings = [p for p in sorted(folder.glob("*.c"))]
        for h in HEADER_INT.finditer(body):
            if h[4] not in names:
                continue
            word = re.compile(rf"\b{re.escape(h[4])}\b")
            users = [p for p in siblings if word.search(p.read_text())]
            for new in ("s8", "u8", "s16", "u16"):
                if new == h[2]:
                    continue
                changed = body[: h.start(2)] + new + body[h.end(2) :]
                yield f"header {h[4]}: {new}", header, changed, users


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
    "k-params": g_params,
    "l-sibling": g_sibling,
    "m-argument": g_argument,
    "n-both-arms": g_both_arms,
    "o-tail": g_tail,
    "p-switch-tail": g_switch_tail,
    "s-sched": g_sched,
    "t-alloc": g_alloc,
}


def variants(text: str, classes=None):
    """(class, label, edit) for every single edit the classes propose on one definition.

    An edit that makes a local read before it is set is dropped; a label that ends
    `[needs-review]` marks an edit whose meaning a reader must confirm."""
    try:
        f = Function(text)
        unset = unset_reads(f)
    except (IndexError, KeyError, RuntimeError, StopIteration, ValueError):
        return
    for cls, gen in CLASSES.items():
        if classes and cls not in classes:
            continue
        seen = set()
        try:
            for label, edit in gen(f):
                if edit in seen:
                    continue
                seen.add(edit)
                if len(seen) > (4**4 if cls == "k-params" else CAP):
                    break
                try:
                    if unset_reads(Function(apply(text, edit))) - unset:
                        continue
                except (IndexError, KeyError, RuntimeError, StopIteration, ValueError):
                    pass
                yield cls, label, edit
        except (IndexError, KeyError, RuntimeError, StopIteration, ValueError):
            continue


# --- measuring ----------------------------------------------------------------------------


class Score(int):
    """Instructions missing from and extra in the candidate plus operand-only differences.

    0 only when the bytes match."""

    missing = extra = operands = 0

    def __new__(cls, missing: int, extra: int, operands: int, matched: bool = False):
        total = 0 if matched else max(1, missing + extra + operands)
        self = super().__new__(cls, total)
        self.missing, self.extra, self.operands = missing, extra, operands
        return self


BRANCH = re.compile(r"^(b|j$|jal$)")
ADDRESS = re.compile(r"0x([0-9a-f]{8})\b")


def _normalise(listing, names: dict[int, str], shift: int) -> list[tuple[str, str]]:
    """(mnemonic, operands) with branch targets as labels and call targets as names; shift is
    how far the listing's code was linked from where it is shown (absolute targets carry it)."""
    if not listing:
        return []
    base = int(listing[0][0], 16)
    out = []
    for _, mnemonic, ops in listing:
        if BRANCH.match(mnemonic):

            def label(m, absolute=mnemonic in ("j", "jal"), call=mnemonic == "jal"):
                address = int(m[1], 16)
                local = address - shift if absolute else address
                if base <= local < base + 4 * len(listing) and not call:
                    return f"L{(local - base) // 4}"
                return names.get(address) or names.get(address - shift) or m[0]

            ops = ADDRESS.sub(label, ops)
        out.append((mnemonic, ops))
    return out


def _lcs_pairs(a: list[str], b: list[str]) -> list[tuple[int, int]]:
    """Index pairs of a longest common subsequence of a and b."""
    head = 0
    while head < min(len(a), len(b)) and a[head] == b[head]:
        head += 1
    tail = 0
    while (
        tail < min(len(a), len(b)) - head
        and a[len(a) - 1 - tail] == b[len(b) - 1 - tail]
    ):
        tail += 1
    pairs = [(k, k) for k in range(head)]
    ma, mb = a[head : len(a) - tail], b[head : len(b) - tail]
    if len(ma) * len(mb) <= 4_000_000:
        n, m = len(ma), len(mb)
        table = [[0] * (m + 1) for _ in range(n + 1)]
        for i in range(n - 1, -1, -1):
            row, below = table[i], table[i + 1]
            for j in range(m - 1, -1, -1):
                row[j] = (
                    below[j + 1] + 1 if ma[i] == mb[j] else max(below[j], row[j + 1])
                )
        i = j = 0
        while i < n and j < m:
            if ma[i] == mb[j]:
                pairs.append((head + i, head + j))
                i += 1
                j += 1
            elif table[i + 1][j] >= table[i][j + 1]:
                i += 1
            else:
                j += 1
    else:  # too large for the table: difflib's matching blocks
        matcher = difflib.SequenceMatcher(None, ma, mb, autojunk=False)
        for block in matcher.get_matching_blocks():
            pairs += [
                (head + block.a + k, head + block.b + k) for k in range(block.size)
            ]
    pairs += [(len(a) - tail + k, len(b) - tail + k) for k in range(tail)]
    return pairs


def lcs_score(retail, candidate, names=None, shift=0, matched=False) -> Score:
    """Align the two listings on their opcodes; count the unpaired and the operand differences."""
    r = _normalise(retail, names or {}, 0)
    c = _normalise(candidate, names or {}, shift)
    pairs = _lcs_pairs([x[0] for x in r], [x[0] for x in c])
    operands = sum(r[i][1] != c[j][1] for i, j in pairs)
    return Score(len(r) - len(pairs), len(c) - len(pairs), operands, matched)


_NAMES: dict[str, dict[int, str]] = {}


def link_names(target: str) -> dict[int, str]:
    """Address to symbol name from the image's link map."""
    if target not in _NAMES:
        link = ROOT / "build/symbols" / (target.replace("/", "+") + ".link")
        names = {}
        if link.exists():
            for line in link.read_text().splitlines():
                parts = line.split()
                if len(parts) == 2 and parts[1].startswith("0x"):
                    names[int(parts[1], 16)] = parts[0]
        _NAMES[target] = names
    return _NAMES[target]


SHIFT = re.compile(
    r"starts at \+0x([0-9A-F]+) in the candidate, retail \+0x([0-9A-F]+)"
)


def measure(ref: str, scratch: Path) -> Score | None:
    """The LCS score of `match.sh --diff` on the scratch source: 0 match, None no compile."""
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
        return Score(0, 0, 0, True)
    retail, candidate = side_by_side(result)
    if not candidate:
        return None
    moved = SHIFT.search(result.output)
    shift = int(moved[1], 16) - int(moved[2], 16) if moved else 0
    return lcs_score(retail, candidate, link_names(ref.split("@")[0]), shift)


def _parts(score) -> dict:
    return {
        "missing": getattr(score, "missing", None),
        "extra": getattr(score, "extra", None),
        "operands": getattr(score, "operands", None),
    }


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
                    "base": base_rows if base_rows is None else int(base_rows),
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
                "base": int(base_rows),
                "tried": tried,
                "failed": failed,
                "source": str(source.relative_to(ROOT)),
                "base_parts": _parts(base_rows),
                "needs_type": needs_type(text),
            }
        )
    return records


def _header_safe(ref, name, header, changed, users, own, workdir, judge) -> bool:
    """Every other MATCH function that names the retyped symbol still matches."""
    target = ref.split("@")[0]
    by_name = {v: k for k, v in link_names(target).items()}
    word = re.compile(rf"\b{re.escape(changed[1])}\b")
    with tempfile.TemporaryDirectory(dir=workdir) as tmp:
        (Path(tmp) / header.name).write_text(changed[0])
        for user in users:
            text = own[1] if user == own[0] else user.read_text()
            copy = Path(tmp) / user.name
            copy.write_text(text)
            for m in re.finditer(r"^MATCH [^(\n]*?[ *](\w+)\(", text, re.M):
                other = m[1]
                if other == name or other not in by_name:
                    continue
                start, end = function_span(text, other)
                if word.search(text[start:end]) and judge(
                    f"{target}@0x{by_name[other]:08X}", copy
                ):
                    return False
    return True


def climb(ref, name, source, judge=measure, workdir=None, classes=None, steps=12):
    """Apply the best improving edit, generate edits again from the new text, repeat.

    Class r-header retypes an s8/u8/s16/u16 global or member of the image's own header and is
    kept only while every other MATCH user of the symbol still matches. Returns one record: the
    path of edits with each step's score, the final score, the diff and the needs-type sites."""
    base = source.read_text()
    start, end = function_span(base, name)
    text = orig = base[start:end]
    path, tried, failed = [], 0, 0
    headers: dict[Path, str] = {}  # header path -> retyped text, kept across steps
    with tempfile.TemporaryDirectory(dir=workdir) as tmp:
        scratch = Path(tmp) / source.name

        def score(body: str, header=None) -> int | None:
            files = dict(headers)
            if header:
                files[header[0]] = header[1]
            for p, content in files.items():
                (Path(tmp) / p.name).write_text(content)
            scratch.write_text(base[:start] + body + base[end:])
            got = judge(ref, scratch)
            if header and header[0] not in headers:
                (Path(tmp) / header[0].name).unlink()
            return got

        rows = base_rows = score(text)
        while rows and len(path) < steps:
            best = None
            for cls, label, edit in variants(text, classes):
                new = apply(text, edit)
                got = score(new)
                tried += 1
                if got is None:
                    failed += 1
                elif got < rows and (best is None or got < best[0]):
                    best = (got, cls, label, new, None)
                    if got == 0:
                        break
            if (not classes or "r-header" in classes) and (best is None or best[0]):
                for label, header, changed, users in header_variants(source, text):
                    if header in headers:
                        continue
                    got = score(text, (header, changed))
                    tried += 1
                    if got is None:
                        failed += 1
                    elif got < rows and (best is None or got < best[0]):
                        whole = base[:start] + text + base[end:]
                        symbol = label.split()[1].rstrip(":")
                        if _header_safe(
                            ref,
                            name,
                            header,
                            (changed, symbol),
                            users,
                            (source, whole),
                            workdir,
                            judge,
                        ):
                            best = (got, "r-header", label, text, (header, changed))
            if best is None:
                break
            rows, cls, label, new, header = best
            step = {
                "class": cls,
                "edit": label,
                "score": int(rows),
                **_parts(rows),
                "needs_review": label.endswith("[needs-review]"),
                "diff": _diff(text, new),
            }
            if header:
                headers[header[0]] = header[1]
                step["diff"] = _diff(header[0].read_text(), header[1])
                step["header"] = str(header[0].relative_to(ROOT))
            path.append(step)
            text = new
    return {
        "ref": ref,
        "class": "climb",
        "source": str(source.relative_to(ROOT)),
        "base": int(base_rows) if base_rows is not None else None,
        "base_parts": _parts(base_rows),
        "path": path,
        "final": int(rows) if rows is not None else None,
        **_parts(rows),
        "match": rows == 0,
        "tried": tried,
        "failed": failed,
        "diff": _diff(orig, text),
        "needs_type": needs_type(text),
    }


def _diff(a: str, b: str) -> str:
    return "".join(difflib.unified_diff(a.splitlines(True), b.splitlines(True), n=1))


def _record(ref, base_rows, cls, label, text, edit, rows):
    diff = _diff(text, apply(text, edit))
    return {
        "ref": ref,
        "base": int(base_rows),
        "class": cls,
        "edit": label,
        "diff": diff,
        "score": int(rows),
        **_parts(rows),
        "match": rows == 0,
    }


def _job(ref: str, name: str | None, pairs: bool, classes=None, steps=0):
    name = name or symbol_name(ref)
    source = find_source(name) if name else None
    if source is None:
        return [{"ref": ref, "class": "summary", "error": f"no draft for {name}"}]
    before = resource.getrusage(resource.RUSAGE_CHILDREN)
    try:
        if steps:
            records = [climb(ref, name, source, classes=classes, steps=steps)]
        else:
            records = sweep(ref, name, source, pairs, classes=classes)
    except Exception as error:  # one bad draft must not stop the sweep
        records = [{"ref": ref, "class": "summary", "error": repr(error)[:200]}]
    after = resource.getrusage(resource.RUSAGE_CHILDREN)
    records[-1]["cpu"] = round(
        after.ru_utime + after.ru_stime - before.ru_utime - before.ru_stime, 1
    )
    return records


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
    parser.add_argument(
        "--climb",
        type=int,
        default=0,
        metavar="STEPS",
        help="hill-climb: apply the best edit and sweep again, up to STEPS edits",
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
            pool.submit(_job, ref, name, args.pairs, args.classes, args.climb): ref
            for ref, name in rows
        }
        for done in as_completed(futures):
            for record in done.result():
                out.write(json.dumps(record) + "\n")
            out.flush()
            summary = done.result()[-1]
            print(
                futures[done],
                {k: v for k, v in summary.items() if k not in ("ref", "diff", "path")},
                file=sys.stderr,
                flush=True,
            )
    return 0


if __name__ == "__main__":
    sys.exit(main())
