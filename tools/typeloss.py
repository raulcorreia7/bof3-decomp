#!/usr/bin/env python3
"""List declarations that got weaker between two revisions.

    tools/typeloss.py OLD NEW        tools/typeloss.py HEAD~5 HEAD        tools/typeloss.py main WORK

OLD and NEW are Git revisions; NEW may be `WORK` for the working tree. The scan reads the C
sources and headers under `src/` and `include/` (not the PsyQ headers) and reports:

- prototypes whose parameters carry fewer named types than before (a `Foo *` became `s32`);
- named functions whose prototype is gone;
- externs that lost a named type, and named externs that are gone.

Use it before a pull request that renames, moves or retypes: a lost type is a regression even
when the bytes still match.
"""

from __future__ import annotations

import argparse
import collections
import re
import subprocess
from collections.abc import Iterator
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
PROTO = re.compile(
    r"^\s*(?:static\s+)?([A-Za-z_][\w\s\*]*?[\s\*])([A-Za-z_]\w*)\s*\(([^()]*)\)\s*;",
    re.M,
)
EXTERN = re.compile(
    r"^\s*extern\s+([^;()]+?)[\s\*]+\**([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*;", re.M
)
WEAK = frozenset("s32 u32 int void u16 s16 u8 s8 char unsigned signed".split())
NEUTRAL = WEAK | {"const", "volatile", "struct"}


# Retail callees read these arguments as integers.
PROTO_INTEGER_CORRECTIONS = {
    # Masks and shifts the first argument before subtraction.
    "func_801F2E64@src/overlays/area/area075/13": (
        "void* arg0, s32 arg1",
        "s32 arg0, s32 arg1",
    ),
    # Compares, shifts and increments the first argument.
    "func_801F46C8@src/overlays/area/area082/13": (
        "void* arg0, s32 arg1, s32 arg2, s32 arg3",
        "s32 arg0, s32 arg1, s32 arg2, s32 arg3",
    ),
    # Masks and multiplies the first argument.
    "func_801F2ED4@src/overlays/area/area091/13": (
        "void* arg0, s32 arg1",
        "s32 arg0, s32 arg1",
    ),
    # Stores the first argument as halfwords and adds to the second.
    "func_801F2F3C@src/overlays/area/area095/13": (
        "void* arg0, void* arg1",
        "s32 arg0, s32 arg1",
    ),
    # Stores the first argument as halfwords and adds to the second.
    "func_801F2ECC@src/overlays/area/area096/13": (
        "void* arg0, void* arg1",
        "s32 arg0, s32 arg1",
    ),
    # Stores the third argument as color bytes.
    "func_801F48E8@src/overlays/area/area098/13": (
        "void* arg0, void* arg1, void* arg2",
        "void* arg0, void* arg1, s32 arg2",
    ),
    # Multiplies and shifts the first argument.
    "func_801F5174@src/overlays/area/area103/13": (
        "void* arg0, s32 arg1",
        "s32 arg0, s32 arg1",
    ),
    # Shifts and multiplies the first argument.
    "func_801F53F0@src/overlays/area/area103/13": ("void* arg0", "s32 arg0"),
    # Shifts the first argument to index tables.
    "func_801F3950@src/overlays/area/area140/13": (
        "void* arg0, s32 arg1",
        "s32 arg0, s32 arg1",
    ),
    # Sign-extends the third argument as a halfword.
    "func_801F36DC@src/overlays/area/area175/13": (
        "s32 arg0, s32 arg1, void* arg2",
        "s32 arg0, s32 arg1, s32 arg2",
    ),
    # Masks and multiplies the first argument.
    "func_801F0550@src/overlays/bmagic/magic003/03": ("void* arg0", "s32 arg0"),
    # Masks the first argument to select a value.
    "func_801F04D4@src/overlays/bmagic/magic114/03": ("void* arg0", "s32 arg0"),
    # Stores the third argument as color bytes.
    "func_801D1678@src/overlays/scenario/sce15ef1/00": (
        "void* arg0, void* arg1, void* arg2",
        "void* arg0, void* arg1, s32 arg2",
    ),
    # Masks the first argument to a byte.
    "func_801F7678@src/overlays/scenario/scena01/00": ("void* arg0", "s32 arg0"),
}


