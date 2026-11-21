#!/usr/bin/env python3
"""Fail when a prototype is not the signature of the function it declares."""

from __future__ import annotations

from bof3.core.paths import ROOT
from bof3.source import ctext, decls


def main() -> int:
    """Print each differing prototype; return 1 when there is one."""
    tree = decls.Tree({name: ctext.read(ROOT, name) for name in ctext.tracked_c(ROOT)})
    rows = decls.signature_rows(tree)
    for row in rows:
        print(f"check-signatures: {row.file}:{row.line}: {row.name}: {row.detail}")
    if rows:
        print(
            "check-signatures: make the prototype the owner's, write `T name();` with the owner's"
            " return type, or add a `sig-kept: <reason>` comment above it"
        )
    return 1 if rows else 0


if __name__ == "__main__":
    raise SystemExit(main())
