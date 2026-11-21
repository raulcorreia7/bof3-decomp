#!/usr/bin/env python3
"""List the values that live across a call, with allocator priority and final register.

    tools/alloc_priority.py SOURCE.c FUNCTION

Compiles the file with `tools/rtl_dump.sh` (`-dl -dg`) and prints one row per pseudo-register
that crosses a call, highest priority first: the priority
(`floor(log2(uses)) * uses * 10000 / live length`, the order GCC's global allocator takes),
the uses, the live length, the register it got (`s0`..`s8`, or STACK) and the instruction that
first sets it. Use it to see which value should take which saved register.

    tools/alloc_priority.py src/engine/field/Area_DrawCellRing.c Area_DrawCellRing
"""

import argparse
import math
import os
import re
import subprocess
import tempfile
from pathlib import Path

from bof3.core.paths import ROOT

SAVED_REGISTERS = {
    16: "s0",
    17: "s1",
    18: "s2",
    19: "s3",
    20: "s4",
    21: "s5",
    22: "s6",
    23: "s7",
    30: "s8",
}
USAGE = re.compile(r"Register (\d+) used (\d+) times across (\d+) insns(.*?)\.\n", re.S)


def dump_part(path, function):
    """Return a dump's text from the start of one function."""
    text = Path(path).read_text()
    return text[text.index(f";; Function {function}") :]


def first_setter(insns, register):
    """Return the start of the first insn that sets the pseudo-register."""
    pattern = re.compile(r"\(set \(reg(/\w)*:\w+ " + register + r"\) (.*)")
    for insn in insns:
        found = pattern.search(" ".join(insn.split()))
        if found:
            return found[2][:60]
    return ""


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("source", help="C file, relative to the repository root")
    parser.add_argument("function")
    args = parser.parse_args()
    with tempfile.TemporaryDirectory(prefix="pri-") as out:
        report(args, out)


def report(args, out):
    """Compile with the dumps on and print the rows."""
    subprocess.run(
        ["sh", str(ROOT / "tools/rtl_dump.sh"), args.source, "lg"],
        check=False,
        cwd=ROOT,
        env={**os.environ, "OUT": out},
        stdout=subprocess.DEVNULL,
        stderr=subprocess.DEVNULL,
    )
    name = os.path.basename(args.source)
    global_alloc = dump_part(f"{out}/{name}.greg", args.function)
    local_alloc = dump_part(f"{out}/{name}.lreg", args.function)
    hard = {}
    dispositions = re.search(r"Register dispositions:(.*?)\n\n", global_alloc, re.S)
    for pseudo, register in re.findall(r"(\d+) in (\d+)", dispositions.group(1)):
        hard[pseudo] = register
    insns = local_alloc.split("\n\n")
    rows = []
    for found in USAGE.finditer(local_alloc):
        pseudo, uses, length, rest = found.groups()
        if "crosses" not in rest:
            continue
        uses, length = int(uses), int(length)
        priority = int(math.log2(uses)) * uses * 10000 // length
        rows.append((priority, pseudo, uses, length, hard.get(pseudo)))
    for priority, pseudo, uses, length, register in sorted(rows, reverse=True):
        place = SAVED_REGISTERS.get(int(register), register) if register else "STACK"
        print(
            f"{priority:5d} r{pseudo:<4} uses {uses:3d} len {length:4d} -> {place:<5}"
            f" {first_setter(insns, pseudo)}"
        )


if __name__ == "__main__":
    main()
