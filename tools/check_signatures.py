#!/usr/bin/env python3
"""Fail when a prototype is not the signature of the function it declares.

A prototype is fine when it has the owner's return type and parameter types, or is the
non-prototype form with the owner's return type (`void name();`, for a retail unit that had no
prototype), or has a `sig-kept:` comment on the line above that says why the retail bytes need the
difference. The owner is the definition that the declaring unit sees, the one in the same image,
or the engine's.

Usage: python3 tools/check_signatures.py
"""

from __future__ import annotations

from pathlib import Path

from bof3.source import ctext, decls

ROOT = Path(__file__).resolve().parent.parent


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
