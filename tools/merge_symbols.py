#!/usr/bin/env python3
"""Git merge driver for `config/symbols/<image>.toml`: `merge_symbols.py BASE OURS THEIRS` writes OURS."""

import re
import sys
from pathlib import Path

ADDR = re.compile(r"addr = 0x([0-9A-Fa-f]+)")
TAIL = "\0"


def parse(path: str) -> tuple[list[str], dict[str, dict[str, str]]]:
    tables: dict[str, dict[str, str]] = {}
    head: list[str] = []
    table = None
    notes: list[str] = []
    for line in Path(path).read_text(encoding="utf-8").splitlines():
        if line.startswith("["):
            if table is not None and notes:
                table[TAIL] = "\n".join(notes)
            table = tables.setdefault(line, {})
            notes = []
        elif table is None:
            head.append(line)
        elif line.startswith("#") or not line.strip():
            notes.append(line)
        else:
            table[line.split(" = ", 1)[0]] = "\n".join([*notes, line])
            notes = []
    if table is not None and notes:
        table[TAIL] = "\n".join(notes)
    return head, tables


def order(name: str, row: str) -> int:
    return 1 << 64 if name == TAIL else int(ADDR.search(row)[1], 16)


def main(base: str, ours: str, theirs: str) -> int:
    head, mine = parse(ours)
    old, new = parse(base)[1], parse(theirs)[1]
    conflict = False
    for title in sorted({*mine, *new}):
        rows, a, b, o = (
            mine.setdefault(title, {}),
            mine[title].copy(),
            new.get(title, {}),
            old.get(title, {}),
        )
        for name in {*a, *b}:
            ours_row, their_row, base_row = a.get(name), b.get(name), o.get(name)
            if ours_row == their_row or their_row == base_row:
                continue
            if ours_row == base_row:
                rows.pop(name, None) if their_row is None else rows.__setitem__(
                    name, their_row
                )
            else:
                conflict = True
    out = list(head)
    for title in sorted(mine) if mine and list(mine) == sorted(mine) else mine:
        out += [
            title,
            *(
                row
                for _, row in sorted(mine[title].items(), key=lambda item: order(*item))
            ),
        ]
    Path(ours).write_text("\n".join(out).rstrip("\n") + "\n", encoding="utf-8")
    return int(conflict)


if __name__ == "__main__":
    sys.exit(main(*sys.argv[1:4]))
