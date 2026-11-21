#!/usr/bin/env python3
"""Compile every source of one image as a single translation unit, to find disagreeing declarations.

    unity_check.py [--build-dir DIR] [--out DIR] [--subsystem NAME] [IMAGE...]

A check, never linked: the unit includes each `.c` of the image (but not a file of raw `u8` payload bytes), in the order the compile database
lists them, and the compiler only parses it (`-S`, the assembly is discarded). It fails on a type, a prototype or a
macro that two files declare differently, and on a static or a function defined twice. IMAGE is the
`ASM_DIR` of the image (`build/asm/emi/title/game/01`) or the part after `build/asm/`.
"""

from __future__ import annotations

import argparse
import collections
import concurrent.futures
import json
import os
import re
import subprocess
import sys
from pathlib import Path

from bof3.core.paths import ROOT

GCC = os.environ.get("PSX_GCC") or str(ROOT / "toolchains/gcc-2.7.2-psx/gcc")
GCC_DIR = os.path.dirname(os.path.realpath(GCC))
ASM_DIR = re.compile(r'-DASM_DIR=\\?"([^"\\]+)\\?"')
#: The subsystem of a source, by the folder rules of docs/subsystems.md.
FAIRY_AREAS = {f"area{n}" for n in range(175, 186)}


def subsystem(source: str) -> str:
    parts = source.split("/")
    if parts[0] != "src":
        return "Other"
    if parts[1] == "engine":
        return {"slus": "Executable", "game": "Game"}.get(parts[2], "Other")
    if parts[1] == "logo":
        return "Logo"
    if parts[1] == "shared":
        return "Shared bodies"
    if parts[1] == "overlays":
        family = parts[2]
        if family == "area":
            return "Fairy Village" if parts[3] in FAIRY_AREAS else "Area"
        return {
            "battle": "Battle",
            "bmagic": "Battle magic",
            "boss": "Boss",
            "commu": "Fairy Village",
            "menu": "Menu",
            "plchar": "Player character",
            "scenario": "Scenario",
            "title": "Title",
        }.get(family, family)
    return "Other"


#: A source that only defines raw `u8` payload arrays: the image header reads those bytes through a
#: typed extern on purpose, so the two cannot agree and the file is left out of the unit.
BYTE_BLOBS = re.compile(r"(?:u8\s+\w+\[\d*\]\s*=\s*\{[\s0-9A-Fa-fx,]*\};\s*)+")


def is_byte_blob(source: str) -> bool:
    text = (ROOT / source).read_text(errors="replace")
    text = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    text = re.sub(r"^#.*$", "", text, flags=re.M).strip()
    return bool(BYTE_BLOBS.fullmatch(text))


def images(build_dir: Path) -> dict[str, dict]:
    """Group the compile database by image: its sources in order and the compiler's arguments."""
    groups: dict[str, dict] = collections.OrderedDict()
    database = json.loads((build_dir / "compile_commands.json").read_text())
    for entry in database:
        source = os.path.normpath(os.path.join(entry["directory"], entry["file"]))
        source = os.path.relpath(source, ROOT)
        if not source.endswith(".c") or not source.startswith("src/"):
            continue
        command = entry["command"]
        found = ASM_DIR.search(command)
        if not found:
            continue
        image = found.group(1)
        group = groups.setdefault(image, {"sources": [], "args": None})
        if "--empty-on-failure" in command or "-DNON_MATCHING" in command:
            continue
        if source not in group["sources"] and not is_byte_blob(source):
            group["sources"].append(source)
        if group["args"] is None:
            group["args"] = arguments(command)
    return groups


def arguments(command: str) -> list[str]:
    """The compiler arguments of one entry without the wrapper, depfile, source and output."""
    import shlex

    words = shlex.split(command)
    start = next(i for i, w in enumerate(words) if w.endswith("cc.py")) + 1
    words = words[start:]
    out: list[str] = []
    skip = 0
    for i, word in enumerate(words):
        if skip:
            skip -= 1
            continue
        if word in ("--build-dir",):
            skip = 1
        elif word in ("-MF", "-o"):
            skip = 1
        elif word in ("-MMD", "-MP", "-c", "-O2", "-O1", "-O0", "-O3"):
            continue
        elif word.startswith(("-Wa,", "-DASM_DIR", "-Isrc/overlays", "-Isrc/engine")):
            continue
        elif word.endswith(".c") or word.endswith(".o"):
            continue
        elif i > 0 and words[i - 1] == "--build-dir":
            continue
        else:
            out.append(word)
    return out


def check(image: str, group: dict, out: Path) -> tuple[str, int, str]:
    """Parse one image as a unit; return the image, its file count and the compiler's complaints."""
    unity = out / (image.replace("/", "+") + ".c")
    unity.write_text("".join(f'#include "{ROOT / s}"\n' for s in group["sources"]))
    folders = sorted({str(Path(src).parent) for src in group["sources"]})
    cmd = [GCC, *group["args"], *(f"-I{f}" for f in folders), f'-DASM_DIR="{image}"']
    cmd += ["-S", "-o", os.devnull, str(unity)]
    env = dict(
        os.environ, LC_ALL="C", GCC_EXEC_PREFIX=GCC_DIR + "/", COMPILER_PATH=GCC_DIR
    )
    env["PATH"] = f"{GCC_DIR}:{env.get('PATH', '')}"
    done = subprocess.run(
        cmd, cwd=ROOT, capture_output=True, text=True, env=env, check=False
    )
    return image, len(group["sources"]), done.stderr if done.returncode else ""


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    parser.add_argument("--build-dir", default="build/meson")
    parser.add_argument("--out", default="build/unity")
    parser.add_argument("--subsystem")
    parser.add_argument("--jobs", type=int, default=os.cpu_count() or 1)
    parser.add_argument("image", nargs="*")
    args = parser.parse_args()
    build_dir = (ROOT / args.build_dir).resolve()
    out = ROOT / args.out
    out.mkdir(parents=True, exist_ok=True)
    wanted = {i if i.startswith("build/asm/") else f"build/asm/{i}" for i in args.image}
    todo = [
        (image, group)
        for image, group in images(build_dir).items()
        if (not wanted or image in wanted)
        and (not args.subsystem or subsystem(group["sources"][0]) == args.subsystem)
    ]
    failed = 0
    with concurrent.futures.ThreadPoolExecutor(args.jobs) as pool:
        for image, count, errors in pool.map(lambda t: check(*t, out), todo):
            if errors:
                failed += 1
                print(f"FAIL  {image} ({count} files)")
                for line in [
                    row for row in errors.splitlines() if "warning" not in row
                ][:20]:
                    print("   ", line)
    print(f"unity: {len(todo) - failed} of {len(todo)} images parse as one unit")
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main())
