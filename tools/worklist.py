#!/usr/bin/env python3
"""Rank the functions that are still assembly, cheapest route first.

    tools/worklist.py [-n 30] [--image SUBSTR] [--route ROUTE] [--tsv | --jsonl]

One row per `INCLUDE_ASM` function; a `HAND_ASM` unit is done and has no row. The route
is the cheapest known way in, in the order docs/matching.md tries them:

    template0   a matched template with no differing instruction: tools/template_try.py REF
    generator   a mechanical shape that tools/gen_body.py can write a body for
    template    a template with a few differing instructions: tools/template_try.py REF,
                or tools/template_diff.py REF to see them
    plain       no known route: m2c draft, diagnose loop, permuter

A function recorded in `config/attempts.jsonl` sorts after the untried ones of
its route and shows its attempts. Build first (`meson compile -C build/meson`): the function index
comes from the built images. Templates need `rapidfuzz`; without it the command stops with exit 2
and the install step (`tools/setup.sh --dev --matching`).
"""

from __future__ import annotations

import argparse
import contextlib
import io
import json
import sys
from dataclasses import dataclass
from pathlib import Path

import dups
import gen_body

ROOT = Path(__file__).resolve().parent.parent
ROUTES = ("template0", "generator", "template", "plain")
GENERATED = ("call-seq", "store-seq", "spad", "dispatch", "straight")
EDITS = 3  # template_diff.py takes up to this many edits
HINT_WIDTH = 150


@dataclass(frozen=True)
class Row:
    """One assembly function and its cheapest route."""

    ref: str
    words: int
    route: str
    how: str
    hint: str


def _score(score: object) -> str:
    """A percent number, or a string that states its own unit."""
    if score is None:
        return ""
    return f"{score:g}%" if isinstance(score, (int, float)) else str(score)


def attempts(path: Path = ROOT / "config/attempts.jsonl") -> dict[str, str]:
    """Return the recorded attempts for each function."""
    result: dict[str, list[str]] = {}
    for line in path.read_text(encoding="utf-8").splitlines():
        if not line.strip():
            continue
        row = json.loads(line)
        note = "; ".join(
            part
            for part in (row["tried"], row["first_diff"], _score(row["score"]))
            if part
        )
        result.setdefault(row["function"], []).append(note or "attempt recorded")
    return {ref: " | ".join(notes) for ref, notes in result.items()}


def is_hand_asm(src: str) -> bool:
    """True when the unit marks its function `HAND_ASM`: written in assembly, so done."""
    return "\nHAND_ASM " in (ROOT / src).read_text(encoding="utf-8")


def templates() -> dict[str, tuple[str, int]]:
    """Return the cheapest template of each assembly function: ref -> (template, diff_count)."""
    out, err = io.StringIO(), io.StringIO()
    try:
        with contextlib.redirect_stdout(out), contextlib.redirect_stderr(err):
            dups.main(["near", "--full", "--jsonl"])
    except SystemExit as error:
        message = str(error.code) if error.code else err.getvalue().strip()
        if "rapidfuzz" in message:
            print(
                "worklist: needs rapidfuzz. Run: tools/setup.sh --dev --matching",
                file=sys.stderr,
            )
            raise SystemExit(2) from None
        print("worklist: no templates (" + message + ")", file=sys.stderr)
        return {}
    rows = (json.loads(line) for line in out.getvalue().splitlines())
    return {r["target"]: (r["template"], r["diff_count"]) for r in rows}


def writable(f: gen_body.Func, tree: gen_body.Tree, names: gen_body.Names) -> bool:
    """True when gen_body can write a body for ``f`` (a SKIP row would only waste the try)."""
    try:
        gen_body.body_for(f, tree, names)
    except gen_body.Unsupported:
        return False
    return True


def rank(image: str = "", route: str = "") -> list[Row]:
    """Return the worklist: cheapest route first, untried before tried, then by size."""
    near = templates()
    notes = attempts()
    tree, names = gen_body.Tree(), gen_body.Names()
    shapes = {
        f.ref: shape for shape, f, _ in gen_body.measure(gen_body.asm_functions())
    }
    rows = []
    for f in gen_body.asm_functions():
        if f.src is None or image not in f.image or is_hand_asm(f.src):
            continue
        tmpl = near.get(f.ref)
        if tmpl and tmpl[1] == 0:
            kind, how = "template0", f"template_try.py: {tmpl[0]}"
        elif shapes[f.ref] in GENERATED and writable(f, tree, names):
            kind, how = "generator", f"gen_body.py {shapes[f.ref]}"
        elif tmpl and tmpl[1] <= EDITS:
            kind, how = "template", f"template_diff.py: {tmpl[0]} ({tmpl[1]} diff)"
        else:
            kind, how = "plain", "m2c draft"
        if not route or route == kind:
            rows.append(Row(f.ref, len(f.words), kind, how, notes.get(f.ref, "")))
    return sorted(
        rows, key=lambda r: (ROUTES.index(r.route), bool(r.hint), r.words, r.ref)
    )


def main(argv: list[str] | None = None) -> int:
    """Print the first rows of the worklist."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "-n", type=int, default=30, help="rows to print, 0 for all (30)"
    )
    parser.add_argument(
        "--image", default="", help="keep images whose name contains this"
    )
    parser.add_argument("--route", choices=ROUTES, default="", help="keep one route")
    output = parser.add_mutually_exclusive_group()
    output.add_argument(
        "--tsv", action="store_true", help="tab-separated, with the full attempts"
    )
    output.add_argument(
        "--jsonl", action="store_true", help="one JSON object per row, keys as --tsv"
    )
    args = parser.parse_args(argv)
    rows = rank(args.image, args.route)
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
