#!/usr/bin/env python3
"""Fail when an invented identifier in include/ or src/ carries an 8-digit hex address.

A name says what a thing is for the game, never where it lives. The default tool names are the
only identifiers allowed to hold an address: ``func_<ADDR>``, ``D_<ADDR>``, ``L<ADDR>``,
``jtbl_*``, ``jpt_*`` and ``s_gap_*``. Comments, strings and config/symbols.toml text are not
checked.

The check is a ratchet. ``config/address_names.txt`` lists the offenders that exist today as
``<file><TAB><identifier>``. A name that is not on the list fails, and so does a listed entry
that no longer occurs, so the list only shrinks. Rename the identifier, then delete its line.

``--diff REF`` checks the lines a change adds. A new identifier must not use a word the
vocabulary rejects where another word is decided ([vocabulary](../docs/naming.md#vocabulary)),
and a parameter must be named. An identifier that already exists at ``REF`` is not a new name:
this check only stops new debt, the rename map clears the old. A file that changes must not gain a
``FIELD``/``SP_REF``/``SP`` use either: the member of the record or of the scratchpad view is the
form to write, so those uses can only shrink (plan section AY). A rebuild that moves an existing
use changes no count, so it passes.

Usage: python3 tools/check_names.py [--write]    (--write rewrites the baseline from the tree)
"""

from __future__ import annotations

import re
import subprocess
import sys
from pathlib import Path

BASELINE = Path("config/address_names.txt")
ROOTS = ("include", "src")
SUFFIXES = (".c", ".h", ".inc")

TOKEN = re.compile(
    r"""
      (?P<skip>/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\\n])*"|'(?:\\.|[^'\\\n])*'|^[ \t]*\#\s*include[^\n]*)
    | (?P<number>\b\d[\w.]*)
    | (?P<ident>[A-Za-z_]\w*)
    """,
    re.DOTALL | re.MULTILINE | re.VERBOSE,
)
ADDRESS = re.compile(r"[0-9A-Fa-f]{8}")
DEFAULT = re.compile(r"(?:func|D)_[0-9A-F]{8}|L[0-9A-F]{8}|jtbl_\w*|jpt_\w*|s_gap_\w*")
UNNAMED = re.compile(r"arg[0-9]+")
OFFSET_MACRO = re.compile(r"\b(FIELD|SP_REF|SP)\s*\(")
OFFSET_DEFINITION = re.compile(r"^[ \t]*\#[ \t]*define[ \t]+(?:FIELD|SP_REF|SP)\b")
SKIP = re.compile(
    r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\\n])*\"|'(?:\\.|[^'\\\n])*'", re.DOTALL
)
WORD = re.compile(r"[A-Z]+(?=[A-Z][a-z])|[A-Z]?[a-z]+|[A-Z]+|[0-9]+")

# One word per concept: a new name that uses a rejected word takes the decided word instead.
# See docs/naming.md#vocabulary. Only words with no second sense are here; data/work/record and
# the other nouns with a game sense are reviewed through the rename map.
REJECTED = {
    "array": "name a table for the plural of what its index selects",
    "table": "name a table for the plural of what its index selects",
    "handler": "name the action; Callback is the void (*)(void) type, Func a table element",
    "proc": "name the action",
    "routine": "name the action",
    "fn": "name the action",
    "cb": "name the action",
    "data": "the game noun",
    "info": "the game noun",
    "work": "the game noun",
    "misc": "the game noun",
    "rec": "the game noun",
    "buf": "buffer",
    "idx": "index",
    "cnt": "count",
    "num": "count or id",
    "tmp": "the value it holds",
    "temp": "the value it holds",
    "cur": "current",
    "ptr": "the pointee's game noun",
    "obj": "the object's game noun",
    "object": "the object's game noun",
    "ctrl": "the role it controls",
    "mgr": "the role it manages",
    "spr": "sprite",
    "chara": "character",
    "monster": "enemy",
    "goods": "item",
    "spell": "magic or ability",
    "fx": "effect",
    "render": "draw",
    "lookup": "find or get",
    "fetch": "load or get",
    "put": "set or write",
    "make": "create or alloc",
    "kill": "free",
    "delete": "remove",
    "destroy": "free or remove",
    "check": "is, has, can, test or find",
    "handle": "dispatch, run or update",
    "finish": "end",
    "store": "set or write",
    "kind": "type",
    "class": "type",
    "bits": "flags",
    "len": "length",
    "colour": "color",
    "amount": "count or value",
    "quantity": "count or value",
}

