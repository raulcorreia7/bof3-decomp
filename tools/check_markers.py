"""Fail when a function definition in src/ does not carry exactly one status marker.

The rule is in include/match/match.h: every lifted function starts its definition with one
marker. ``MATCH`` marks a body that compiles in the default build. ``NON_MATCHING`` marks a
draft, which must sit under ``#ifdef NON_MATCHING`` with its ``INCLUDE_ASM`` in the ``#else``.
The one exception is a ``static inline`` helper in a header, which is not a lifted function. PsyQ
stubs such as ``__main`` carry ``MATCH`` like any other definition.

The scan tokenizes each file, so wrapped signatures, comments, strings and macro bodies do not
confuse it. A definition is a top-level ``{`` that follows a parameter list. Both branches of an
``#if`` count, since each defines the function for one build. A marker on anything that is not
a definition (for example ``MATCH INCLUDE_ASM(f);``) fails as well.

Usage: python3 tools/check_markers.py [FILE...]    (default: every tracked src/**/*.c and *.h)
"""

from __future__ import annotations

import re
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

MARKERS = ("MATCH", "NON_MATCHING")
TOKEN = re.compile(
    r"""
      (?P<comment>/\*.*?\*/|//[^\n]*)
    | (?P<string>"(?:\\.|[^"\\\n])*")
    | (?P<char>'(?:\\.|[^'\\\n])*')
    | (?P<directive>^[ \t]*\#(?:\\\n|[^\n])*)
    | (?P<ident>[A-Za-z_]\w*)
    | (?P<number>\d[\w.]*)
    | (?P<space>\s+)
    | (?P<punct>.)
    """,
    re.DOTALL | re.MULTILINE | re.VERBOSE,
)


@dataclass(frozen=True)
class Violation:
    path: str
    line: int
    name: str
    problem: str

    def __str__(self) -> str:
        return f"{self.path}:{self.line}: {self.name}: {self.problem}"


def _in_draft(stack: list[tuple[str, bool]]) -> bool:
    """True inside the first branch of an `#ifdef NON_MATCHING` (or `#if defined(...)`)."""
    return any(guard == "draft" and not in_else for guard, in_else in stack)


def check_text(text: str, path: str = "<text>") -> list[Violation]:
    found: list[Violation] = []
    stack: list[tuple[str, bool]] = []
    head: list[tuple[str, int, str]] = []  # (token, line, draft-state at the token)
    depth = 0
    line = 1
    body_is_function = False
    kr_params = False

    def draft() -> str:
        return "draft" if _in_draft(stack) else "plain"

    def judge_head(is_definition: bool) -> None:
        markers = [t for t in head if t[0] in MARKERS]
        if is_definition and not markers and any(t[0] == "inline" for t in head):
            return  # `static inline` helpers are not lifted functions
        if not markers and not is_definition:
            return
        first = head[0] if head else ("", line, "plain")
        name = _function_name(head) if is_definition else "(not a definition)"
        where = markers[0][1] if markers else first[1]
        if not is_definition:
            found.append(
                Violation(
                    path,
                    where,
                    _head_text(head),
                    "marker on something that is not a function definition",
                )
            )
            return
        if len(markers) != 1:
            kind = "no marker" if not markers else f"{len(markers)} markers"
            found.append(
                Violation(path, where, name, f"{kind}; a definition needs exactly one")
            )
        elif head[0][0] not in MARKERS:
            found.append(
                Violation(
                    path,
                    where,
                    name,
                    "the marker must be the first token of the definition",
                )
            )
        elif head[0][0] == "NON_MATCHING" and head[0][2] != "draft":
            found.append(
                Violation(
                    path, where, name, "NON_MATCHING outside `#ifdef NON_MATCHING`"
                )
            )
        elif head[0][0] == "MATCH" and head[0][2] == "draft":
            found.append(
                Violation(path, where, name, "MATCH inside `#ifdef NON_MATCHING`")
            )

    for m in TOKEN.finditer(text):
        kind, tok = m.lastgroup, m.group()
        tok_line = line
        line += tok.count("\n")
        if kind in ("comment", "string", "char", "number", "space"):
            continue
        if kind == "directive":
            parsed = re.match(
                r"\s*#\s*(\w*)\s*(.*)", tok.replace("\\\n", " "), re.DOTALL
            )
            word, rest = parsed.groups() if parsed else ("", "")
            if word in ("if", "ifdef", "ifndef"):
                is_draft = (word == "ifdef" and rest.strip() == "NON_MATCHING") or (
                    word == "if"
                    and re.fullmatch(
                        r"defined\s*\(?\s*NON_MATCHING\s*\)?", rest.strip()
                    )
                )
                stack.append(("draft" if is_draft else "", False))
            elif word in ("else", "elif") and stack:
                stack[-1] = (stack[-1][0], True)
            elif word == "endif" and stack:
                stack.pop()
            continue
        if depth > 0:
            if tok == "{":
                depth += 1
            elif tok == "}":
                depth -= 1
                if depth == 0 and body_is_function:
                    head.clear()
                    body_is_function = False
                    kr_params = False
            continue
        if tok == "{":
            if head and (head[-1][0] == ")" or kr_params):
                judge_head(True)
                body_is_function = True
            depth = 1
            continue
        if tok == ";":
            if _starts_kr_params(head):
                head.append((tok, tok_line, draft()))
                kr_params = True
                continue
            judge_head(False)
            head.clear()
            kr_params = False
            continue
        if tok == "}":
            head.clear()
            kr_params = False
            continue
        head.append((tok, tok_line, draft()))
    return found


def _starts_kr_params(head: list[tuple[str, int, str]]) -> bool:
    """True for ``name(a, b) type a;``: an old-style definition whose parameter types follow."""
    toks = [t[0] for t in head]
    if "(" not in toks or "=" in toks[: toks.index("(")]:
        return False
    close = toks.index(")") if ")" in toks else -1
    names = toks[toks.index("(") + 1 : close]
    if close < 0 or close == len(toks) - 1 or not names or names == ["void"]:
        return False
    if not re.fullmatch(r"[A-Za-z_]\w*", toks[close + 1]):
        return False
    return all(t == "," or re.fullmatch(r"[A-Za-z_]\w*", t) for t in names)


def _head_text(head: list[tuple[str, int, str]]) -> str:
    return " ".join(t[0] for t in head)[:60]


def _function_name(head: list[tuple[str, int, str]]) -> str:
    for i, (tok, _, _) in enumerate(head):
        if tok == "(" and i > 0:
            return head[i - 1][0]
    return "(unnamed)"


def tracked_sources() -> list[str]:
    out = subprocess.run(
        ["git", "ls-files", "src/*.c", "src/*.h"],
        capture_output=True,
        text=True,
        check=True,
    ).stdout
    return out.split()


def main(argv: list[str]) -> int:
    paths = argv or tracked_sources()
    problems: list[Violation] = []
    for path in paths:
        problems += check_text(
            Path(path).read_text(encoding="utf-8", errors="ignore"), path
        )
    for problem in problems:
        print(problem, file=sys.stderr)
    if problems:
        print(
            f"check-markers: {len(problems)} definition(s) without exactly one marker",
            file=sys.stderr,
        )
        return 1
    print(f"check-markers: {len(paths)} files, every definition carries one marker")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
