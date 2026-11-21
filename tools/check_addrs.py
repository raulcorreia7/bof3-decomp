#!/usr/bin/env python3
"""Fail when a symbol address that config/symbols/<image>.toml records at REF is gone at HEAD.

Every function and data address found so far stays findable: a rename keeps its row's
`addr`, and a global folded into a record keeps its old address as an `alias = true` row
whose `source` names the member that holds it now. The check compares (target, addr) pairs,
so renames, retypes and moved rows pass; only a vanished address fails. REF is reduced to its
merge base with HEAD, so rows that landed on REF after the branch point are not counted as lost.

Usage: python3 tools/check_addrs.py REF [HEAD]
"""

import sys
from pathlib import Path

from bof3.adapters.config import symbols_text
from bof3.adapters.git import merge_base
from bof3.symbols import parse


def addresses(rev):
    text = symbols_text(Path.cwd(), rev)
    found = {}
    for target, rows in parse(text).items():
        for name, row in rows.items():
            if isinstance(row, dict) and "addr" in row:
                found[(target, row["addr"])] = name
    return found


def main(argv):
    if len(argv) == 2 and argv[1] in ("-h", "--help"):
        print(__doc__.strip())
        return 0
    if len(argv) not in (2, 3):
        print(__doc__.strip(), file=sys.stderr)
        return 2
    ref, head = argv[1], argv[2] if len(argv) == 3 else "HEAD"
    base = merge_base(ref, head)
    before, after = addresses(base), addresses(head)
    lost = sorted(key for key in before if key not in after)
    for target, addr in lost:
        print(
            f"{target}: 0x{addr:08X} ({before[(target, addr)]}) has no row; "
            "keep it as an alias row naming its new member"
        )
    if lost:
        print(f"check-addrs: {len(lost)} address(es) lost against {ref}")
        return 1
    print(f"check-addrs: all {len(before)} addresses kept against {ref}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
