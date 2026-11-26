#!/usr/bin/env python3
"""Fail when a function definition in src/ does not carry exactly one status marker.

The rule is in include/match/match.h: every lifted function starts its definition with one
marker. ``MATCH`` marks a body that compiles in the default build. ``NON_MATCHING`` marks a
draft, which must sit under ``#ifdef NON_MATCHING`` with its ``INCLUDE_ASM`` in the ``#else``.
``HAND_ASM`` marks the C equivalent of a function the original programmer wrote in assembly. It
sits under ``#if HAND_ASM_MODEL`` (the model builds under ``NON_MATCHING`` or ``BOF3_PORT``), is
required for every function in ``asm/*/hand/`` and is allowed nowhere else.
``--diff REF`` runs the same whole-tree marker scan and lets a new draft land only when ``config/attempts.jsonl`` holds an object for its function
(``<image>@0x<ADDR>``), so every unmatched function keeps its closest draft with its record.
Every row of that file is one JSON object per line with exactly ``function``, ``tried``,
``first_diff``, ``score``, in that order, which are the keys ``tools/worklist.py`` reads; a row
with other keys or another order fails here. The file is append-only: ``tools/attempts.py add``.
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

import re
import subprocess
import sys
from dataclasses import dataclass
from pathlib import Path

from bof3.adapters.attempts import PATH as ROW_PATH
from bof3.adapters.attempts import files, read_lines, read_text
from bof3.adapters.config import read_symbols
from bof3.attempts import function_of, validate
from bof3.core.paths import ROOT
from bof3.resolve.ids import asm_dir
from check_names import added_lines

MARKERS = ("MATCH", "NON_MATCHING", "HAND_ASM")
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


def _switch(stack: list[tuple[str, bool]]) -> str:
    """The open switch the next token sits in: ``draft``, ``hand`` or ``plain``."""
    for guard, in_else in stack:
        if guard and not in_else:
            return guard
    return "plain"


Head = list[tuple[str, int, str]]
ATTEMPT_COMMENT = re.compile(
    r"\b(?:NON_?MATCHING(?:\s|:)|first diff(?:erence|ering)?|\btried\b)", re.I
)
NON_MATCHING_GUARD = re.compile(r"defined\s*\(?\s*NON_MATCHING\s*\)?")


def _definition_problem(head: Head, markers: Head) -> str | None:
    """Why a definition's markers are wrong, or None."""
    if len(markers) != 1:
        kind = "no marker" if not markers else f"{len(markers)} markers"
        return f"{kind}; a definition needs exactly one"
    marker, _, guard = head[0]
    if marker not in MARKERS:
        return "the marker must be the first token of the definition"
    if marker == "NON_MATCHING" and guard != "draft":
        return f"{marker} outside `#ifdef NON_MATCHING`"
    if marker == "HAND_ASM" and guard != "hand":
        return "HAND_ASM outside `#if HAND_ASM_MODEL`"
    if marker == "MATCH" and guard != "plain":
        return "MATCH inside a draft switch"
    return None


def _head_violation(
    path: str, head: Head, is_definition: bool, line: int
) -> Violation | None:
    """The marker problem of one declaration or definition head, or None when it is fine."""
    markers = [t for t in head if t[0] in MARKERS]
    if not markers and (not is_definition or any(t[0] == "inline" for t in head)):
        return None  # `static inline` helpers are not lifted functions
    where = markers[0][1] if markers else head[0][1] if head else line
    if not is_definition:
        return Violation(
            path,
            where,
            _head_text(head),
            "marker on something that is not a function definition",
        )
    problem = _definition_problem(head, markers)
    return Violation(path, where, _function_name(head), problem) if problem else None


def _comment_problem(comment: str, after: str) -> str | None:
    """Why a comment does not belong in the source, or None."""
    if re.match(r"[ \t]*\n[ \t]*INCLUDE_ASM\s*\(", after):
        return "comment above INCLUDE_ASM; record attempts in config/attempts.jsonl"
    if ATTEMPT_COMMENT.search(comment):
        return "attempt note belongs in config/attempts.jsonl"
    return None


def _apply_directive(directive: str, stack: list[tuple[str, bool]]) -> None:
    """Track the `#if` nesting and which branches are the draft switch."""
    parsed = re.match(r"\s*#\s*(\w*)\s*(.*)", directive.replace("\\\n", " "), re.DOTALL)
    word, rest = parsed.groups() if parsed else ("", "")
    if word in ("if", "ifdef", "ifndef"):
        is_draft = (word == "ifdef" and rest.strip() == "NON_MATCHING") or (
            word == "if" and NON_MATCHING_GUARD.fullmatch(rest.strip())
        )
        is_hand = word == "if" and rest.strip() == "HAND_ASM_MODEL"
        stack.append(("draft" if is_draft else "hand" if is_hand else "", False))
    elif word in ("else", "elif") and stack:
        stack[-1] = (stack[-1][0], True)
    elif word == "endif" and stack:
        stack.pop()


