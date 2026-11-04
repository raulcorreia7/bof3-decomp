#!/usr/bin/env python3
"""Draft every open function with m2c, try each draft, and keep the exact ones.

    tools/m2c_sweep.py                        every INCLUDE_ASM function without a template
    tools/m2c_sweep.py --sample 200           200 functions, in a fixed random order (--seed)
    tools/m2c_sweep.py --image emi/bmagic     one image or image prefix (repeatable)
    tools/m2c_sweep.py --tsv ROWS.tsv         the TARGET@NAME refs in the first column
    tools/m2c_sweep.py REF...                 TARGET@NAME or TARGET@0xADDRESS refs
    tools/m2c_sweep.py --residual FILE        write the finished rows, fewest differing first

For each function the tool preprocesses the context of the image header (`tools/m2ctx.py`), runs
`third_party/m2c` with a few flag variants (`default`, `no-andor`, `gotos-only`, `no-casts`) and
gives each distinct draft to `tools/try_body.py`. An exact draft stays in the tree: it is a lead,
so polish it (docs/matching.md#polish) and run `meson compile -C build/meson check-<image>`.
A function that no draft matches is left as it was. Each function prints one line, `EXACT`
or `BEST` with the fewest differing instructions of any draft that compiled (`NONE` when none
did), and goes to `build/m2c_sweep/results.tsv` (ref, differing, variant). A run skips a
function already in that file; `--again` drafts it anew. The drafts are in `build/m2c_sweep/`.

Functions that `tools/dups.py near --full` pairs with a matched template are skipped: use
`tools/template_try.py` for them (`--templates` adds them to the sweep). Needs `rapidfuzz`
(`tools/setup.sh --matching`) and `third_party/m2c` (`tools/setup.sh --matching`).
"""

from __future__ import annotations

import argparse
import random
import re
import subprocess
import sys
from collections.abc import Iterator
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

import m2ctx
import try_body
from bof3.source.index import Func, find, load_index

ROOT = Path(__file__).resolve().parent.parent
WORK = "build/m2c_sweep"
RESULTS = f"{WORK}/results.tsv"
VARIANTS = {
    "default": [],
    "no-andor": ["--no-andor"],
    "gotos-only": ["--gotos-only"],
    "no-casts": ["--no-casts"],
}
DEFINITION = re.compile(r"^\w[^;]*\)\s*\{\s*$")
UNKNOWN_TYPE = re.compile(r"(?:^[ \t]*|[(,][ \t]*)\?(?=[\s*,)])", re.M)
COMMENT = re.compile(r"\s*/\*.*?\*/\s*$")


def asm_path(root: Path, func: Func) -> Path | None:
    """Return the assembly file of an INCLUDE_ASM function, or None."""
    path = root / "asm" / func.image / f"{func.name}.s"
    return path if path.is_file() else None


def to_body(draft: str, name: str) -> str | None:
    """Return the m2c output as a try_body body, or None when it holds no ``name`` definition.

    A declaration before the definition becomes an `@decl` line, unless it has an unknown type
    (`?`); the definition gets the `MATCH` prefix. A draft that still names an unknown type fails
    to compile, so it is dropped here.
    """
    lines = draft.rstrip().splitlines()
    start = next(
        (
            i
            for i, ln in enumerate(lines)
            if DEFINITION.match(ln)
            and re.search(r"\b" + re.escape(name) + r"\s*\(", ln)
        ),
        None,
    )
    if start is None:
        return None
    decls = []
    for ln in lines[:start]:
        ln = COMMENT.sub("", ln).strip()
        if ln and "?" not in ln:
            decls.append(f"@decl {ln}")
    body = "\n".join(lines[start:])
    if UNKNOWN_TYPE.search(body):
        return None
    return "\n".join([*decls, "MATCH " + body]) + "\n"


def context(root: Path, func: Func, cache: dict[str, Path]) -> Path:
    """Return the preprocessed context of the function's image header, made once."""
    header = try_body.image_header(root, func.src or "") or func.src or ""
    if header not in cache:
        path = root / WORK / "ctx" / (header.replace("/", "+") + ".c")
        if not path.is_file():
            path.parent.mkdir(parents=True, exist_ok=True)
            path.write_text(m2ctx.preprocess(root / header, m2ctx.PSX_GCC), "utf-8")
        cache[header] = path
    return cache[header]


def drafts(root: Path, func: Func, ctx: Path) -> dict[str, str]:
    """Return the body that each m2c variant gives, one per distinct text."""
    asm = asm_path(root, func)
    out: dict[str, str] = {}
    seen: set[str] = set()
    for variant, flags in VARIANTS.items():
        run = subprocess.run(
            [
                sys.executable,
                str(root / "third_party/m2c/m2c.py"),
                "-t",
                "mips-gcc-c",
                "--context",
                str(ctx),
                *flags,
                "-f",
                func.name,
                str(asm),
            ],
            cwd=root,
            capture_output=True,
            text=True,
            check=False,
        )
        body = to_body(run.stdout, func.name) if run.returncode == 0 else None
        if body and (key := try_body.body_key(body)) not in seen:
            seen.add(key)
            out[variant] = body
    return out


def sweep_one(
    root: Path, func: Func, found: dict[str, str]
) -> tuple[str, int | None, str]:
    """Try the drafts; return (EXACT|BEST|NONE, fewest differing instructions, variant)."""
    best: tuple[int, str] | None = None
    for variant, body in found.items():
        status, _, diff = try_body.trial(root, func, body)
        if status == "EXACT":
            return "EXACT", 0, variant
        if diff is not None and (best is None or diff < best[0]):
            best = (diff, variant)
    return ("BEST", *best) if best else ("NONE", None, "")