# A tag with one spelling per system; a new name with the left side takes the right side.
PREFIXES = (
    (re.compile(r"^World_"), "WorldMap_"),
    (re.compile(r"^Plchar"), "PlChar"),
    (re.compile(r"^PAD_"), "INPUT_"),
    (re.compile(r"^Mem_"), "SYS_"),
    (re.compile(r"^Matrix_"), "MATH_"),
    (re.compile(r"^Fish_"), "Fishing_"),
    (re.compile(r"^CD_"), "EMI_ or DISC_"),
)


def split_words(name: str) -> list[str]:
    """Split an identifier at underscores and camel humps, lower case."""
    return [token.lower() for chunk in name.split("_") for token in WORD.findall(chunk)]


def rejected_reason(name: str) -> str | None:
    """Why a new identifier breaks the vocabulary, or ``None`` when it follows it."""
    for pattern, replacement in PREFIXES:
        if pattern.search(name):
            return f"the system tag is {replacement}"
    for word in split_words(name):
        if word in REJECTED:
            return REJECTED[word]
    return None


def rejected_names(text: str) -> set[str]:
    """Identifiers in ``text`` that use a rejected word or an old tag."""
    return {
        m.group()
        for m in TOKEN.finditer(text)
        if m.lastgroup == "ident"
        and not ADDRESS.fullmatch(m.group())
        and rejected_reason(m.group()) is not None
    }


def in_ref(ref: str, name: str) -> bool:
    """Whether ``name`` occurs as a word in the tracked tree at ``ref``."""
    found = subprocess.run(
        ["git", "grep", "-q", "-w", "-F", "-e", name, ref, "--", "."],
        check=False,
        capture_output=True,
    )
    return found.returncode == 0


def unnamed_parameters(text: str) -> set[str]:
    """``argN`` identifiers in code; comments, strings and hex literals are skipped."""
    return {
        m.group()
        for m in TOKEN.finditer(text)
        if m.lastgroup == "ident" and UNNAMED.fullmatch(m.group())
    }


def offset_macros(text: str) -> set[str]:
    """``FIELD``, ``SP_REF`` and ``SP`` uses in code; comments and strings are skipped."""
    if OFFSET_DEFINITION.match(text):
        return set()
    return {m.group(1) for m in OFFSET_MACRO.finditer(SKIP.sub(" ", text))}


def macro_counts(text: str) -> dict[str, int]:
    """``FIELD``/``SP_REF``/``SP`` uses in code, per macro name."""
    counts: dict[str, int] = {}
    for match in OFFSET_MACRO.finditer(SKIP.sub(" ", text)):
        counts[match.group(1)] = counts.get(match.group(1), 0) + 1
    return counts


def changed_paths(ref: str) -> list[str]:
    """The paths under include/ or src/ a change touches."""
    out = subprocess.run(
        ["git", "diff", "--name-only", f"{ref}...HEAD", "--", *ROOTS],
        check=False,
        capture_output=True,
        text=True,
    ).stdout
    return [path for path in out.split() if path]


def base_text(ref: str, path: str) -> str:
    """The file at ``path`` as it is in the base revision; empty when new."""
    result = subprocess.run(
        ["git", "show", f"{ref}:{path}"],
        check=False,
        capture_output=True,
        text=True,
    )
    return result.stdout if result.returncode == 0 else ""


def added_lines(ref: str):
    """Yield (path, line, text) for each line a change adds under include/ or src/."""
    diff = subprocess.run(
        ["git", "diff", "-U0", f"{ref}...HEAD", "--", *ROOTS],
        check=False,
        capture_output=True,
        text=True,
    ).stdout
    path, line = "", 0
    for row in diff.splitlines():
        if row.startswith("+++ b/"):
            path = row[6:]
        elif row.startswith("@@"):
            m = re.search(r"\+(\d+)", row)
            line = int(m.group(1)) if m else 0
        elif row.startswith("+") and not row.startswith("+++"):
            yield path, line, row[1:]
            line += 1
        elif row.startswith(" "):
            line += 1