class _Scanner:
    """Walks the tokens of one file and collects the definition heads it finds."""

    def __init__(self, path: str) -> None:
        self.path = path
        self.found: list[Violation] = []
        self.stack: list[tuple[str, bool]] = []
        self.head: Head = []
        self.depth = 0
        self.body_is_function = False
        self.kr_params = False

    def reset_head(self) -> None:
        self.head.clear()
        self.kr_params = False

    def judge(self, is_definition: bool, line: int) -> None:
        violation = _head_violation(self.path, self.head, is_definition, line)
        if violation:
            self.found.append(violation)

    def body_token(self, tok: str) -> None:
        """A token inside a braced body: track where the body ends."""
        if tok == "{":
            self.depth += 1
        elif tok == "}":
            self.depth -= 1
            if self.depth == 0 and self.body_is_function:
                self.body_is_function = False
                self.reset_head()

    def head_token(self, tok: str, line: int) -> None:
        """A token at the top level: a head token, or the `{`, `;` or `}` that ends it."""
        draft = _switch(self.stack)
        if tok == "{":
            if self.head and (self.head[-1][0] == ")" or self.kr_params):
                self.judge(True, line)
                self.body_is_function = True
            self.depth = 1
        elif tok == ";":
            if _starts_kr_params(self.head):
                self.head.append((tok, line, draft))
                self.kr_params = True
                return
            self.judge(False, line)
            self.reset_head()
        elif tok == "}":
            self.reset_head()
        else:
            self.head.append((tok, line, draft))


def check_text(text: str, path: str = "<text>") -> list[Violation]:
    scan = _Scanner(path)
    line = 1
    for m in TOKEN.finditer(text):
        kind, tok = m.lastgroup, m.group()
        tok_line = line
        line += tok.count("\n")
        if kind == "comment":
            problem = _comment_problem(tok, text[m.end() :])
            if problem:
                scan.found.append(Violation(path, tok_line, "comment", problem))
        elif kind == "directive":
            _apply_directive(tok, scan.stack)
        elif kind in ("string", "char", "number", "space"):
            continue
        elif scan.depth > 0:
            scan.body_token(tok)
        else:
            scan.head_token(tok, tok_line)
    return scan.found


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


def hand_names(hand_file: str) -> set[str]:
    """The names a hand file answers to: its stem and each symbol it exports."""
    path = Path(hand_file)
    text = path.read_text(errors="ignore") if path.exists() else ""
    return {path.stem, *re.findall(r"^\s*\.globl\s+(\w+)", text, re.M)}


def check_hand_units(hand_files: list[str], sources: dict[str, str]) -> list[Violation]:
    """HAND_ASM is required on every asm/*/hand/ function and allowed on no other."""
    names = {f: hand_names(f) for f in hand_files}
    hand = set().union(*names.values())
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
    for name in sorted(Path(f).stem for f, n in names.items() if not n & marked):
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


def draft_ref(path: str, text: str, root: Path | None = None) -> str | None:
    """The attempts key ``<image>@0x<ADDR>`` of the draft that `text` starts, or None."""
    root = root or ROOT
    found = re.search(r"NON_MATCHING\s[^;{}()]*?\b(\w+)\s*\(", text)
    folder = asm_dir(root / path, root)
    if not found or not folder:
        return None
    name, image = found.group(1), folder.removeprefix("build/").removeprefix("asm/")
    if m := re.fullmatch(r"func_([0-9A-Fa-f]{8})", name):
        return f"{image}@0x{m.group(1).upper()}"
    symbols = read_symbols(root)
    addr = symbols.get(image, {}).get(name, {}).get("addr")
    return f"{image}@0x{addr:08X}" if addr is not None else None


def attempted(root: Path | None = None) -> set[str]:
    return {function_of(row) for row in read_lines((root or ROOT) / ROW_PATH)}


def attempt_problems(root: Path | None = None) -> list[str]:
    """Each attempts row outside the schema or the order, as `path:line: problem`."""
    return [
        problem
        for path in files((root or ROOT) / ROW_PATH)
        if path.exists()
        for problem in validate(read_text(path), str(path))
    ]


def report_attempts(problems: list[str]) -> bool:
    """Print each malformed attempts row and the count; True when there is one."""
    for problem in problems:
        print(problem, file=sys.stderr)
    if problems:
        print(
            f"check-markers: {len(problems)} row(s) of config/attempts.jsonl "
            "outside the schema",
            file=sys.stderr,
        )
    return bool(problems)


def marker_problems(paths: list[str], whole_tree: bool) -> list[Violation]:
    """Print and return every definition in `paths` without exactly one marker."""
    sources = {p: Path(p).read_text(encoding="utf-8", errors="ignore") for p in paths}
    problems: list[Violation] = []
    if whole_tree:
        problems += check_hand_units(tracked_hand_files(), sources)
    for path, text in sources.items():
        problems += check_text(text, path)
    for problem in problems:
        print(problem, file=sys.stderr)
    if problems:
        print(
            f"check-markers: {len(problems)} definition(s) without exactly one marker",
            file=sys.stderr,
        )
    return problems


def main(argv: list[str]) -> int:
    if argv and argv[0] in ("-h", "--help"):
        print(__doc__.strip())
        return 0
    if argv and argv[0] == "--diff":
        if len(argv) != 2:
            print("usage: python3 tools/check_markers.py --diff REF", file=sys.stderr)
            return 2
        if report_attempts(attempt_problems()):
            return 1
        bad, known = 0, attempted()
        if marker_problems(tracked_sources(), whole_tree=True):
            bad = 1
        for path, line, text in added_lines(argv[1]):
            if re.match(r"\s*#\s*if(?:def)?\s+NON_MATCHING\b", text):
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
            print(f"check-markers: markers or drafts fail against {argv[1]}", file=sys.stderr)
            return 1
        print(
            f"check-markers: every definition carries one marker; every draft landed "
            f"against {argv[1]} has attempts"
        )
        return 0
    paths = argv or tracked_sources()
    problems = marker_problems(paths, whole_tree=not argv)
    malformed_rows = report_attempts(attempt_problems())
    if problems or malformed_rows:
        return 1
    print(f"check-markers: {len(paths)} files, every definition carries one marker")
    return 0

if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
