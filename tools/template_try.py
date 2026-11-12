#!/usr/bin/env python3
"""Try matched C functions as the bodies of assembly functions, and keep the exact ones.

    tools/template_try.py REF [--dry-run]
    tools/template_try.py ROWS.tsv [--dry-run]

REF is `TARGET@NAME` or `TARGET@0xADDRESS`; the tool uses its closest lifted template
(`tools/template_diff.py` finds it). Each row of ROWS.tsv is `TARGET@NAME`, a tab, then
`TEMPLATE@NAME`: the assembly function and the lifted function it resembles (other columns are
ignored). The tool lines up the template's instructions with the target's. Where
only a relocation symbol differs (`%hi/%lo(D_x)`, `jal func_x`), it names the target's symbol in
the template's C and declares it like the template's; where only an immediate differs and that
literal occurs once in the body, it writes the target's literal. It then puts the body in place of
the target's `INCLUDE_ASM(name);` line (`tools/try_body.py`) and runs `tools/match.sh`. An exact
result stays in the tree; any other result restores the files. One line per row: `EXACT`,
`REMAP-EXACT` (after a rename or literal), `FAIL` with the number of differing instructions and the
first difference, `SKIP` with the reason. A row that ran stays a lead: run `meson compile -C
build/meson check-<image>`, then give the body its evidence-based name and the shared-body
treatment of docs/conventions.md.
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path

import template_diff
import try_body
from bof3.source.ctext import find_definition, read
from bof3.source.index import Func, find, load_index
from bof3.source.remap import (
    Plan,
    align,
    declaration,
    diff_count,
    macro_edits,
    object_insns,
    read_listing,
    rename,
    substitute_literals,
    target_insns,
    used_defines,
)

ROOT = Path(__file__).resolve().parent.parent


def locate(src: str, name: str, depth: int = 3) -> tuple[str, int, int] | None:
    """Find where ``name`` is defined for the C file ``src``, or in a header it includes."""
    for path in try_body.closure(ROOT, src, depth):
        span = find_definition(read(ROOT, path), name)
        if span:
            return path, *span
    return None


def analyse(target: Func, template: Func) -> Plan | None:
    """Line up the template's instructions with the target's; None when that is not possible."""
    if not template.src:
        return None
    obj = template.src.replace("/", "+") + ".o"
    theirs = object_insns(ROOT, obj, template.name, len(template.words))
    listing = read_listing(ROOT, target.image)
    lines = [listing.get(target.addr + 4 * i) for i in range(len(target.words))]
    if theirs is None or None in lines:
        return None
    return align(theirs, target_insns(target.words, lines), template.words)  # type: ignore[arg-type]


def remap(plan: Plan, template: Func, body: str) -> str | None:
    """Apply the plan's renames and literals to ``body`` and append the declarations."""
    texts = [read(ROOT, f) for f in try_body.closure(ROOT, template.src or "", 6, True)]
    decls = []
    for name in plan.keep:
        found = next((d for t in texts if (d := declaration(t, name))), None)
        if found:
            decls.append("@decl " + found)
    for old, new in plan.symbols.items():
        body = rename(body, old, new) or ""
        if not body:
            return None
        found = next((d for t in texts if (d := declaration(t, old))), None)
        if found:
            decls.append("@decl " + re.sub(r"\b" + re.escape(old) + r"\b", new, found))
    pairs, defines = macro_edits(body, plan.literals, texts)
    decls += ["@decl " + d for d in defines]
    if pairs:
        body = substitute_literals(body, pairs) or ""
    named = {d.split()[1] for d in defines}
    decls += [
        "@decl " + d for d in used_defines(body, texts) if d.split()[1] not in named
    ]
    return "\n".join([body, *decls]) if body else None


def closest_row(funcs: list[Func], ref: str) -> str:
    """Return the row for ``ref`` and its closest lifted template."""
    target = find(funcs, ref)
    ranked = template_diff.candidates(funcs, target, 1)
    if not ranked:
        raise SystemExit(
            f"template_try: no lifted function to use as a template for {ref}"
        )
    template = ranked[0][1]
    return f"{target.image}@{target.name}\t{template.image}@{template.name}"


def attempt(funcs: list[Func], row: str, dry: bool) -> str:
    """Try one row and return its report line."""
    target_ref, template_ref = row.split("\t")[:2]
    target, template = find(funcs, target_ref), find(funcs, template_ref)
    if target.status != "ASM" or not target.src:
        return f"SKIP {target_ref} is not an INCLUDE_ASM function"
    if template.status != "C" or not template.src:
        return f"SKIP {template_ref} is not lifted C"
    if f"INCLUDE_ASM({target.name});" not in read(ROOT, target.src):
        return f"SKIP {target_ref} already has a body"
    where = locate(template.src, template.name)
    if where is None:
        return f"SKIP no definition of {template.name} under {template.src}"
    source, start, end = where
    body = re.sub(
        r"\b" + re.escape(template.name) + r"\b",
        target.name,
        read(ROOT, source)[start:end],
    ).strip("\n")
    pair = f"{target_ref} <- {template_ref}"
    plan = analyse(target, template)
    kind, differ = "EXACT", diff_count(template.words, target.words)
    if plan:
        differ = plan.total
        if plan.hard:
            return f"FAIL {pair}: {differ} differ, {plan.first_hard}"
        body = remap(plan, template, body) or ""
        if not body:
            return (
                f"FAIL {pair}: {differ} differ, a symbol or literal is not in the body"
            )
        kind = "REMAP-EXACT" if plan.edits else "EXACT"
    if dry:
        return f"DRY {pair}\n{body}"
    status, detail = try_body.attempt(ROOT, target, body)
    if status == "EXACT":
        return f"{kind} {pair} in {detail}"
    return f"{status} {pair}: {differ} differ, {detail}"


def main(argv: list[str] | None = None) -> int:
    """Try every row."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "rows", help="TARGET@NAME, or a TSV of TARGET@NAME and TEMPLATE@NAME"
    )
    parser.add_argument(
        "--dry-run", action="store_true", help="print each body; change nothing"
    )
    args = parser.parse_args(argv)
    funcs = load_index(ROOT)
    source = Path(args.rows)
    if source.is_file():
        lines = source.read_text(encoding="utf-8").splitlines()
    elif "@" in args.rows:
        lines = [closest_row(funcs, args.rows)]
    else:
        parser.error(f"{args.rows}: not a rows file and not a TARGET@NAME")
    for row in lines:
        if row.strip() and not row.startswith("#"):
            print(attempt(funcs, row, args.dry_run), flush=True)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
