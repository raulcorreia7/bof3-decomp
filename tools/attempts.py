#!/usr/bin/env python3
"""Append a row to `config/attempts.jsonl`; the file is append-only.

    tools/attempts.py add --function <target>@0x<ADDR> --tried TEXT [--first-diff TEXT]
                          [--score TEXT] [--path FILE]

A row carries `function`, `tried`, `first_diff`, `score` in that order, in the spelling of the last
row. `--score` writes a JSON number for a number, `null` for `null`, and the text otherwise.
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

from bof3.adapters.attempts import PATH as ROW_PATH
from bof3.adapters.attempts import read_lines, write_lines
from bof3.attempts import Attempt, score, spelling
from bof3.core.paths import ROOT

PATH = ROOT / ROW_PATH
REF = re.compile(r"^[^@\s]+@0x[0-9A-F]{8}$")


def add(path: Path, function: str, tried: str, first_diff: str, value: object) -> int:
    """Append one row and return its 1-based line."""
    lines = read_lines(path)
    lines.append(
        spelling(
            Attempt(function, tried, first_diff, value), lines[-1] if lines else None
        )
    )
    write_lines(path, lines)
    return len(lines)


def shown(path: Path) -> str:
    """`path` relative to the tree, for a message."""
    try:
        return str(path.relative_to(ROOT))
    except ValueError:
        return str(path)


def main(argv: list[str] | None = None) -> int:
    parser = argparse.ArgumentParser(
        prog="tools/attempts.py",
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    verbs = parser.add_subparsers(dest="verb", required=True)
    adder = verbs.add_parser("add", help="append one row")
    adder.add_argument("--function", required=True, help="<target>@0x<ADDR>")
    adder.add_argument("--tried", required=True, help="what was tried")
    adder.add_argument("--first-diff", default="", help="the first difference")
    adder.add_argument("--score", default="null", help="a number, null, or the text")
    adder.add_argument("--path", type=Path, default=PATH)
    args = parser.parse_args(argv)
    if not REF.match(args.function):
        print(
            f"attempts: --function {args.function} is not <target>@0x<ADDR>",
            file=sys.stderr,
        )
        return 2
    line = add(args.path, args.function, args.tried, args.first_diff, score(args.score))
    print(f"{shown(args.path)}:{line}: {args.function}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
