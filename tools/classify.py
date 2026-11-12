#!/usr/bin/env python3
"""Mark each member of a tools/chunks.py file as asm, shared or pasted.

    tools/classify.py chunks.jsonl classified.jsonl

A member is shared when its body sits in an included header or is a call of a few lines at most,
pasted when its own source holds the body. A group stays when two or more copies are asm or pasted,
or one is pasted beside a shared one: the work left to fold into one body. Both files are JSON
Lines; the output adds the asm, pasted and shared counts to each kept group.
"""

from __future__ import annotations

import json
import re
import sys
from collections.abc import Callable
from functools import lru_cache
from pathlib import Path

from bof3.source.index import load_index

ROOT = Path(__file__).resolve().parent.parent
SHARED_LINES = 3
MEMBER = re.compile(r"(.+?):(\w+)\+0x[0-9A-F]+\[(\w+)\]")


@lru_cache(None)
def text(path: str) -> str:
    """Return the source text of path, or empty when it is missing."""
    p = Path(path) if path else None
    return p.read_text(errors="replace") if p and p.exists() else ""


def kind(idx: dict, image: str, name: str, status: str) -> str:
    """Return asm, shared or pasted for one chunk member."""
    if status == "ASM":
        return "asm"
    f = idx.get((image, name))
    t = text(f.src) if f else ""
    m = re.search(rf"^[^\n;]*\b{re.escape(name)}\s*\([^;{{]*\)\s*\{{", t, re.M)
    if not m:
        return "shared"
    depth, j = 0, m.end() - 1
    for j in range(m.end() - 1, len(t)):
        depth += t[j] == "{"
        depth -= t[j] == "}"
        if depth == 0:
            break
    body = [
        ln
        for ln in t[m.end() : j].splitlines()
        if ln.strip() and not ln.strip().startswith(("/*", "*"))
    ]
    return "shared" if len(body) <= SHARED_LINES else "pasted"


def classify_rows(
    rows: list[dict], classify: Callable[[str, str, str], str]
) -> list[dict]:
    """Return the groups worth folding, with each member's kind counted."""
    result = []
    for row in rows:
        kinds = []
        for member in row["members"]:
            m = MEMBER.match(member)
            kinds.append(classify(*m.groups()) if m else "?")
        asm, pasted, shared = (
            kinds.count("asm"),
            kinds.count("pasted"),
            kinds.count("shared"),
        )
        if asm + pasted >= 2 or (pasted and shared):
            result.append(
                {
                    "weight": row["weight"],
                    "insns": row["insns"],
                    "funcs": row["funcs"],
                    "images": row["images"],
                    "asm": asm,
                    "pasted": pasted,
                    "shared": shared,
                    "members": row["members"],
                }
            )
    return result


def main() -> None:
    if sys.argv[1:] in (["-h"], ["--help"]):
        print(__doc__.strip())
        return
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    idx = {(f.image, f.name): f for f in load_index(ROOT, False)}
    rows = [
        json.loads(line)
        for line in Path(sys.argv[1]).read_text(encoding="utf-8").splitlines()
        if line.strip()
    ]
    kept = classify_rows(
        rows, lambda image, name, status: kind(idx, image, name, status)
    )
    with open(sys.argv[2], "w", encoding="utf-8") as out:
        for row in kept:
            out.write(json.dumps(row, ensure_ascii=False) + "\n")


if __name__ == "__main__":
    main()
