#!/usr/bin/env python3
"""Mark each member of a tools/chunks.py file as asm, shared or pasted.

    tools/classify.py chunks.tsv classified.tsv

A member is shared when its body sits in an included header or is a call of a few lines at most,
pasted when its own source holds the body. A group stays when two or more copies are asm or pasted,
or one is pasted beside a shared one: the work left to fold into one body.
"""

from __future__ import annotations

import re
import sys
from functools import lru_cache
from pathlib import Path

from bof3.source.index import load_index

ROOT = Path(__file__).resolve().parent.parent
SHARED_LINES = 3


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


def main() -> None:
    if len(sys.argv) != 3:
        sys.exit(__doc__)
    idx = {(f.image, f.name): f for f in load_index(ROOT, False)}
    rows = [ln.split("\t") for ln in Path(sys.argv[1]).read_text().splitlines()][1:]
    with open(sys.argv[2], "w") as out:
        out.write("weight\tinsns\tfuncs\timages\tasm\tpasted\tshared\tmembers\n")
        for r in rows:
            ks = []
            for m in r[5].split(" ; "):
                mm = re.match(r"(.+?):(\w+)\+0x[0-9A-F]+\[(\w+)\]", m)
                ks.append(kind(idx, *mm.groups()) if mm else "?")
            a, p, s = ks.count("asm"), ks.count("pasted"), ks.count("shared")
            if a + p >= 2 or (p and s):
                out.write("\t".join([*r[:4], str(a), str(p), str(s), r[5]]) + "\n")


if __name__ == "__main__":
    main()
