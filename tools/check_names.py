#!/usr/bin/env python3
"""Fail when an invented identifier in include/ or src/ carries an 8-digit hex address.

A name says what a thing is for the game, never where it lives. The default tool names are the
only identifiers allowed to hold an address: ``func_<ADDR>``, ``D_<ADDR>``, ``L<ADDR>``,
``jtbl_*``, ``jpt_*`` and ``s_gap_*``. Comments, strings and config/symbols.toml text are not
checked.

The check is a ratchet. ``config/address_names.txt`` lists the offenders that exist today as
``<file><TAB><identifier>``. A name that is not on the list fails, and so does a listed entry
that no longer occurs, so the list only shrinks. Rename the identifier, then delete its line.

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


def unnamed_parameters(text: str) -> set[str]:
    """``argN`` identifiers in code; comments, strings and hex literals are skipped."""
    return {
        m.group()
        for m in TOKEN.finditer(text)
        if m.lastgroup == "ident" and UNNAMED.fullmatch(m.group())
    }


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
        for path, line, text in added_lines(argv[1]):
            for name in unnamed_parameters(text):
                print(
                    f"{path}:{line}: {name}: an unnamed parameter; rename it to what it holds",
                    file=sys.stderr,
                )
                bad = 1
        if bad:
            print(f"check-names: unnamed parameters against {argv[1]}", file=sys.stderr)
            return 1
        print(f"check-names: no unnamed parameters against {argv[1]}")
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
