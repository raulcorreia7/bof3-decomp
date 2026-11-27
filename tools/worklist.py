#!/usr/bin/env python3
"""List the functions that are still assembly, shortest first.

    tools/worklist.py [-n 30] [--image GLOB ...] [--tsv | --jsonl]
    tools/worklist.py --image GLOB [--image GLOB ...] [--except NAME ...] --order strategy
                      [--measure] [-n N] [--jsonl]

One row per `INCLUDE_ASM` function; a `HAND_ASM` unit is done and has no row. The route column
reads `plain` (an m2c draft, the diagnose loop, the permuter). A function recorded in
`config/attempts.jsonl` sorts after the untried ones and shows its attempts. Build first
(`meson compile -C build/meson`): the function index comes from the built images.

`--order strategy` lists one lane's open functions in the order that pays most first: promote (the
draft matches), twin (open functions with one body), near (sched, regalloc or frame, at most four
hunks), medium (shape), undrafted (150 words or fewer), hard, stub (a draft under half of retail),
blocked (nocompile). A unit-order function (code before it in its file has another size) follows its
culprit, the lowest-address open function of the file, and names it in `after`. `--image` takes a
directory glob (`emi/battle` covers `emi/battle/...`); `--except` drops functions by name.
Each draft is measured with `tools/match.sh --diff` once per source hash and kept in `build/worklist/`;
`--measure` measures the lane's drafts again, and an unmeasured draft shows kind `unmeasured`.
"""

from __future__ import annotations

import argparse
import difflib
import fnmatch
import hashlib
import json
import re
import sys
import time
from dataclasses import dataclass, replace
from pathlib import Path

from bof3.adapters.attempts import PATH as ROW_PATH
from bof3.adapters.attempts import read_lines
from bof3.adapters.match import run_match
from bof3.attempts import parse
from bof3.core.paths import ROOT
from bof3.match import side_by_side
from bof3.source.index import Func, load_index

HINT_WIDTH = 150
CACHE = ROOT / "build/worklist"
SHORT = 150  # an undrafted function of this many words or fewer is cheap
TWIN_WORDS = 8
UNIT_ORDER = ("begins at", "cannot isolate", "no function starts")


@dataclass(frozen=True)
class Row:
    """One assembly function."""

    ref: str
    words: int
    route: str
    how: str
    hint: str


def attempt_notes(path: Path = ROOT / ROW_PATH) -> dict[str, list[str]]:
    """Return the note of each recorded attempt, per function."""
    result: dict[str, list[str]] = {}
    for line in read_lines(path):
        row = parse(line)
        result.setdefault(row.function, []).append(row.note)
    return result


def attempts(path: Path = ROOT / ROW_PATH) -> dict[str, str]:
    """Return the recorded attempts for each function."""
    return {ref: " | ".join(n) for ref, n in attempt_notes(path).items()}


def in_images(image: str, globs: list[str]) -> bool:
    """True when ``image`` is under one of the directory globs (all images when empty)."""
    return not globs or any(
        fnmatch.fnmatch(image, g) or fnmatch.fnmatch(image, g.rstrip("/") + "/*")
        for g in globs
    )


def is_hand_asm(src: str) -> bool:
    return "\nHAND_ASM " in (ROOT / src).read_text(encoding="utf-8")


def asm_functions(root: Path = ROOT) -> list[Func]:
    return [f for f in load_index(root) if f.status == "ASM"]


def rank(images: list[str] | None = None) -> list[Row]:
    """Return the worklist: untried before tried, then by size."""
    notes = attempts()
    rows = [
        Row(f.ref, len(f.words), "plain", "m2c draft", notes.get(f.ref, ""))
        for f in asm_functions()
        if f.src is not None
        and in_images(f.image, images or [])
        and not is_hand_asm(f.src)
    ]
    return sorted(rows, key=lambda r: (bool(r.hint), r.words, r.ref))


@dataclass(frozen=True)
class Pick:
    """One open function in strategy order."""

    ref: str
    name: str
    words: int
    tier: str
    kind: str
    tries: int
    after: str
    twin: str


def is_draft(f: Func) -> bool:
    text = (ROOT / f.src).read_text(encoding="utf-8")
    return re.search(rf"#else\s*\nINCLUDE_ASM\({f.name}\)", text) is not None


