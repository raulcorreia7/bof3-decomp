#!/usr/bin/env python3
"""Compare retail and candidate by opcode sequence only, ignoring registers and offsets.

    tools/opcode_diff.py TARGET@0xADDRESS [CONTEXT]

Runs `tools/match.sh --diff`, aligns the two instruction lists on their opcodes and prints each
differing hunk with both sides in full (`R` retail, `C` candidate), then a last line
`hunks N retail R cand C`. CONTEXT is the number of instructions printed before each hunk
(default 0). Use it on a large function to fix the structure before the registers.

    tools/opcode_diff.py exe/slus_004_22@0x801530D0 2
"""

import argparse
import difflib
import re
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
DIFF_LINE = re.compile(r"^[! ] ?[0-9A-F]{8}:")
DIFF_CONTINUATION = re.compile(r"^[! ]\s+\|")
INSTRUCTION = re.compile(r"\s*([0-9A-F]{8}):\s+[0-9a-f]{8}\s+(\S+)\s*(.*)")


def side_by_side(function):
    """Return the (retail, candidate) instruction lists of `match.sh --diff`."""
    output = subprocess.run(
        ["sh", str(ROOT / "tools/match.sh"), "--diff", function],
        check=False,
        cwd=ROOT,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT,
        text=True,
    ).stdout
    retail, candidate = [], []
    for line in output.splitlines():
        if not (DIFF_LINE.match(line) or DIFF_CONTINUATION.match(line)):
            continue
        left, _, right = line[2:].partition("|")
        for text, instructions in ((left, retail), (right, candidate)):
            found = INSTRUCTION.match(text)
            if found:
                instructions.append((found[1], found[2], found[3].strip()))
    return retail, candidate


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("function", help="TARGET@0xADDRESS")
    parser.add_argument("context", nargs="?", type=int, default=0)
    args = parser.parse_args()
    retail, candidate = side_by_side(args.function)
    matcher = difflib.SequenceMatcher(
        None, [i[1] for i in retail], [i[1] for i in candidate], autojunk=False
    )
    hunks = 0
    for tag, r1, r2, c1, c2 in matcher.get_opcodes():
        if tag == "equal":
            continue
        hunks += 1
        print(
            f"--- {tag} retail[{retail[r1][0] if r1 < len(retail) else 'end'}..]"
            f" cand[{candidate[c1][0] if c1 < len(candidate) else 'end'}..]"
        )
        for row in retail[max(r1 - args.context, 0) : r2]:
            print("  R {} {:<6} {}".format(*row))
        for row in candidate[max(c1 - args.context, 0) : c2]:
            print("  C {} {:<6} {}".format(*row))
    print(f"hunks {hunks} retail {len(retail)} cand {len(candidate)}")


if __name__ == "__main__":
    main()
