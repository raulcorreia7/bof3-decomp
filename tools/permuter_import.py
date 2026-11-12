#!/usr/bin/env python3
"""Import one function into decomp-permuter with the project's cc wrapper.

Usage: tools/permuter_import.py FUNC   (after `meson setup build/meson`)

FUNC is a source under ``src/``; its first NON_MATCHING definition is imported,
else its first MATCH definition. The split assembly name is the function name,
and the settings use the flags the Meson build compiles with (build/meson/emit).
"""

from __future__ import annotations

import argparse
import json
import re
import shlex
import subprocess
import sys
from pathlib import Path

from bof3.core.io import write_atomic
from bof3.resolve.ids import asm_dir
from bof3.status.claims import source_text

ROOT = Path(__file__).resolve().parent.parent
# The permuter's MIPS flags (its MIPS_SETTINGS). A set objdump_command replaces its default arguments.
OBJDUMP_ARGUMENTS = ["-drz", "-m", "mips:4300"]
_DRAFT = re.compile(r"^NON_MATCHING\s+.*?\b([A-Za-z_]\w*)\s*\(", re.M)
_DEFINITION = re.compile(
    r"^(?:MATCH|NON_MATCHING)\s+(?:INCLUDE_ASM\(\s*(\w+)\s*\)|.*?\b([A-Za-z_]\w*)\s*\()",
    re.M,
)


def function_name(source: Path) -> str:
    """Return the draft's function name, else the first matched definition.

    A shared-body member holds an ``#include`` of the header that defines it; the header counts.

    A `MATCH INCLUDE_ASM(name)` unit names its function in the macro.
    """
    text = source_text(source)
    draft = _DRAFT.search(text)
    if draft is not None:
        return draft.group(1)
    match = _DEFINITION.search(text)
    if match is None:
        raise SystemExit(f"{source}: no MATCH or NON_MATCHING definition")
    return match.group(1) or match.group(2)


def settings_toml(compiler: str, assembler: str, prelude: str) -> str:
    """Return the permuter settings; objdump is the repo's binutils, found without PATH."""
    objdump = shlex.join([f"{ROOT}/bin/internal/binutils/objdump", *OBJDUMP_ARGUMENTS])
    return "\n".join(
        [
            'compiler_type = "gcc"',
            f"compiler_command = {json.dumps(compiler)}",
            f"assembler_command = {json.dumps(assembler)}",
            f"objdump_command = {json.dumps(objdump)}",
            f"asm_prelude_file = {json.dumps(prelude)}",
            "",
        ]
    )


def main() -> int:
    """Write the settings and import the source's selected function."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("func", type=Path, help="C source with the function")
    args = parser.parse_args()
    emit = ROOT / "build/meson/emit"
    try:
        compiler_flags = (emit / "cflags.txt").read_text().strip()
        assembler_flags = (emit / "asflags.txt").read_text().strip()
    except OSError:
        raise SystemExit(
            f"{emit}: no flags; run `meson setup build/meson` first"
        ) from None
    assembler_command = f"{ROOT}/bin/internal/binutils/as {assembler_flags}"
    source = args.func if args.func.is_absolute() else ROOT / args.func
    directory = asm_dir(source, ROOT)
    if directory is None:
        raise SystemExit(f"{source}: outside every target's source folder")
    name = function_name(source)
    asm = ROOT / directory / f"{name}.s"
    if not asm.is_file():
        raise SystemExit(f"{asm}: missing split assembly for {name}")
    importer = ROOT / "third_party/decomp-permuter/import.py"
    if not importer.is_file():
        raise SystemExit(
            f"{importer}: decomp-permuter is not checked out; run `tools/setup.sh --matching`"
        )
    work = ROOT / "work/permute"
    settings = work / "settings.toml"
    prelude = work / "prelude.inc"
    target_asm = work / "target.s"
    write_atomic(prelude, '.include "macro.inc"\n.set noat\n.set noreorder\n')
    compiler = f"{sys.executable} {ROOT}/tools/cc.py {compiler_flags} -O2 -DNON_MATCHING -DBOF3_ASM_MATCH=0 -c"
    write_atomic(
        settings,
        settings_toml(
            compiler, assembler_command, prelude.relative_to(ROOT).as_posix()
        ),
    )
    text = asm.read_text(encoding="utf-8", errors="replace")
    write_atomic(target_asm, text.replace('.section .text, "ax"', ".section .text"))
    result = subprocess.run(
        [
            sys.executable,
            str(importer),
            "--settings",
            str(settings),
            str(source),
            str(target_asm),
        ],
        cwd=work,
        check=False,
    )
    return result.returncode


if __name__ == "__main__":
    raise SystemExit(main())