def save_drafts(root: Path, func: Func, found: dict[str, str]) -> None:
    """Keep the drafts under ``build/m2c_sweep/<image>/<ADDR>.<variant>.c``."""
    folder = root / WORK / func.image.replace("/", "+")
    folder.mkdir(parents=True, exist_ok=True)
    for variant, body in found.items():
        (folder / f"{func.addr:08X}.{variant}.c").write_text(body, encoding="utf-8")


def read_results(root: Path) -> dict[str, tuple[str, str]]:
    """Return ref -> (differing, variant) of the finished functions."""
    path = root / RESULTS
    if not path.is_file():
        return {}
    rows = (ln.split("\t") for ln in path.read_text(encoding="utf-8").splitlines())
    return {r[0]: (r[1], r[2]) for r in rows if len(r) >= 3}


def templated(root: Path) -> set[str]:
    """Return the refs that ``dups.py near --full`` pairs with a matched template."""
    out = root / WORK / "templates.tsv"
    out.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run(
        [sys.executable, str(root / "tools/dups.py"), "near", "--full", "-o", str(out)],
        cwd=root,
        capture_output=True,
        check=True,
    )
    rows = out.read_text(encoding="utf-8").splitlines()[1:]
    return {r.split("\t")[0] for r in rows if r.strip()}


def select(args: argparse.Namespace, funcs: list[Func]) -> list[Func]:
    """Return the functions to sweep, smaller first."""
    if args.refs or args.tsv:
        refs = list(args.refs)
        if args.tsv:
            refs += [
                ln.split("\t")[0]
                for ln in args.tsv.read_text(encoding="utf-8").splitlines()
                if ln.strip() and not ln.startswith("#")
            ]
        chosen = [find(funcs, r) for r in refs]
    else:
        chosen = [f for f in funcs if f.status == "ASM" and f.src]
    if args.image:
        chosen = [f for f in chosen if any(f.image.startswith(i) for i in args.image)]
    chosen = [f for f in chosen if asm_path(ROOT, f)]
    if not args.templates and not (args.refs or args.tsv):
        skip = templated(ROOT)
        chosen = [f for f in chosen if f.ref not in skip]
    if not args.again:
        done = read_results(ROOT)
        chosen = [f for f in chosen if f.ref not in done]
    if args.sample:
        chosen = random.Random(args.seed).sample(chosen, min(args.sample, len(chosen)))
    return sorted(chosen, key=lambda f: (f.size, f.ref))


def residual(root: Path, out: Path) -> int:
    """Write the finished rows without an exact match, fewest differing first."""
    rows = [(r, d) for r, (d, _) in read_results(root).items() if d != "EXACT"]
    rows.sort(key=lambda x: (int(x[1]) if x[1].isdigit() else 10**9, x[0]))
    out.parent.mkdir(parents=True, exist_ok=True)
    with out.open("w", encoding="utf-8") as fh:
        fh.write("function\tbest_diff\n")
        for ref, diff in rows:
            fh.write(f"{ref}\t{diff or 'none'}\n")
    return len(rows)


def stream(root: Path, funcs: list[Func], jobs: int) -> Iterator[tuple[Func, dict]]:
    """Yield each function with its drafts; m2c runs ``jobs`` at a time, in order."""
    cache: dict[str, Path] = {}
    contexts = {id(f): context(root, f, cache) for f in funcs}
    with ThreadPoolExecutor(jobs) as pool:
        yield from zip(
            funcs,
            pool.map(lambda f: drafts(root, f, contexts[id(f)]), funcs),
            strict=True,
        )


def main(argv: list[str] | None = None) -> int:
    """Run the sweep."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("refs", nargs="*", help="TARGET@NAME or TARGET@0xADDRESS")
    parser.add_argument("--tsv", type=Path, help="refs in the first column")
    parser.add_argument("--image", action="append", help="image id or prefix")
    parser.add_argument("--sample", type=int, help="sweep N functions at random")
    parser.add_argument("--seed", type=int, default=1, help="sample seed (1)")
    parser.add_argument("-j", "--jobs", type=int, default=8, help="m2c processes (8)")
    parser.add_argument(
        "--templates", action="store_true", help="keep templated functions"
    )
    parser.add_argument("--again", action="store_true", help="redo finished functions")
    parser.add_argument("--residual", type=Path, help="write the residual TSV and exit")
    args = parser.parse_args(argv)
    if args.residual:
        print(f"{residual(ROOT, args.residual)} rows -> {args.residual}")
        return 0
    funcs = select(args, load_index(ROOT))
    print(f"sweeping {len(funcs)} functions", file=sys.stderr, flush=True)
    path = ROOT / RESULTS
    path.parent.mkdir(parents=True, exist_ok=True)
    hits = 0
    with path.open("a", encoding="utf-8") as log:
        for func, found in stream(ROOT, funcs, args.jobs):
            save_drafts(ROOT, func, found)
            status, diff, variant = sweep_one(ROOT, func, found)
            hits += status == "EXACT"
            shown = "EXACT" if status == "EXACT" else "" if diff is None else str(diff)
            log.write(f"{func.ref}\t{shown}\t{variant}\n")
            log.flush()
            print(
                f"{status} {func.ref} {func.name}"
                + (f" {diff} differ ({variant})" if status == "BEST" else ""),
                flush=True,
            )
    print(f"{hits} exact of {len(funcs)}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