def offenders(text: str) -> set[str]:
    """Identifiers in ``text`` that hold an address and are not a default tool name."""
    found = set()
    for m in TOKEN.finditer(text):
        if m.lastgroup != "ident":
            continue
        name = m.group()
        run = ADDRESS.search(name)
        if (
            run
            and any(c.isdigit() for c in run.group())
            and not DEFAULT.fullmatch(name)
        ):
            found.add(name)
    return found


def tree_entries() -> set[str]:
    files = subprocess.run(
        ["git", "ls-files", *ROOTS], capture_output=True, text=True, check=True
    ).stdout.split()
    entries = set()
    for path in files:
        if path.endswith(SUFFIXES):
            text = Path(path).read_text(encoding="utf-8", errors="ignore")
            entries |= {f"{path}\t{name}" for name in offenders(text)}
    return entries


def baseline_entries() -> set[str]:
    if not BASELINE.is_file():
        return set()
    return {
        line
        for line in BASELINE.read_text().splitlines()
        if line and not line.startswith("#")
    }


def main(argv: list[str]) -> int:
    if argv and argv[0] in ("-h", "--help"):
        print(__doc__.strip())
        return 0
    if argv and argv[0] == "--diff":
        if len(argv) != 2:
            print("usage: python3 tools/check_names.py --diff REF", file=sys.stderr)
            return 2
        bad = 0
        seen: set[str] = set()
        for path, line, text in added_lines(argv[1]):
            for name in unnamed_parameters(text):
                print(
                    f"{path}:{line}: {name}: an unnamed parameter; rename it to what it holds",
                    file=sys.stderr,
                )
                bad = 1
            if path.startswith(("include/psyq", "include/psx")):
                continue
            if path == "include/common/util.h":
                continue  # the generic helpers may name arrays and bits directly
            for name in rejected_names(text):
                if name in seen or in_ref(argv[1], name):
                    continue
                seen.add(name)
                print(
                    f"{path}:{line}: {name}: {rejected_reason(name)} (new name)",
                    file=sys.stderr,
                )
                bad = 1
        for path in changed_paths(argv[1]):
            before = macro_counts(base_text(argv[1], path))
            after_text = Path(path).read_text(encoding="utf-8", errors="replace")
            after = macro_counts(after_text)
            grown = {name: after[name] - before.get(name, 0) for name in after}
            for name, extra in sorted(grown.items()):
                if extra <= 0:
                    continue
                where = [
                    f"{path}:{number}"
                    for number, text in enumerate(after_text.splitlines(), 1)
                    if name in offset_macros(text)
                ]
                print(
                    f"{where[0]}: {name}(): {extra} new offset access(es); "
                    "write the member of the record or of the scratchpad view",
                    file=sys.stderr,
                )
                bad = 1
        if bad:
            print(f"check-names: names against {argv[1]}", file=sys.stderr)
            return 1
        print(
            f"check-names: no new rejected names, unnamed parameters or offset accesses against {argv[1]}"
        )
        return 0
    now = tree_entries()
    if argv == ["--write"]:
        BASELINE.write_text(
            "# Identifiers that still carry an address (file, name). check_names.py only lets this shrink.\n"
            + "".join(f"{e}\n" for e in sorted(now))
        )
        print(f"check-names: wrote {len(now)} entries to {BASELINE}")
        return 0
    base = baseline_entries()
    new, gone = sorted(now - base), sorted(base - now)
    for entry in new:
        print(
            f"{entry.replace(chr(9), ': ')}: a name must not carry an address",
            file=sys.stderr,
        )
    for entry in gone:
        print(
            f"{BASELINE}: {entry.replace(chr(9), ': ')} no longer exists; delete the line",
            file=sys.stderr,
        )
    if new or gone:
        print(f"check-names: {len(new)} new, {len(gone)} stale", file=sys.stderr)
        return 1
    print(f"check-names: no new address names ({len(base)} left to rename)")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
