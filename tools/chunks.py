#!/usr/bin/env python3
"""Find repeated instruction runs (chunks) inside functions across every built image.

    tools/chunks.py [-w 12] [-n 3] [-o chunks.jsonl]

A chunk is a run of at least W instructions whose shape (opcode plus register fields; immediates,
offsets and jump targets masked) recurs in N or more distinct function bodies. Overlapping windows
are merged into maximal runs. Byte-identical whole functions count once. Writes one JSON object
per line, with `members` naming the functions of each group. Reads the function index
of the built images (see tools/dups.py); run `meson compile -C build/meson` first. Feed the output
to tools/classify.py.
"""

from __future__ import annotations

import argparse
import collections
import json
import sys
from pathlib import Path

from bof3.source.index import load_index

ROOT = Path(__file__).resolve().parent.parent


def shape(w: int) -> int:
    """Return the instruction word with its immediate, shift amount or jump target masked."""
    if w == 0:
        return 0
    op = w >> 26
    if op == 0:
        # R-type: keep the registers, and the shift amount only for shifts
        return w & ~(0x1F << 6) if (w & 63) not in (0, 2, 3) else w
    if op in (2, 3):
        return op << 26  # j/jal: drop the target
    return w & 0xFFFF0000  # I-type: keep rs/rt, drop the immediate


def write_rows(path: str, rows: list[dict]) -> None:
    """Write the chunk rows as JSON Lines."""
    with open(path, "w", encoding="utf-8") as out:
        for row in rows:
            out.write(json.dumps(row, ensure_ascii=False) + "\n")


def main() -> None:
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument(
        "-w", type=int, default=12, help="minimum run length in instructions"
    )
    ap.add_argument(
        "-n", type=int, default=3, help="minimum number of distinct functions"
    )
    ap.add_argument("-o", default="chunks.jsonl", help="output file")
    a = ap.parse_args()
    funcs, seen = [], set()
    for f in load_index(ROOT, False):
        if f.status == "LIB" or f.sha1 in seen or len(f.words) < a.w:
            continue
        seen.add(f.sha1)
        funcs.append(f)
    width = a.w
    hits = collections.defaultdict(set)  # window hash -> {(func idx, offset)}
    shapes = [tuple(shape(w) for w in f.words) for f in funcs]
    for i, s in enumerate(shapes):
        for o in range(len(s) - width + 1):
            win = s[o : o + width]
            if sum(1 for x in win if x) < width * 3 // 4:
                continue  # skip nop-padded runs
            hits[hash(win)].add((i, o))
    keep = {h: v for h, v in hits.items() if len({i for i, _ in v}) >= a.n}
    mark = collections.defaultdict(set)
    for v in keep.values():
        for i, o in v:
            mark[i].add(o)
    groups = collections.defaultdict(
        list
    )  # merge consecutive windows into maximal runs
    for i, offs in mark.items():
        offs = sorted(offs)
        start = prev = offs[0]
        for o in [*offs[1:], None]:
            if o is not None and o == prev + 1:
                prev = o
                continue
            groups[hash(shapes[i][start : start + width])].append(
                (i, start, prev - start + width)
            )
            if o is not None:
                start = prev = o
    rows = []
    for mem in groups.values():
        fs = {i for i, _, _ in mem}
        if len(fs) < a.n:
            continue
        length = min(n for _, _, n in mem)
        imgs = {funcs[i].image for i in fs}
        lifted = sum(1 for i in fs if funcs[i].status == "C")
        rows.append(
            {
                "weight": length * (len(fs) - 1),
                "insns": length,
                "funcs": len(fs),
                "images": len(imgs),
                "lifted": lifted,
                "members": [
                    f"{funcs[i].image}:{funcs[i].name}+0x{o * 4:X}[{funcs[i].status}]"
                    for i, o, _ in sorted(mem, key=lambda m: funcs[m[0]].status)[:12]
                ],
            }
        )
    rows.sort(key=lambda r: -r["weight"])
    write_rows(a.o, rows)
    print(
        f"functions {len(funcs)}, chunk groups {len(rows)} (>= {width} insns in >= {a.n} functions)",
        file=sys.stderr,
    )


if __name__ == "__main__":
    main()
