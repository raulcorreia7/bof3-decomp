#!/usr/bin/env python3
"""Draft every open function with m2c, try each draft, and keep the exact ones.

    tools/m2c_sweep.py                        every INCLUDE_ASM function without a template
    tools/m2c_sweep.py --sample 200           200 functions in a fixed random order
    tools/m2c_sweep.py --image emi/bmagic     one image or image prefix (repeatable)
    tools/m2c_sweep.py REF...                 TARGET@NAME or TARGET@0xADDRESS refs

For each function the tool preprocesses the context of the image header (`tools/m2ctx.py`), runs
`third_party/m2c` with a few flag variants (`default`, `no-andor`, `gotos-only`, `no-casts`) and
gives each distinct draft to `tools/try_body.py`. An exact draft stays in the tree: it is a lead,
so polish it (docs/matching.md#polish) and run `meson compile -C build/meson check-<image>`.
A function that no draft matches is left as it was. Each function prints one line, `EXACT`
or `BEST` with the fewest differing instructions of any draft that compiled (`NONE` when none
did), and goes to `build/m2c_sweep/results.jsonl` (target, status, differing, variant). A run skips
a function already in that file. `--jsonl` turns each printed line into an object. The drafts are
in `build/m2c_sweep/`.

Functions that `tools/dups.py near --full` pairs with a matched template are skipped: use
`tools/template_try.py` for them. Needs `rapidfuzz`
(`tools/setup.sh --matching`) and `third_party/m2c` (`tools/setup.sh --matching`).
"""

from __future__ import annotations

import argparse
import json
import random
import re
import subprocess
import sys
from collections.abc import Iterator
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from typing import NamedTuple

import m2ctx
import try_body
from bof3.adapters.cli import run_main
from bof3.core.paths import ROOT
from bof3.source.index import Func, find, load_index

WORK = "build/m2c_sweep"
SAMPLE_SEED = 1
JOBS = 8
RESULTS = f"{WORK}/results.jsonl"
VARIANTS = {
    "default": [],
    "no-andor": ["--no-andor"],
    "gotos-only": ["--gotos-only"],
    "no-casts": ["--no-casts"],
}
DEFINITION = re.compile(r"^\w[^;]*\)\s*\{\s*$")
UNKNOWN_TYPE = re.compile(r"(?:^[ \t]*|[(,][ \t]*)\?(?=[\s*,)])", re.M)
COMMENT = re.compile(r"\s*/\*.*?\*/\s*$")
# The work cell at 0x1F800044 holds a pointer to the mode's work record (include/sys/scratchpad.h).
SPAD_CELL = "g_Self"
SPAD_VIEW_NAME = (
    "g_SpadView"  # the typed twin of the cell that the context declares for m2c
)
SPAD_HI = re.compile(r"\(0x1F800044 >> 16\)")
SPAD_LO = re.compile(r"\(0x1F800044 & 0xFFFF\)")
SPAD_CAST = re.compile(r"\(\(?(?:volatile\s+)?(\w+)\s*\*\)\s*g_Self\b")
SPAD_TYPES = (  # image prefix -> work record, for a context that never casts the cell
    ("emi/battle/", "PartyMember"),
    ("emi/bmagic/", "PartyMember"),
    ("emi/boss/", "PartyMember"),
    ("emi/scenario/", "SceneBandEffect"),
    ("emi/etc/commu", "CommunicationTaskSlot"),
    ("emi/", "Actor"),
)


def asm_path(root: Path, func: Func) -> Path | None:
    """Return the assembly file of an INCLUDE_ASM function, or None."""
    path = root / "build/asm" / func.image / f"{func.name}.s"
    return path if path.is_file() else None


def to_body(draft: str, name: str) -> str | None:
    """Return the m2c output as a try_body body, or None when it holds no ``name`` definition."""
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


def spad_type(text: str, image: str) -> str | None:
    """Return the work record type of the scratchpad cell for a context, or None."""
    views = SPAD_CAST.findall(text)
    name = max(set(views), key=views.count) if views else None
    name = name or next((t for p, t in SPAD_TYPES if image.startswith(p)), None)
    if name and re.search(r"\}\s*" + name + r"\s*;", text):
        return name
    return None


