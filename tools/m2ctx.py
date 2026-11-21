#!/usr/bin/env python3
"""Preprocess one source's include chain for ``m2c --context``.

A header is preprocessed directly; a C source through a stub of its quoted
includes. The output carries declarations, not the source's function body. The
preprocessor is the build's GCC 2.7.2 PSX (``M2CTX_CC`` picks another), so the
context compiles under that compiler, which decomp.me also uses, and m2c parses it.

    tools/m2ctx.py src/overlays/battle/battle/03/battle_03.h -o build/m2ctx/battle_03.c
"""

from __future__ import annotations

import argparse
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

from bof3.core.paths import ROOT

# Same order as the build: src/ is searched before include/.
# The context must read like the build's: the PSX compiler's preprocessor predefines
# LANGUAGE_C, which hides the register names in <asm.h> (`fp` is `$30` otherwise, and
# `CdSearchFile(CdlFILE *fp, ...)` stops compiling), and it sets the 32-bit types.
PSX_GCC = os.environ.get("PSX_GCC") or str(ROOT / "toolchains/gcc-2.7.2-psx/gcc")
INCLUDES = ("-Isrc", "-Iinclude", "-Iinclude/psyq")
DEFINES = ("-D__attribute__(x)=", "-D__asm__(x)=", "-D__extension__=")
QUOTED = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.M)


def stub(path: Path) -> str:
    """Return one preprocessor input: the header, or a stub of its includes."""
    if path.suffix == ".h":
        return f'#include "{path.resolve()}"\n'
    names = QUOTED.findall(path.read_text(encoding="utf-8", errors="replace"))
    return "".join(f'#include "{name}"\n' for name in names) or '#include "common.h"\n'


def preprocess(path: Path, compiler: str) -> str:
    """Return the preprocessed stub, without line markers or duplicate pragmas."""
    with tempfile.TemporaryDirectory() as scratch:
        source = Path(scratch) / "ctx.c"
        source.write_text(stub(path), encoding="utf-8")
        argv = [
            compiler,
            "-E",
            "-P",
            *INCLUDES,
            f"-I{path.parent}",
            *DEFINES,
            str(source),
        ]
        result = subprocess.run(
            argv, cwd=ROOT, capture_output=True, text=True, check=False
        )
    if result.returncode:
        detail = result.stderr.strip() or result.stdout.strip()
        raise SystemExit(f"{' '.join(argv)} failed: {detail}")
    lines = result.stdout.splitlines(keepends=True)
    return "".join(
        line for line in lines if not line.lstrip().startswith(("#pragma", "#line"))
    )


def main(argv: list[str] | None = None) -> int:
    """Write the context for one source path."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("source", type=Path, help="C source or header to preprocess")
    parser.add_argument(
        "-o", "--output", type=Path, help="output file (default stdout)"
    )
    args = parser.parse_args(argv)
    compiler = os.environ.get("M2CTX_CC") or PSX_GCC
    if not os.path.exists(compiler):
        raise SystemExit(
            f"m2ctx: no compiler at {compiler}; run tools/setup.sh, or set M2CTX_CC"
        )
    text = preprocess(args.source, compiler)
    if args.output is None:
        sys.stdout.buffer.write(text.encode("utf-8"))
    else:
        args.output.parent.mkdir(parents=True, exist_ok=True)
        args.output.write_text(text, encoding="utf-8")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
