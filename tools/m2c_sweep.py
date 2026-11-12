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
did), and goes to `build/m2c_sweep/results.tsv` (ref, differing, variant). A run skips a
function already in that file. The drafts are in `build/m2c_sweep/`.

Functions that `tools/dups.py near --full` pairs with a matched template are skipped: use
`tools/template_try.py` for them. Needs `rapidfuzz`
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
SAMPLE_SEED = 1
JOBS = 8
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
# The work cell at 0x1F800044 holds a pointer to the mode's work record (include/sys/scratchpad.h).
SPAD_CELL = "g_Task"
SPAD_VIEW_NAME = (
    "g_SpadView"  # the typed twin of the cell that the context declares for m2c
)
SPAD_HI = re.compile(r"\(0x1F800044 >> 16\)")
SPAD_LO = re.compile(r"\(0x1F800044 & 0xFFFF\)")
SPAD_CAST = re.compile(r"\(\(?(?:volatile\s+)?(\w+)\s*\*\)\s*g_Task\b")
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


def spad_type(text: str, image: str) -> str | None:
    """Return the work record type of the scratchpad cell for a context, or None.

    The type is the one the context itself casts the cell to most often, else the image family's
    record; a type the context does not define as a complete struct gives None.
    """
    views = SPAD_CAST.findall(text)
    name = max(set(views), key=views.count) if views else None
    name = name or next((t for p, t in SPAD_TYPES if image.startswith(p)), None)
    if name and re.search(r"\}\s*" + name + r"\s*;", text):
        return name
    return None


def typed_cell(text: str, image: str) -> str:
    """Return the context with ``g_SpadView``, a pointer to the work record, declared last.

    The cell itself stays `u8 *g_Task`: the record may be defined after that declaration.
    """
    name = spad_type(text, image)
    if name is None:
        return text
    return text.rstrip("\n") + f"\nextern {name} *{SPAD_VIEW_NAME};\n"


def typed_asm(text: str) -> str:
    """Return the assembly with the 0x1F800044 cell read as the symbol ``g_SpadView``."""
    return SPAD_LO.sub(
        f"%lo({SPAD_VIEW_NAME})", SPAD_HI.sub(f"%hi({SPAD_VIEW_NAME})", text)
    )


def wrap_cell(body: str, name: str, root: Path, func: Func) -> str:
    """Spell the cell as `((T *)g_Task)` in a body, unless the unit defines a view macro."""
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


def drafts(root: Path, func: Func, ctx: Path) -> dict[str, str]:
    """Return the body that each m2c variant gives, one per distinct text."""
    asm = asm_path(root, func)
    out: dict[str, str] = {}
    seen: set[str] = set()
    work = spad_type(ctx.read_text(encoding="utf-8"), func.image)
    if work and asm:
        asm = root / WORK / "asm" / func.image.replace("/", "+") / asm.name
        asm.parent.mkdir(parents=True, exist_ok=True)
        asm.write_text(typed_asm(asm_path(root, func).read_text("utf-8")), "utf-8")
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
        if body and work and SPAD_VIEW_NAME in body:
            body = wrap_cell(body, work, root, func)
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
    result = subprocess.run(
        [sys.executable, str(root / "tools/dups.py"), "near", "--full"],
        cwd=root,
        capture_output=True,
        check=True,
        text=True,
    )
    rows = result.stdout.splitlines()[1:]
    return {r.split("\t")[0] for r in rows if r.strip()}


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
        chosen = random.Random(SAMPLE_SEED).sample(
            chosen, min(args.sample, len(chosen))
        )
    return sorted(chosen, key=lambda f: (f.size, f.ref))


def stream(root: Path, funcs: list[Func]) -> Iterator[tuple[Func, dict]]:
    """Yield each function with its drafts; m2c runs ``JOBS`` at a time, in order."""
    cache: dict[str, Path] = {}
    contexts = {id(f): context(root, f, cache) for f in funcs}
    with ThreadPoolExecutor(JOBS) as pool:
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
    parser.add_argument("--image", action="append", help="image id or prefix")
    parser.add_argument("--sample", type=int, help="sweep N functions at random")
    args = parser.parse_args(argv)
    funcs = select(args, load_index(ROOT))
    print(f"sweeping {len(funcs)} functions", file=sys.stderr, flush=True)
    path = ROOT / RESULTS
    path.parent.mkdir(parents=True, exist_ok=True)
    hits = 0
    with path.open("a", encoding="utf-8") as log:
        for func, found in stream(ROOT, funcs):
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
