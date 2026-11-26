#!/usr/bin/env python3
"""Build several full bodies of one function in turn and stop at the first exact match.

    tools/try_variants.py TARGET@0xADDRESS SOURCE.c VARIANTS.py

VARIANTS.py is Python that defines `NAME` (the function name) and `V`, a dict of tag to the
complete function text. Each variant replaces the existing `MATCH`/`NON_MATCHING` definition of NAME
in SOURCE.c, or its `INCLUDE_ASM(NAME);` line when there is none, and `tools/match.sh --diff`
judges it. A line per variant: `<tag> => MATCH`, `<tag> => N diff | <first difference>` or `<tag> => ERR ...`.
The first match stays in SOURCE.c and ends the run; otherwise SOURCE.c is restored and the last
line is `best (N, tag)`. Run `check-<image>` on a match.

    tools/try_variants.py exe/slus_004_22@0x801530D0 src/engine/area/map/Area_CellDrawRing.c variants.py
"""

import argparse
import re
from pathlib import Path

from bof3.adapters.match import run_match
from bof3.core.paths import ROOT


def function_span(source, name):
    """Return the start and end of the definition to replace, else of the INCLUDE_ASM line."""
    found = re.search(
        rf"^(?:MATCH|NON_MATCHING)[^\n]*\b{name}\([^{{]*\{{\n.*?^\}}\n",
        source,
        re.S | re.M,
    )
    if not found:
        found = re.search(rf"INCLUDE_ASM\({name}\);\n", source)
    return found.start(), found.end()


def main():
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("function", help="TARGET@0xADDRESS")
    parser.add_argument("source", help="C file of the function")
    parser.add_argument("variants", help="Python file that defines NAME and V")
    args = parser.parse_args()
    scope = {}
    exec(Path(args.variants).read_text(), scope)
    name, variants = scope["NAME"], scope["V"]
    path = Path(args.source)
    base = path.read_text()
    start, end = function_span(base, name)
    best = None
    try:
        for tag, text in variants.items():
            path.write_text(base[:start] + text.rstrip("\n") + "\n" + base[end:])
            result = run_match(ROOT, "--diff", args.function, merged=True)
            lines, differing = result.lines, result.differing
            if result.matched:
                print(tag, "=> MATCH")
                return
            if not differing:
                print(tag, "=> ERR", "\n".join(lines)[-260:].replace("\n", " / "))
                continue
            first = differing[0]
            print(f"{tag} => {len(differing)} diff | {first[2:38]} <> {first[47:84]}")
            if best is None or len(differing) < best[0]:
                best = (len(differing), tag)
    except BaseException:
        path.write_text(base)
        raise
    path.write_text(base)
    print("best", best)


if __name__ == "__main__":
    main()
