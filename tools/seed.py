#!/usr/bin/env python3
"""Write the seed bundle of one open function: everything to read before the first attempt.

    tools/seed.py TARGET@NAME            or TARGET@0xADDRESS

The bundle is `work/<image>/<ADDR>/`:

    asm.s        the function's assembly
    ctx.c        the image header's preprocessed context (tools/m2ctx.py)
    draft.c      the best m2c draft, the one with the fewest differing instructions
    draft.txt    that draft's result: variant, differing instructions, first difference
    hints.md     the facts in the assembly, each with the tactic row it maps to
                 (bof3/source/hints.py)
    callees.txt  the prototype of each function the assembly calls
    callers.txt  the lines of src/ and the split assembly that call the function (`--callers`, 30 by default)

The trial runs `tools/try_body.py` on each m2c draft (tools/m2c_sweep.py); an exact draft stays
in the tree, so polish it and run `meson compile -C build/meson check-<image>`. The bundle is
scratch under `work/`, which Git ignores.
"""

from __future__ import annotations

import argparse
import re
import subprocess
from pathlib import Path

import m2c_sweep
import try_body
from bof3.adapters.cli import run_main
from bof3.core.paths import ROOT
from bof3.source import hints
from bof3.source.ctext import read
from bof3.source.index import Func, find, load_index
from bof3.source.remap import declaration

CALLERS = 30
JAL = re.compile(r"^\s*/\*.*?\*/\s+jal\s+(\w+)", re.M)


def callees(root: Path, func: Func) -> list[str]:
    """Return one line per called function: its prototype, or ``name  (no prototype)``."""
    asm = m2c_sweep.asm_path(root, func)
    names = sorted(set(JAL.findall(asm.read_text(encoding="utf-8")))) if asm else []
    texts = [read(root, f) for f in try_body.closure(root, func.src or "")]
    return [
        next((d for t in texts if (d := declaration(t, n))), f"{n}  (no prototype)")
        for n in names
    ]


def callers(root: Path, func: Func, limit: int = CALLERS) -> list[str]:
    """Return the ``path:line: text`` lines that call the function, outside its own file."""
    out = subprocess.run(
        ["git", "grep", "-n", "-w", func.name, "--", "src", "asm"],
        cwd=root,
        capture_output=True,
        text=True,
        check=False,
    ).stdout.splitlines()
    own = {func.src, f"build/asm/{func.image}/{func.name}.s"}
    lines = [ln for ln in out if ln.split(":", 1)[0] not in own]
    return [
        ln
        for ln in lines
        if re.search(r"\b" + re.escape(func.name) + r"\s*\(|jal\s+" + func.name, ln)
    ][:limit]


def draft(root: Path, func: Func, context: Path) -> tuple[str, str]:
    """Return the best draft and the line that says how it fared."""
    found = m2c_sweep.drafts(root, func, context, jobs=len(m2c_sweep.VARIANTS))
    if not found:
        return "", "no m2c draft compiles to a definition of the function\n"
    best = None
    for variant, body in found.items():
        status, detail, diff = try_body.trial(root, func, body)
        if status == "EXACT":
            return body, f"{variant}: EXACT, kept in {func.src}\n"
        rank = (diff is None, diff or 0)
        if best is None or rank < best[0]:
            best = (rank, variant, body, detail)
    assert best
    _, variant, body, detail = best
    return body, f"{variant}: {detail}\n"


def main(argv: list[str] | None = None) -> int:
    """Write the bundle and print its folder."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("target", help="TARGET@NAME or TARGET@0xADDRESS")
    parser.add_argument(
        "--callers",
        type=int,
        default=CALLERS,
        help="caller lines to keep (default %(default)s)",
    )
    args = parser.parse_args(argv)
    funcs = load_index(ROOT)
    func = find(funcs, args.target)
    asm = m2c_sweep.asm_path(ROOT, func)
    if func.status != "ASM" or not asm or not func.src:
        raise SystemExit(f"seed: {args.target} is not an INCLUDE_ASM function")
    folder = ROOT / "work" / func.image / f"{func.addr:08X}"
    folder.mkdir(parents=True, exist_ok=True)
    (folder / "asm.s").write_text(asm.read_text(encoding="utf-8"), encoding="utf-8")
    context = m2c_sweep.context(ROOT, func, {})
    (folder / "ctx.c").write_text(context.read_text(encoding="utf-8"), encoding="utf-8")
    body, result = draft(ROOT, func, context)
    (folder / "draft.c").write_text(body, encoding="utf-8")
    (folder / "draft.txt").write_text(result, encoding="utf-8")
    (folder / "hints.md").write_text(
        hints.build(ROOT, func, asm.read_text(encoding="utf-8")), encoding="utf-8"
    )
    (folder / "callees.txt").write_text("\n".join(callees(ROOT, func)) + "\n", "utf-8")
    (folder / "callers.txt").write_text(
        "\n".join(callers(ROOT, func, args.callers)) + "\n", "utf-8"
    )
    print(folder.relative_to(ROOT))
    print(result.rstrip())
    return 0


if __name__ == "__main__":
    raise SystemExit(run_main(main))
