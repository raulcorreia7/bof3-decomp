#!/usr/bin/env python3
"""Compare prototypes, definitions and calls across the C tree.

    tools/sigs.py scan [--kind KIND] [PATH...]   one row per problem, counts on stderr

`scan` kinds: ret_mismatch, argc_mismatch, argtype_mismatch, proto_unspecified_args,
param_name_differs, proto_placeholder_name, def_placeholder_name, implicit_decl, call_argc,
call_through_cast, return_cast, void_result_read, wide_ret_all_callers_cast.
"""

from __future__ import annotations

import argparse
import collections
import sys
from pathlib import Path

from bof3.source import ctext, decls

ROOT = Path(__file__).resolve().parent.parent


def load_tree() -> decls.Tree:
    """Read every tracked C file under ``src/`` and ``include/``."""
    return decls.Tree({name: ctext.read(ROOT, name) for name in ctext.tracked_c(ROOT)})


def scan(args: argparse.Namespace) -> int:
    """Print one tab-separated row per problem."""
    rows = decls.problems(load_tree())
    prefixes = tuple(args.paths)
    counts: collections.Counter[str] = collections.Counter()
    for row in rows:
        if args.kind and row.kind not in args.kind:
            continue
        if prefixes and not row.file.startswith(prefixes):
            continue
        counts[row.kind] += 1
        print(row.kind, row.name, row.file, row.line, row.detail, sep="\t")
    for kind, count in sorted(counts.items()):
        print(f"{kind}\t{count}", file=sys.stderr)
    return 0


def main(argv: list[str] | None = None) -> int:
    """Run one verb."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    verbs = parser.add_subparsers(dest="verb", required=True)
    one = verbs.add_parser("scan", help="list problems")
    one.add_argument("--kind", action="append", help="only this kind (repeatable)")
    one.add_argument("paths", nargs="*", help="only rows in files under these paths")
    one.set_defaults(run=scan)
    args = parser.parse_args(argv)
    return args.run(args)


if __name__ == "__main__":
    raise SystemExit(main())
