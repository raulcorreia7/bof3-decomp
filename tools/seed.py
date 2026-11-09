#!/usr/bin/env python3
"""Write the seed bundle of one open function: everything to read before the first attempt.

    tools/seed.py TARGET@NAME            or TARGET@0xADDRESS
    tools/seed.py TARGET@NAME --no-try   skip the draft trial (no compile)

The bundle is `work/<image>/<ADDR>/`:

    asm.s        the function's assembly
    ctx.c        the image header's preprocessed context (tools/m2ctx.py)
    draft.c      the best m2c draft, the one with the fewest differing instructions
    draft.txt    that draft's result: variant, differing instructions, first difference
    twins.txt    the three nearest matched functions: C body and instruction diff
                 (tools/template_diff.py)
    callees.txt  the prototype of each function the assembly calls
    callers.txt  the lines of src/ and asm/ that call the function

The trial runs `tools/try_body.py` on each m2c draft (tools/m2c_sweep.py); an exact draft stays
in the tree, so polish it and run `meson compile -C build/meson check-<image>`. The bundle is
scratch under `work/`, which Git ignores. Needs `rapidfuzz` (`tools/setup.sh --matching`).
"""

from __future__ import annotations

import argparse
import contextlib
import io
import re
import subprocess
from pathlib import Path

import m2c_sweep
import template_diff
import template_try
import try_body
from bof3.source.ctext import read
from bof3.source.index import Func, find, load_index
from bof3.source.remap import declaration

ROOT = Path(__file__).resolve().parent.parent
TWINS = 3
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


def callers(root: Path, func: Func) -> list[str]:
    """Return the ``path:line: text`` lines that call the function, outside its own file."""
    out = subprocess.run(
        ["git", "grep", "-n", "-w", func.name, "--", "src", "asm"],
        cwd=root,
        capture_output=True,
        text=True,
        check=False,
    ).stdout.splitlines()
    own = {func.src, f"asm/{func.image}/{func.name}.s"}
    lines = [ln for ln in out if ln.split(":", 1)[0] not in own]
    return [
        ln
        for ln in lines
        if re.search(r"\b" + re.escape(func.name) + r"\s*\(|jal\s+" + func.name, ln)
    ][:CALLERS]


def twins(root: Path, funcs: list[Func], func: Func) -> str:
    """Return the nearest matched functions with their C and their instruction diff."""
    parts = []
    for score, twin in template_diff.candidates(funcs, func, TWINS):
        parts.append(f"# {score:.3f} {twin.ref} {twin.name} ({twin.size} bytes)")
        found = template_try.locate(twin.src or "", twin.name)
        if found:
            path, start, end = found
            parts.append(f"# {path}\n{read(root, path)[start:end].strip()}")
        buffer = io.StringIO()
        with contextlib.redirect_stdout(buffer):
            template_diff.show(twin, func)
        parts.append(buffer.getvalue().rstrip())
    return "\n\n".join(parts) + "\n"


def draft(root: Path, func: Func, run: bool) -> tuple[str, str]:
    """Return the best draft and the line that says how it fared."""
    ctx = m2c_sweep.context(root, func, {})
    found = m2c_sweep.drafts(root, func, ctx)
    if not found:
        return "", "no m2c draft compiles to a definition of the function\n"
    if not run:
        variant, body = next(iter(found.items()))
        return body, f"{variant}: not tried\n"
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
        "--no-try", action="store_true", help="do not compile the drafts"
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
    (folder / "ctx.c").write_text(
        m2c_sweep.context(ROOT, func, {}).read_text(encoding="utf-8"), encoding="utf-8"
    )
    body, result = draft(ROOT, func, not args.no_try)
    (folder / "draft.c").write_text(body, encoding="utf-8")
    (folder / "draft.txt").write_text(result, encoding="utf-8")
    (folder / "twins.txt").write_text(twins(ROOT, funcs, func), encoding="utf-8")
    (folder / "callees.txt").write_text("\n".join(callees(ROOT, func)) + "\n", "utf-8")
    (folder / "callers.txt").write_text("\n".join(callers(ROOT, func)) + "\n", "utf-8")
    print(folder.relative_to(ROOT))
    print(result.rstrip())
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