def sources(rev: str) -> Iterator[tuple[str, str]]:
    """Yield ``(path, text)`` for each C file of ``rev``."""
    if rev == "WORK":
        for path in sorted(ROOT.glob("src/**/*.[ch]")) + sorted(
            ROOT.glob("include/**/*.h")
        ):
            if "psyq" not in path.parts:
                yield str(path), path.read_text(encoding="utf-8", errors="ignore")
        return
    names = subprocess.run(
        ["git", "ls-tree", "-r", "--name-only", rev, "src", "include"],
        cwd=ROOT, capture_output=True, text=True, check=True,
    ).stdout.split()  # fmt: skip
    names = [n for n in names if n.endswith((".c", ".h")) and "/psyq/" not in n]
    blobs = subprocess.run(
        ["git", "cat-file", "--batch"],
        cwd=ROOT, input="".join(f"{rev}:{n}\n" for n in names).encode(),
        capture_output=True, check=True,
    ).stdout  # fmt: skip
    pos = 0
    for name in names:
        eol = blobs.index(b"\n", pos)
        size = int(blobs[pos:eol].split()[-1])
        yield name, blobs[eol + 1 : eol + 1 + size].decode(errors="ignore")
        pos = eol + 1 + size + 1


def squash(text: str) -> str:
    """Normalise spaces."""
    return re.sub(r"\s+", " ", text.replace(" *", "*")).strip()


def strength(params: str) -> int:
    """Score how much type a parameter list names: 2 per named type, 1 per pointer."""
    params = params.strip()
    if params in ("", "void"):
        return 0
    score = 0
    for param in params.split(","):
        words = re.findall(r"[A-Za-z_]\w*", param)
        if any(w not in NEUTRAL for w in words[:-1]):
            score += 2
        elif "*" in param:
            score += 1
    return score


def scan(rev: str) -> tuple[dict[str, set[tuple[str, str]]], dict[str, set[str]]]:
    """Return the prototypes and externs of ``rev`` by name.

    An address name is unique only per image, so ``func_<ADDR>`` and ``D_<ADDR>`` are keyed by its folder: the same
    address in another image is another function, and a rename must not read as a lost type.
    """
    protos: dict[str, set[tuple[str, str]]] = collections.defaultdict(set)
    externs: dict[str, set[str]] = collections.defaultdict(set)
    for path, text in sources(rev):
        for m in PROTO.finditer(text):
            if m.group(1).strip() not in ("return", "else"):
                name = m.group(2)
                if name.startswith("func_"):
                    name = f"{name}@{path.rpartition('/')[0]}"
                protos[name].add((squash(m.group(1)), squash(m.group(3))))
        for m in EXTERN.finditer(text):
            name = m.group(2)
            if name.startswith("D_"):
                name = f"{name}@{path.rpartition('/')[0]}"
            externs[name].add(squash(m.group(1)))
    return protos, externs


def lost_extern(old: set[str], new: set[str]) -> bool:
    """True when the types changed, every new one is weak and an old one was named."""
    if old == new or any(t not in WEAK and not t.startswith(tuple(WEAK)) for t in new):
        return False
    return any(t.split()[-1].rstrip("*") not in WEAK for t in old)


def main(argv: list[str] | None = None) -> int:
    """Print the report; exit 1 when a declaration got weaker."""
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument("old", help="the earlier revision")
    parser.add_argument("new", help="the later revision, or WORK for the working tree")
    args = parser.parse_args(argv)
    (fa, ea), (fb, eb) = scan(args.old), scan(args.new)
    print(f"prototypes {len(fa)} -> {len(fb)}, externs {len(ea)} -> {len(eb)}")
    weaker = [
        (n, sorted(fa[n])[:2], sorted(fb[n])[:2])
        for n in fa
        if n in fb
        and not (
            n in PROTO_INTEGER_CORRECTIONS
            and len(fa[n]) == len(fb[n]) == 1
            and any(x[1] == PROTO_INTEGER_CORRECTIONS[n][0] for x in fa[n])
            and any(x[1] == PROTO_INTEGER_CORRECTIONS[n][1] for x in fb[n])
        )
        and max(strength(x[1]) for x in fb[n]) < max(strength(x[1]) for x in fa[n])
    ]
    gone = [n for n in fa if n not in fb and not n.startswith("func_")]
    weaker_externs = [
        (n, sorted(ea[n])[:2], sorted(eb[n])[:2])
        for n in ea
        if n in eb and lost_extern(ea[n], eb[n])
    ]
    extern_gone = [n for n in ea if n not in eb and not n.startswith("D_")]
    for title, rows in (
        ("prototype weaker", weaker),
        ("named prototype gone", gone),
        ("extern lost its named type", weaker_externs),
        ("named extern gone", extern_gone),
    ):
        print(f"{title}: {len(rows)}")
        for row in rows:
            print(f"  {row}")
    return int(bool(weaker or weaker_externs))


if __name__ == "__main__":
    raise SystemExit(main())