def normalize(words: tuple[int, ...]) -> tuple[int, ...]:
    """Mask immediates and jump targets: the same body at other addresses compares equal."""
    return tuple(
        w >> 26 if w >> 26 in (2, 3) else w if w >> 26 == 0 else w & ~0xFFFF
        for w in words
    )


def twin_groups(funcs: list[Func]) -> dict[str, str]:
    """Return ref -> group id (the lowest ref) for open functions that share a normalized body."""
    groups: dict[tuple[int, ...], list[str]] = {}
    for f in funcs:
        if len(f.words) >= TWIN_WORDS:
            groups.setdefault(normalize(f.words), []).append(f.ref)
    return {r: min(refs) for refs in groups.values() if len(refs) > 1 for r in refs}


def classify(retail: list, cand: list) -> dict:
    """Return the first-diff kind of a candidate against retail, from the two listings."""
    ops = difflib.SequenceMatcher(
        None, [i[1] for i in retail], [i[1] for i in cand], autojunk=False
    )
    hunks = rows = 0
    for tag, r1, r2, c1, _ in ops.get_opcodes():
        if tag == "equal":
            rows += sum(retail[r1 + k][2] != cand[c1 + k][2] for k in range(r2 - r1))
        else:
            hunks += 1
    delta = len(cand) - len(retail)
    same = sorted(i[1] for i in retail) == sorted(i[1] for i in cand)
    if not hunks:
        kind = "regalloc"
    elif same and not delta:
        kind = "sched"
    elif "addiu" == retail[0][1] and "sp" in retail[0][2]:
        kind = "frame"
    else:
        kind = "shape"
    far = abs(delta) > 0.25 * len(retail) or hunks > 20
    return {"kind": kind, "hunks": hunks, "rows": rows, "far": far, "cand": len(cand)}


def measure_draft(f: Func) -> dict:
    """Run ``match.sh --diff`` on one draft."""
    result = run_match(ROOT, "--diff", f.ref, merged=True)
    if result.exact:
        return {"kind": "match", "cand": len(f.words)}
    text = result.output
    if "differs:" not in text:
        unit = any(m in text for m in UNIT_ORDER)
        return {"kind": "unit-order" if unit else "nocompile", "cand": len(f.words)}
    return classify(*side_by_side(result))


def measured(f: Func, refresh: bool) -> dict | None:
    """Return the cached measurement of a draft, measuring it when ``refresh``."""
    digest = hashlib.sha1((ROOT / f.src).read_bytes()).hexdigest()[:12]
    stem = f"{f.image.replace('/', '+')}@0x{f.addr:08X}.{digest}"
    old = sorted(CACHE.glob(stem + ".*.json"))
    if old and not refresh:
        return json.loads(old[-1].read_text(encoding="utf-8"))
    if not refresh:
        return None
    row = measure_draft(f)
    CACHE.mkdir(parents=True, exist_ok=True)
    (CACHE / f"{stem}.{time.time_ns()}.json").write_text(
        json.dumps(row), encoding="utf-8"
    )
    return row


def place(f: Func, m: dict | None, draft: bool, tries: int, twin: bool):
    """Return (tier, kind, sort key) of one function."""
    w = len(f.words)
    if twin and (m is None or m["kind"] not in ("match", "nocompile")):
        return (
            "twin",
            m["kind"] if m else ("unmeasured" if draft else "undrafted"),
            (1, 0, w, ""),
        )
    if not draft:
        return (
            ("undrafted", "undrafted", (4, 0, w, ""))
            if w <= SHORT
            else ("hard", "undrafted", (5, tries, w, ""))
        )
    if m is None:
        return "medium", "unmeasured", (3, 0, w, "")
    kind = m["kind"]
    if kind == "match":
        return "promote", kind, (0, 0, w, "")
    if kind == "nocompile":
        return "blocked", kind, (9, 0, w, "")
    if m["cand"] * 2 < w:
        return "stub", "stub", (6, 0, w, "")
    if kind in ("sched", "regalloc", "frame") and m["hunks"] <= 4:
        return "near", kind, (2, m["rows"] + m["hunks"] * 5, w, "")
    if m.get("far"):
        return "hard", kind, (5, tries, w, "")
    return "medium", kind, (3, 0, w, "")


