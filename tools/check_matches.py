#!/usr/bin/env python3
"""Fail when a function that is lifted MATCH C at the merge base is not MATCH C at HEAD.

A function counts as MATCH C in an image when a `MATCH` definition reaches the image's sources:
a file in the image's folder under `src/` (or in an engine module folder) or a file such a file includes by path (function files,
shared headers). Its address comes from `config/symbols/<image>.toml` by name; a `func_<ADDR>`
name carries it. A file that two images share (an engine module folder) counts a `func_<ADDR>`
function only for the image whose splat address range holds the address, so renaming an executable
function away from its address name loses nothing in the other image. The comparison is per image
by address, so a rename, a fold into a shared header, a regrouping and a move all pass; an
`INCLUDE_ASM` or a `NON_MATCHING` draft in its place fails.

A deliberate downgrade passes with a commit message line between the merge base and HEAD:

    Match-Removed: <image>@0x<ADDR> <reason>

Usage: python3 tools/check_matches.py REF [HEAD]
"""

from __future__ import annotations

import io
import posixpath
import re
import subprocess
import sys
import tarfile
from pathlib import Path

from bof3.adapters.config import symbols_text
from bof3.adapters.git import git, merge_base
from bof3.core.paths import ROOT
from bof3.resolve.ids import source_folder
from bof3.symbols import parse

DEFINITION = re.compile(r"^MATCH\b[^;{}]*?\b(\w+)\s*\(", re.M)
INCLUDE = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.M)
ADDRESS_NAME = re.compile(r"func_([0-9A-Fa-f]{8})$")
ENGINE_IMAGES = ("exe/slus_004_22", "emi/etc/game/00")
VRAM = re.compile(r"^\s*vram:\s*(0x[0-9A-Fa-f]+)", re.M)
REMOVED = re.compile(r"^Match-Removed:\s*(\S+@0x[0-9A-Fa-f]+)", re.M)


def address_range(root: Path, rev: str, image: str) -> tuple[int, int] | None:
    """The lowest and highest address the image's `splat.yaml` places, or None without one."""
    text = git("show", f"{rev}:config/{image}/splat.yaml", root=root, check=False)
    starts = [int(v, 16) for v in VRAM.findall(text)]
    return (min(starts), max(starts)) if starts else None


def lifted(root: Path, rev: str) -> dict[str, str]:
    """`<image>@0x<ADDR>` -> name of every MATCH function the images compile at `rev`."""
    tar = subprocess.run(
        ["git", "archive", rev, "src"], cwd=root, capture_output=True, check=False
    ).stdout
    if not tar:
        return {}  # no src/ at this revision
    with tarfile.open(fileobj=io.BytesIO(tar)) as archive:
        text = {
            m.name: (archive.extractfile(m) or io.BytesIO())
            .read()
            .decode("utf-8", "replace")
            for m in archive
            if m.isfile() and m.name.endswith((".c", ".h"))
        }
    tables = parse(symbols_text(root, rev))
    homes = {f"src/{source_folder(image)}/": image for image in tables}
    reach: dict[str, set[str]] = {}

    def reached(path: str) -> set[str]:
        if path not in reach:
            reach[path] = {path}
            for name in INCLUDE.findall(text[path]):
                for base in (posixpath.dirname(path), "src", "include"):
                    target = posixpath.normpath(posixpath.join(base, name))
                    if target in text:
                        reach[path] |= reached(target)
                        break
        return reach[path]

    found: dict[str, str] = {}
    spans: dict[str, tuple[int, int] | None] = {}

    def holds(image: str, addr: int) -> bool:
        if image not in spans:
            spans[image] = address_range(root, rev, image)
        span = spans[image]
        return span is None or span[0] <= addr < span[1]

    def add(image: str, name: str, *, owned: bool, shared: bool) -> None:
        row = tables[image].get(name)
        if owned and (m := ADDRESS_NAME.match(name)):
            addr = int(m[1], 16)
            if shared and not holds(image, addr):
                return
        elif (
            isinstance(row, dict) and "addr" in row and (owned or not row.get("alias"))
        ):
            addr = row["addr"]
        else:
            return
        found[f"{image}@0x{addr:08X}"] = name

    owned: dict[str, set[str]] = {}
    for path in text:
        images = [i for h, i in homes.items() if path.startswith(h)]
        if not images and path.startswith("src/engine/"):
            # a module folder holds files of both engine images
            images = [i for i in ENGINE_IMAGES if i in tables]
        for image in images:
            for file in reached(path):
                owned.setdefault(file, set()).add(image)
    for path, body in text.items():
        for name in DEFINITION.findall(body):
            images = owned.get(path) or tables
            for image in images:
                shared = image in ENGINE_IMAGES and len(images) > 1
                add(image, name, owned=path in owned, shared=shared)
    return found


def lost(root: Path, base: str, head: str) -> list[str]:
    """`<image>@0x<ADDR> <old name>` of each MATCH function of `base` that `head` lacks."""
    removed = set(
        REMOVED.findall(git("log", "--format=%B", f"{base}..{head}", root=root))
    )
    before, after = lifted(root, base), lifted(root, head)
    return [
        f"{k} {before[k]}"
        for k in sorted(before)
        if k not in after and k not in removed
    ]


def main(argv: list[str]) -> int:
    if len(argv) not in (2, 3):
        print((__doc__ or "").strip(), file=sys.stderr)
        return 2
    ref, head = argv[1], argv[2] if len(argv) == 3 else "HEAD"
    problems = lost(ROOT, merge_base(ref, head, root=ROOT), head)
    print("\n".join(problems))
    if problems:
        print(
            f"check-matches: {len(problems)} MATCH function(s) lost against {ref}; keep them, or add "
            "a 'Match-Removed: <image>@0x<ADDR> <reason>' line to a commit message"
        )
        return 1
    print(f"check-matches: every MATCH function of {ref} is still MATCH")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