def typed_cell(text: str, image: str) -> str:
    """Return the context with ``g_SpadView``, a pointer to the work record, declared last."""
    name = spad_type(text, image)
    if name is None:
        return text
    return text.rstrip("\n") + f"\nextern {name} *{SPAD_VIEW_NAME};\n"


def typed_asm(text: str) -> str:
    return SPAD_LO.sub(
        f"%lo({SPAD_VIEW_NAME})", SPAD_HI.sub(f"%hi({SPAD_VIEW_NAME})", text)
    )


def wrap_cell(body: str, name: str, root: Path, func: Func) -> str:
    """Spell the cell as `((T *)g_Self)` in a body, unless the unit defines a view macro."""
    macro = re.compile(rf"^[ \t]*#[ \t]*define[ \t]+{SPAD_CELL}\b", re.M)
    files = try_body.closure(root, func.src or "", 6, True)
    head, sep, rest = body.partition("MATCH ")
    if any(macro.search(try_body.read(root, f)) for f in files):
        return head + sep + re.sub(rf"\b{SPAD_VIEW_NAME}\b", SPAD_CELL, rest)
    return (
        head + sep + re.sub(rf"\b{SPAD_VIEW_NAME}\b", f"(({name} *){SPAD_CELL})", rest)
    )


def context(root: Path, func: Func, cache: dict[str, Path]) -> Path:
    """Return the preprocessed context of the function's image header, made once."""
    header = try_body.image_header(root, func.src or "") or func.src or ""
    if header not in cache:
        path = root / WORK / "ctx" / (header.replace("/", "+") + ".c")
        if not path.is_file():
            path.parent.mkdir(parents=True, exist_ok=True)
            text = m2ctx.preprocess(root / header, m2ctx.PSX_GCC)
            path.write_text(typed_cell(text, func.image), "utf-8")
        cache[header] = path
    return cache[header]


def drafts(root: Path, func: Func, ctx: Path, jobs: int = 1) -> dict[str, str]:
    """Return the body that each m2c variant gives, one per distinct text."""
    asm = asm_path(root, func)
    work = spad_type(ctx.read_text(encoding="utf-8"), func.image)
    if work and asm:
        asm = root / WORK / "asm" / func.image.replace("/", "+") / asm.name
        asm.parent.mkdir(parents=True, exist_ok=True)
        asm.write_text(typed_asm(asm_path(root, func).read_text("utf-8")), "utf-8")

    def one(item: tuple[str, list[str]]) -> tuple[str, str | None]:
        variant, flags = item
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
        if body and work and SPAD_VIEW_NAME in body:
            body = wrap_cell(body, work, root, func)
        return variant, body

    items = list(VARIANTS.items())
    if jobs > 1:
        with ThreadPoolExecutor(jobs) as pool:
            results = list(pool.map(one, items))
    else:
        results = [one(item) for item in items]
    out: dict[str, str] = {}
    seen: set[str] = set()
    for variant, body in results:
        if body and (key := try_body.body_key(body)) not in seen:
            seen.add(key)
            out[variant] = body
    return out


class Sweep(NamedTuple):
    """How the drafts of one function fared."""

    status: str
    diff: int | None
    variant: str


def sweep_one(root: Path, func: Func, found: dict[str, str]) -> Sweep:
    """Try the drafts; return (EXACT|BEST|NONE, fewest differing instructions, variant)."""
    best: tuple[int, str] | None = None
    for variant, body in found.items():
        status, _, diff = try_body.trial(root, func, body)
        if status == "EXACT":
            return Sweep("EXACT", 0, variant)
        if diff is not None and (best is None or diff < best[0]):
            best = (diff, variant)
    return Sweep("BEST", *best) if best else Sweep("NONE", None, "")