def strategy(images: list[str], skip: list[str], refresh: bool = False) -> list[Pick]:
    """Return one lane's open functions in strategy order."""
    open_funcs = [f for f in asm_functions() if f.src and not is_hand_asm(f.src)]
    groups = twin_groups(open_funcs)
    notes = attempt_notes()
    first: dict[str, Func] = {}
    for f in open_funcs:
        if f.src not in first or f.addr < first[f.src].addr:
            first[f.src] = f
    keyed, shifted = {}, []
    for f in open_funcs:
        if not in_images(f.image, images) or f.name in skip:
            continue
        draft = is_draft(f)
        m = measured(f, refresh) if draft else None
        tries = len(notes.get(f.ref, []))
        tier, kind, key = place(f, m, draft, tries, f.ref in groups)
        pick = Pick(
            f.ref, f.name, len(f.words), tier, kind, tries, "", groups.get(f.ref, "")
        )
        if tier == "twin":
            key = (1, 0, 0, groups[f.ref])
        keyed[f.ref] = (key, f.addr, pick)
        if kind == "unit-order" and first[f.src] is not f:
            shifted.append((f, pick))
    for f, pick in shifted:
        culprit = first[f.src]
        if culprit.ref in keyed:
            base = keyed[culprit.ref][0]
        else:
            m = measured(culprit, False) if is_draft(culprit) else None
            base = place(culprit, m, m is not None, 0, False)[2]
        blocked = replace(pick, tier="blocked", after=culprit.ref)
        keyed[f.ref] = (base + (1,), f.addr, blocked)
    order = sorted(keyed.values(), key=lambda t: (t[0], t[1]))
    return [p for _, _, p in order]


def main(argv: list[str] | None = None) -> int:
    """Print the first rows of the worklist."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "-n", type=int, default=30, help="rows to print, 0 for all (30)"
    )
    parser.add_argument(
        "--image",
        action="append",
        default=[],
        metavar="GLOB",
        help="keep images under this directory glob (repeat for more)",
    )
    parser.add_argument(
        "--except",
        dest="skip",
        action="append",
        default=[],
        metavar="NAME",
        help="drop a function by name (repeat for more); with --order",
    )
    parser.add_argument("--order", choices=("strategy",), help="the lane order")
    parser.add_argument(
        "--measure", action="store_true", help="measure the drafts again; with --order"
    )
    output = parser.add_mutually_exclusive_group()
    output.add_argument(
        "--tsv", action="store_true", help="tab-separated, with the full attempts"
    )
    output.add_argument(
        "--jsonl", action="store_true", help="one JSON object per row, keys as --tsv"
    )
    args = parser.parse_args(argv)
    if args.order:
        picks = strategy(args.image, args.skip, args.measure)
        shown = picks[: args.n] if args.n else picks
        for p in shown:
            if args.jsonl:
                print(json.dumps(p.__dict__, ensure_ascii=False))
            else:
                print(
                    f"{p.ref:<44} {p.name:<32} {p.words:>5} {p.tier:<9} {p.kind:<10}"
                    f" {p.tries:>2} {p.after or '-':<44} {p.twin or '-'}"
                )
        print(f"{len(shown)} of {len(picks)} open functions", file=sys.stderr)
        return 0
    rows = rank(args.image)
    shown = rows[: args.n] if args.n else rows
    for r in shown:
        if args.jsonl:
            print(
                json.dumps(
                    {
                        "function": r.ref,
                        "words": r.words,
                        "route": r.route,
                        "how": r.how,
                        "hint": r.hint,
                    },
                    ensure_ascii=False,
                )
            )
            continue
        if args.tsv:
            print(f"{r.ref}\t{r.words}\t{r.route}\t{r.how}\t{r.hint}")
            continue
        note = f"  tried: {r.hint[:HINT_WIDTH]}" if r.hint else ""
        print(f"{r.ref:<44} {r.words:>5}  {r.how}{note}")
    print(f"{len(shown)} of {len(rows)} assembly functions", file=sys.stderr)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
