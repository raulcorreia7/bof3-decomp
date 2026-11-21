#!/usr/bin/env python3
"""Keep `config/attempts.jsonl` in function order.

    tools/attempts.py add --function <target>@0x<ADDR> --tried TEXT [--first-diff TEXT]
                          [--score TEXT] [--path FILE]
    tools/attempts.py sort [--path FILE]

A row carries `function`, `tried`, `first_diff`, `score` in that order, in the spelling of the row
it joins. The rows stay in `function` order, so two branches that add rows merge without a conflict:
a row for a function the file holds goes after that function's last row, whose attempt order stays,
and a new function goes to its sorted place. `sort` restores the order after a merge that
interleaved rows, and drops a row that repeats one already in the file.

`--score` writes a JSON number for a number, `null` for `null`, and the text otherwise.
"""

from __future__ import annotations

import argparse
import re
import sys
from pathlib import Path

from bof3.adapters.attempts import PATH as ROW_PATH
from bof3.adapters.attempts import read_lines, write_lines
from bof3.attempts import Attempt, insert, score
from bof3.attempts import sort as sort_lines
from bof3.core.paths import ROOT

PATH = ROOT / ROW_PATH
REF = re.compile(r"^[^@\s]+@0x[0-9A-F]{8}$")


def add(path: Path, function: str, tried: str, first_diff: str, value: object) -> int:
    """Insert one row and return its 1-based line."""
    lines = read_lines(path)
    index = insert(lines, Attempt(function, tried, first_diff, value))
    write_lines(path, lines)
    return index


def sort(path: Path) -> None:
    """Put the rows in `function` order, each function's rows in the order they hold."""
    write_lines(path, sort_lines(read_lines(path)))


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
    adder = verbs.add_parser("add", help="insert one row at its place")
    adder.add_argument("--function", required=True, help="<target>@0x<ADDR>")
    adder.add_argument("--tried", required=True, help="what was tried")
    adder.add_argument("--first-diff", default="", help="the first difference")
    adder.add_argument("--score", default="null", help="a number, null, or the text")
    adder.add_argument("--path", type=Path, default=PATH)
    sorter = verbs.add_parser("sort", help="restore function order, drop repeated rows")
    sorter.add_argument("--path", type=Path, default=PATH)
    args = parser.parse_args(argv)
    if args.verb == "add":
        if not REF.match(args.function):
            print(
                f"attempts: --function {args.function} is not <target>@0x<ADDR>",
                file=sys.stderr,
            )
            return 2
        line = add(
            args.path, args.function, args.tried, args.first_diff, score(args.score)
        )
        print(f"{shown(args.path)}:{line}: {args.function}")
    else:
        sort(args.path)
        print(
            f"{shown(args.path)}: {len(read_lines(args.path))} rows in function order"
        )
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
