#!/usr/bin/env python3
"""List the values that live across a call, with allocator priority and final register.

    tools/alloc_priority.py SOURCE.c FUNCTION

Compiles the file with `tools/rtl_dump.sh` (`-dl -dg`) and prints one row per pseudo-register
that crosses a call, in the order GCC 2.7.2 places them: local allocation first (`b<N>`, a value
that lives in one basic block, block by block), then global allocation (`all`). Within each, the
priority `floor(log2(uses)) * uses * 10000 / live length` decides, highest first, and a tie goes to
the lower pseudo number. Uses are already weighted by loop depth (a use inside one loop counts 2).
A row shows the priority, scope, uses, live length, the register it got (`s0`..`s8`, or STACK) and
the instruction that first sets it. Each value takes the lowest saved register free over its life.

    tools/alloc_priority.py src/engine/area/map/Area_CellDrawRing.c Area_CellDrawRing
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
BLOCK = re.compile(r"^ in block (\d+)")


def priority(uses, length):
    """Return GCC 2.7.2's allocno priority, computed in double as global.c does."""
    return int(float(int(math.log2(uses)) * uses) / length * 10000)


def allocation_order(rows):
    """Sort (pseudo, uses, length, block) rows into the order the allocators take them."""
    return sorted(
        rows,
        key=lambda row: (
            row[3] is None,
            row[3] if row[3] is not None else 0,
            -priority(row[1], row[2]),
            row[0],
        ),
    )


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
        block = BLOCK.match(rest)
        rows.append(
            (int(pseudo), int(uses), int(length), int(block[1]) if block else None)
        )
    for pseudo, uses, length, block in allocation_order(rows):
        register = hard.get(str(pseudo))
        place = SAVED_REGISTERS.get(int(register), register) if register else "STACK"
        scope = f"b{block}" if block is not None else "all"
        print(
            f"{priority(uses, length):5d} {scope:<4} r{pseudo:<4} uses {uses:3d} len {length:4d}"
            f" -> {place:<5} {first_setter(insns, str(pseudo))}"
        )


if __name__ == "__main__":
    main()
