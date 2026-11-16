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
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
PATH = ROOT / "config/attempts.jsonl"
REF = re.compile(r"^[^@\s]+@0x[0-9A-F]{8}$")


def read(path: Path) -> list[str]:
    """The rows of `path`, one line each."""
    text = path.read_text(encoding="utf-8") if path.exists() else ""
    return [line for line in text.splitlines() if line.strip()]


def write(path: Path, lines: list[str]) -> None:
    """Write `lines` as one row per line."""
    path.write_text("\n".join(lines) + "\n", encoding="utf-8")


def function_of(line: str) -> str:
    """The `function` of one row."""
    return json.loads(line)["function"]


def score(text: str) -> object:
    """The value of a `--score` text: a number, `null`, or the text."""
    try:
        value = json.loads(text)
    except json.JSONDecodeError:
        return text
    return value if value is None or isinstance(value, (int, float)) else text


def spelling(row: dict, like: str | None) -> str:
    """`row` as one line, spelled as `like` spells its own object."""
    if like is not None and like == json.dumps(json.loads(like), separators=(",", ":")):
        return json.dumps(row, separators=(",", ":"))
    return json.dumps(row)


def place(lines: list[str], function: str) -> int:
    """The index a row for `function` goes to: after its last row, else its sorted place."""
    last = None
    for index, line in enumerate(lines):
        other = function_of(line)
        if other == function:
            last = index
        elif last is None and other > function:
            return index
    return len(lines) if last is None else last + 1


def add(path: Path, function: str, tried: str, first_diff: str, value: object) -> int:
    """Insert one row and return its 1-based line."""
    row = {
        "function": function,
        "tried": tried,
        "first_diff": first_diff,
        "score": value,
    }
    lines = read(path)
    index = place(lines, function)
    like = lines[index - 1] if index else (lines[0] if lines else None)
    lines.insert(index, spelling(row, like))
    write(path, lines)
    return index + 1


def sort(path: Path) -> None:
    """Put the rows in `function` order, each function's rows in the order they hold."""
    write(path, distinct(sorted(read(path), key=function_of)))


def distinct(lines: list[str]) -> list[str]:
    """`lines` without a row that repeats an earlier one."""
    seen: set[str] = set()
    kept: list[str] = []
    for line in lines:
        row = json.dumps(json.loads(line), sort_keys=True)
        if row not in seen:
            seen.add(row)
            kept.append(line)
    return kept


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
        print(f"{shown(args.path)}: {len(read(args.path))} rows in function order")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
