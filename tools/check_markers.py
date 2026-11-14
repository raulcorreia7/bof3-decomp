#!/usr/bin/env python3
"""Fail when a function definition in src/ does not carry exactly one status marker.

The rule is in include/match/match.h: every lifted function starts its definition with one
marker. ``MATCH`` marks a body that compiles in the default build. ``NON_MATCHING`` marks a
draft, which must sit under ``#ifdef NON_MATCHING`` with its ``INCLUDE_ASM`` in the ``#else``.
``HAND_ASM`` marks the C equivalent of a function the original programmer wrote in assembly. It
sits under ``#ifdef NON_MATCHING`` like a draft, is required for every function in
``asm/*/hand/`` and is allowed nowhere else; ``--diff`` lets that switch land in a file that holds one.
``--diff REF`` lets a new draft land when ``config/attempts.jsonl`` holds an object for its function
(``<image>@0x<ADDR>``), so every unmatched function keeps its closest draft with its record.
Status markers never take a ``FAKE:`` note.
The one exception is a ``static inline`` helper in a header, which is not a lifted function. PsyQ
stubs such as ``__main`` carry ``MATCH`` like any other definition.

The scan tokenizes each file, so wrapped signatures, comments, strings and macro bodies do not
confuse it. A definition is a top-level ``{`` that follows a parameter list. Both branches of an
``#if`` count, since each defines the function for one build. A marker on anything that is not
a definition (for example ``MATCH INCLUDE_ASM(f);``) fails as well.

Usage: python3 tools/check_markers.py [FILE...]    (default: every tracked src/**/*.c and *.h)
"""

from __future__ import annotations

import json
import re
import subprocess
import sys
import tomllib
from dataclasses import dataclass
from pathlib import Path

from bof3.resolve.ids import asm_dir
from check_names import added_lines

ROOT = Path(__file__).resolve().parent.parent

MARKERS = ("MATCH", "NON_MATCHING", "HAND_ASM")
DRAFT_MARKERS = ("NON_MATCHING", "HAND_ASM")
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
        elif head[0][0] in DRAFT_MARKERS and head[0][2] != "draft":
            found.append(
                Violation(
                    path, where, name, f"{head[0][0]} outside `#ifdef NON_MATCHING`"
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
        if kind == "comment":
            if re.match(r"[ \t]*\n[ \t]*INCLUDE_ASM\s*\(", text[m.end() :]):
                found.append(
                    Violation(
                        path,
                        tok_line,
                        "comment",
                        "comment above INCLUDE_ASM; record attempts in config/attempts.jsonl",
                    )
                )
            elif re.search(
                r"\b(?:NON_?MATCHING(?:\s|:)|first diff(?:erence|ering)?|\btried\b)",
                tok,
                re.I,
            ):
                found.append(
                    Violation(
                        path,
                        tok_line,
                        "comment",
                        "attempt note belongs in config/attempts.jsonl",
                    )
                )
            continue
        if kind in ("string", "char", "number", "space"):
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


def hand_functions(hand_files: list[str]) -> set[str]:
    """The function names of the files in asm/*/hand/."""
    return {Path(f).stem for f in hand_files}


def check_hand_units(hand_files: list[str], sources: dict[str, str]) -> list[Violation]:
    """HAND_ASM is required on every asm/*/hand/ function and allowed on no other."""
    hand = hand_functions(hand_files)
    marked: set[str] = set()
    found: list[Violation] = []
    for path, text in sources.items():
        for m in re.finditer(r"^HAND_ASM\b[^;{]*?\b(\w+)\s*\(", text, re.M):
            marked.add(m.group(1))
            if m.group(1) not in hand:
                line = text.count("\n", 0, m.start()) + 1
                found.append(
                    Violation(
                        path,
                        line,
                        m.group(1),
                        "HAND_ASM on a function with no asm/*/hand/ file",
                    )
                )
    for name in sorted(hand - marked):
        found.append(
            Violation("asm/hand", 1, name, "hand-written assembly without HAND_ASM")
        )
    return found


def tracked_hand_files() -> list[str]:
    out = subprocess.run(
        ["git", "ls-files", "asm/**/hand/*.s"],
        capture_output=True,
        text=True,
        check=True,
    ).stdout
    return out.split()


def has_hand_asm(path: str) -> bool:
    """True when the file defines a HAND_ASM function, whose model stays under the draft switch."""
    try:
        text = Path(path).read_text(encoding="utf-8", errors="ignore")
    except OSError:
        return False
    return re.search(r"^HAND_ASM\s", text, re.M) is not None


def draft_ref(path: str, text: str, root: Path | None = None) -> str | None:
    """The attempts key ``<image>@0x<ADDR>`` of the draft that `text` starts, or None."""
    root = root or ROOT
    found = re.search(r"NON_MATCHING\s[^;{}()]*?\b(\w+)\s*\(", text)
    folder = asm_dir(root / path, root)
    if not found or not folder:
        return None
    name, image = found.group(1), folder.removeprefix("asm/")
    if m := re.fullmatch(r"func_([0-9A-Fa-f]{8})", name):
        return f"{image}@0x{m.group(1).upper()}"
    symbols = tomllib.loads((root / "config/symbols.toml").read_text(encoding="utf-8"))
    addr = symbols.get(image, {}).get(name, {}).get("addr")
    return f"{image}@0x{addr:08X}" if addr is not None else None


def attempted(root: Path | None = None) -> set[str]:
    """The functions that `config/attempts.jsonl` holds an object for."""
    path = (root or ROOT) / "config/attempts.jsonl"
    rows = path.read_text(encoding="utf-8").splitlines() if path.exists() else []
    return {json.loads(row)["function"] for row in rows if row.strip()}


def main(argv: list[str]) -> int:
    if argv and argv[0] in ("-h", "--help"):
        print(__doc__.strip())
        return 0
    if argv and argv[0] == "--diff":
        if len(argv) != 2:
            print("usage: python3 tools/check_markers.py --diff REF", file=sys.stderr)
            return 2
        bad, known = 0, attempted()
        for path, line, text in added_lines(argv[1]):
            if re.match(r"\s*#\s*if(?:def)?\s+NON_MATCHING\b", text):
                if has_hand_asm(path):
                    continue
                rest = "\n".join(Path(path).read_text().splitlines()[line:])
                ref = draft_ref(path, rest)
                if ref in known:
                    continue
                print(
                    f"{path}:{line}: a draft needs its attempts object: add one with "
                    f'"function": "{ref or "<image>@0x<ADDR>"}" to config/attempts.jsonl '
                    "(the form reached and the first differing instruction)",
                    file=sys.stderr,
                )
                bad = 1
        if bad:
            print(f"check-markers: drafts landed against {argv[1]}", file=sys.stderr)
            return 1
        print(f"check-markers: every draft landed against {argv[1]} has attempts")
        return 0
    paths = argv or tracked_sources()
    problems: list[Violation] = []
    if not argv:
        sources = {
            p: Path(p).read_text(encoding="utf-8", errors="ignore") for p in paths
        }
        problems += check_hand_units(tracked_hand_files(), sources)
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
