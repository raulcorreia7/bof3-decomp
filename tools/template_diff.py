#!/usr/bin/env python3
"""Find the matched C function that an assembly function resembles, and show how they differ.

    tools/template_diff.py TARGET@NAME                     closest templates, diff against the best
    tools/template_diff.py TARGET@NAME TARGET@NAME         diff against the template you name

A reference is `TARGET@NAME` or `TARGET@0xADDRESS`, for example
`emi/plchar/plp016/00@func_801CF610`. Only instructions that differ print, aligned on opcodes:
`~` same opcode, other operands; `-` only in the template; `+` only in the target. Offsets are
bytes from each function start; jump targets always differ. `--jsonl` writes every line as an
object instead, with `kind` naming the line. The templates are lifted functions
(status C) of the built images ({cache}); run `meson compile -C build/meson` first and add
--rebuild after a build. Candidate search needs `rapidfuzz` (`tools/setup.sh --matching`).
"""

from __future__ import annotations

import argparse
import difflib
import json
import subprocess
import tempfile
from pathlib import Path

from bof3.source.index import CACHE, OBJDUMP, Func, find, load_index, opcode_string

ROOT = Path(__file__).resolve().parent.parent


def disassemble(words: tuple[int, ...]) -> list[str]:
    """Return one instruction text per word."""
    with tempfile.TemporaryDirectory() as scratch:
        blob = Path(scratch) / "f.bin"
        blob.write_bytes(b"".join(w.to_bytes(4, "little") for w in words))
        out = subprocess.run(
            [
                str(ROOT / OBJDUMP),
                "-D",
                "-b",
                "binary",
                "-m",
                "mips:3000",
                "-EL",
                "-z",
                str(blob),
            ],
            capture_output=True,
            text=True,
            check=True,
        ).stdout
    lines = [
        ln.split("\t", 2)[-1].strip()
        for ln in out.splitlines()
        if ln[:1] == " " and ":\t" in ln
    ]
    return lines[: len(words)]


def candidates(funcs: list[Func], target: Func, top: int) -> list[tuple[float, Func]]:
    """Return the ``top`` lifted functions closest to ``target`` by opcode sequence."""
    try:
        from rapidfuzz import process
        from rapidfuzz.distance import Indel
    except ImportError:
        raise SystemExit(
            "template_diff: needs rapidfuzz. Run: tools/setup.sh --matching"
        ) from None
    pool = [f for f in funcs if f.status == "C" and f is not target]
    wanted = opcode_string(target.words)
    scored = process.extract(
        wanted,
        [opcode_string(f.words) for f in pool],
        scorer=Indel.normalized_similarity,
        limit=top,
    )
    return [(score, pool[i]) for _seq, score, i in scored]


def align_rows(a: list[str], b: list[str]) -> list[dict]:
    """Return the differing instructions as row objects, aligned on opcodes."""

    def opcode(s: str) -> str:
        return s.split()[0] if s else ""

    matcher = difflib.SequenceMatcher(
        None, [opcode(x) for x in a], [opcode(x) for x in b], autojunk=False
    )
    rows = []
    for tag, i1, i2, j1, j2 in matcher.get_opcodes():
        if tag == "equal":
            for k in range(i2 - i1):
                if a[i1 + k] != b[j1 + k]:
                    rows.append(
                        {
                            "kind": "same_opcode",
                            "template_offset": 4 * (i1 + k),
                            "template": a[i1 + k],
                            "target_offset": 4 * (j1 + k),
                            "target": b[j1 + k],
                        }
                    )
            continue
        for k in range(i1, i2):
            rows.append(
                {
                    "kind": "template_only",
                    "template_offset": 4 * k,
                    "template": a[k],
                    "target_offset": None,
                    "target": None,
                }
            )
        for k in range(j1, j2):
            rows.append(
                {
                    "kind": "target_only",
                    "template_offset": None,
                    "template": None,
                    "target_offset": 4 * k,
                    "target": b[k],
                }
            )
    return rows


def rows_for(template: Func, target: Func) -> tuple[list[dict], int, int]:
    """Return the differing rows and the instruction counts of both functions."""
    a, b = disassemble(template.words), disassemble(target.words)
    return align_rows(a, b), len(a), len(b)


def show(template: Func, target: Func) -> int:
    """Print the differing instructions; return their count."""
    rows, a, b = rows_for(template, target)
    for row in rows:
        if row["kind"] == "same_opcode":
            print(
                f"~ +0x{row['template_offset']:03X} {row['template']:40} "
                f"| +0x{row['target_offset']:03X} {row['target']}"
            )
        elif row["kind"] == "template_only":
            print(f"- +0x{row['template_offset']:03X} {row['template']}")
        else:
            print(f"+ +0x{row['target_offset']:03X} {row['target']}")
    print(f"{len(rows)} differing of {a} template and {b} target instructions")
    return len(rows)


def main(argv: list[str] | None = None) -> int:
    """Pick a template, then print the diff."""
    parser = argparse.ArgumentParser(
        description=__doc__.format(cache=CACHE),
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    parser.add_argument("target", help="the function to explain, TARGET@NAME")
    parser.add_argument(
        "template", nargs="?", help="the template, TARGET@NAME (default: the closest)"
    )
    parser.add_argument(
        "--rebuild", action="store_true", help="rebuild the function index first"
    )
    parser.add_argument("--jsonl", action="store_true", help="one JSON object per line")
    args = parser.parse_args(argv)
    funcs = load_index(ROOT, args.rebuild)
    target = find(funcs, args.target)
    if args.template:
        template = find(funcs, args.template)
    else:
        ranked = candidates(funcs, target, 5)
        for score, f in ranked:
            if args.jsonl:
                print(
                    json.dumps(
                        {
                            "kind": "candidate",
                            "similarity": score,
                            "template": f"{f.image}@{f.name}",
                            "size": f.size,
                        },
                        ensure_ascii=False,
                    )
                )
            else:
                print(f"# {score:.3f} {f.image}@{f.name} ({f.size} bytes)")
        if not ranked:
            raise SystemExit("template_diff: no lifted function to compare with")
        template = ranked[0][1]
    pair = {
        "kind": "pair",
        "template": f"{template.image}@{template.name}",
        "target": f"{target.image}@{target.name}",
    }
    if args.jsonl:
        print(json.dumps(pair, ensure_ascii=False))
        rows, a, b = rows_for(template, target)
        for row in rows:
            print(json.dumps(row, ensure_ascii=False))
        print(
            json.dumps(
                {
                    "kind": "summary",
                    "differing": len(rows),
                    "template_instructions": a,
                    "target_instructions": b,
                },
                ensure_ascii=False,
            )
        )
        return 0
    print(f"# template {pair['template']}, target {pair['target']}")
    show(template, target)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