def save_drafts(root: Path, func: Func, found: dict[str, str]) -> None:
    """Keep the drafts under ``build/m2c_sweep/<image>/<ADDR>.<variant>.c``."""
    folder = root / WORK / func.image.replace("/", "+")
    folder.mkdir(parents=True, exist_ok=True)
    for variant, body in found.items():
        (folder / f"{func.addr:08X}.{variant}.c").write_text(body, encoding="utf-8")


def read_results(root: Path) -> set[str]:
    """Return the refs of the functions already swept."""
    path = root / RESULTS
    if not path.is_file():
        return set()
    return {
        json.loads(line)["target"]
        for line in path.read_text(encoding="utf-8").splitlines()
        if line.strip()
    }


def templated(root: Path) -> set[str]:
    """Return the refs that ``dups.py near --full`` pairs with a matched template."""
    result = subprocess.run(
        [sys.executable, str(root / "tools/dups.py"), "near", "--full", "--jsonl"],
        cwd=root,
        capture_output=True,
        check=True,
        text=True,
    )
    return {
        json.loads(line)["target"]
        for line in result.stdout.splitlines()
        if line.strip()
    }


def select(args: argparse.Namespace, funcs: list[Func]) -> list[Func]:
    """Return the functions to sweep, smaller first."""
    if args.refs:
        chosen = [find(funcs, r) for r in args.refs]
    else:
        chosen = [f for f in funcs if f.status == "ASM" and f.src]
    if args.image:
        chosen = [f for f in chosen if any(f.image.startswith(i) for i in args.image)]
    chosen = [f for f in chosen if asm_path(ROOT, f)]
    if not args.refs:
        skip = templated(ROOT)
        chosen = [f for f in chosen if f.ref not in skip]
    done = read_results(ROOT)
    chosen = [f for f in chosen if f.ref not in done]
    if args.sample:
        chosen = random.Random(args.seed).sample(chosen, min(args.sample, len(chosen)))
    return sorted(chosen, key=lambda f: (f.size, f.ref))


def stream(
    root: Path, funcs: list[Func], jobs: int = JOBS
) -> Iterator[tuple[Func, dict]]:
    """Yield each function with its drafts; m2c runs ``jobs`` at a time, in order."""
    cache: dict[str, Path] = {}
    contexts = {id(f): context(root, f, cache) for f in funcs}
    with ThreadPoolExecutor(jobs) as pool:
        yield from zip(
            funcs,
            pool.map(lambda f: drafts(root, f, contexts[id(f)]), funcs),
            strict=True,
        )


def _parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("refs", nargs="*", help="TARGET@NAME or TARGET@0xADDRESS")
    parser.add_argument("--image", action="append", help="image id or prefix")
    parser.add_argument("--sample", type=int, help="sweep N functions at random")
    parser.add_argument(
        "--seed",
        type=int,
        default=SAMPLE_SEED,
        help="seed of the random sample (default %(default)s)",
    )
    parser.add_argument(
        "--jobs",
        type=int,
        default=JOBS,
        help="m2c runs at a time (default %(default)s)",
    )
    parser.add_argument(
        "--jsonl", action="store_true", help="one JSON object per printed line"
    )
    return parser  # fmt: skip


def _line(func: Func, status: str, diff: int | None, variant: str, jsonl: bool) -> str:
    """The printed line of one result."""
    if jsonl:
        row = {"status": status, "target": func.ref, "name": func.name}
        return json.dumps(
            row | {"differing": diff, "variant": variant or None}, ensure_ascii=False
        )
    best = f" {diff} differ ({variant})" if status == "BEST" else ""
    return f"{status} {func.ref} {func.name}{best}"


def main(argv: list[str] | None = None) -> int:
    """Run the sweep."""
    args = _parser().parse_args(argv)
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
            entry = {
                "target": func.ref,
                "status": status,
                "differing": diff,
                "variant": variant or None,
            }
            log.write(json.dumps(entry, ensure_ascii=False) + "\n")
            log.flush()
            print(_line(func, status, diff, variant, args.jsonl), flush=True)
    print(f"{hits} exact of {len(funcs)}", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(run_main(main))
