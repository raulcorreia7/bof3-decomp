#!/usr/bin/env python3
"""Put a new C body in a function's draft block, keeping INCLUDE_ASM in the `#else`.

    tools/draft_swap.py TARGET@NAME BODY.c      tools/draft_swap.py TARGET@0xADDR BODY.c

The body file replaces everything between `#ifdef NON_MATCHING` and its `#else` in the function's
C file. A function that is still a bare `INCLUDE_ASM(NAME);` gets the block around it, so the
open build keeps the assembly. The old body is saved under `work/<image>/<ADDR>/` and its path
prints; the rest of the file does not change. The new body carries the status marker like any
draft (include/match/match.h, tools/check_markers.py).

    tools/draft_swap.py emi/battle/battle/03@0x801DAAE4 draft.c
    swapped src/overlays/battle/battle/03/Battle_BuildTurnOrder.c
    saved work/emi/battle/battle/03/801DAAE4/before.c
"""

from __future__ import annotations

import argparse
import re
from pathlib import Path

from bof3.source.ctext import read
from bof3.source.index import Func, find, load_index

ROOT = Path(__file__).resolve().parent.parent
DIRECTIVE = re.compile(r"^[ \t]*#[ \t]*(if|ifdef|ifndef|elif|else|endif)\b", re.M)
GUARD = re.compile(
    r"^[ \t]*#[ \t]*(?:ifdef[ \t]+NON_MATCHING"
    r"|if[ \t]+defined\([ \t]*NON_MATCHING[ \t]*\))[ \t]*$",
    re.M,
)
INCLUDE = re.compile(r"INCLUDE_ASM\(\s*(\w+)\s*\)")
INCLUDE_LINE = re.compile(r"^[ \t]*INCLUDE_ASM\(\s*(\w+)\s*\);[^\n]*$", re.M)


def holds(text: str, name: str) -> bool:
    """Say whether ``text`` carries ``name``'s INCLUDE_ASM."""
    return any(m.group(1) == name for m in INCLUDE.finditer(text))


def draft_block(text: str, name: str) -> tuple[int, int] | None:
    """Return the end of ``name``'s guard line and the start of its alternative branch."""
    for guard in GUARD.finditer(text):
        depth, alternative = 0, None
        for d in DIRECTIVE.finditer(text, guard.end()):
            if d.group(1) in ("if", "ifdef", "ifndef"):
                depth += 1
            elif d.group(1) == "endif":
                if depth == 0:
                    if alternative is not None and holds(
                        text[alternative : d.start()], name
                    ):
                        return guard.end(), alternative
                    break
                depth -= 1
            elif depth == 0 and alternative is None:
                alternative = d.start()
    return None


def swap(text: str, name: str, body: str) -> tuple[str, str | None]:
    """Return ``text`` with ``name``'s draft block holding ``body``, and the old body."""
    body = body.strip("\n")
    found = draft_block(text, name)
    if found is not None:
        start, end = found
        old = text[start:end].strip("\n")
        return text[:start] + "\n" + body + "\n" + text[end:], old
    line = next((m for m in INCLUDE_LINE.finditer(text) if m.group(1) == name), None)
    if line is None:
        raise SystemExit(f"draft_swap: {name} has no INCLUDE_ASM: not an open function")
    block = f"#ifdef NON_MATCHING\n{body}\n#else\n{line.group(0).strip()}\n#endif"
    return text[: line.start()] + block + text[line.end() :], None


def save(root: Path, func: Func, old: str) -> str:
    """Write the old body under ``work/`` and return its repo path, never replacing one."""
    folder = root / "work" / func.image / f"{func.addr:08X}"
    folder.mkdir(parents=True, exist_ok=True)
    path, n = folder / "before.c", 2
    while path.exists():
        path, n = folder / f"before-{n}.c", n + 1
    path.write_text(old + "\n", encoding="utf-8")
    return path.relative_to(root).as_posix()


def main(argv: list[str] | None = None) -> int:
    """Swap one body into its function's draft block."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("ref", help="TARGET@NAME or TARGET@0xADDRESS")
    parser.add_argument("body", type=Path, help="the C file that holds the new body")
    args = parser.parse_args(argv)
    func = find(load_index(ROOT), args.ref)
    if not func.src:
        raise SystemExit(f"draft_swap: {args.ref} has no C file: not a C unit")
    body = args.body.read_text(encoding="utf-8")
    if not body.strip():
        raise SystemExit(f"draft_swap: {args.body}: empty body")
    text = read(ROOT, func.src)
    new, old = swap(text, func.name, body)
    saved = save(ROOT, func, old) if old is not None else None
    (ROOT / func.src).write_text(new, encoding="utf-8")
    print(f"{'swapped' if saved else 'created'} {func.src}")
    if saved:
        print(f"saved {saved}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
