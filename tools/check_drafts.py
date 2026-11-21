#!/usr/bin/env python3
"""Fail when a changed source holds a `NON_MATCHING` draft that does not compile.

A kept draft compiles with `-DNON_MATCHING`: `tools/match.sh --diff` builds it. The image build
compiles a draft with `--empty-on-failure`, so a draft that stops compiling goes unseen there.
This check compiles each draft source that changed since the merge base of BASE_REF and HEAD
with the draft's own flags from `build/meson/compile_commands.json` and prints one line per
failing file with the first compiler error. Nothing changed, nothing printed.

Usage: python3 tools/check_drafts.py [BASE_REF]    (default: the newest of public/main, origin/main, main)

A source the build graph does not list yet (a new draft before `meson setup`) borrows the flags of
a draft in the same folder. With no compiler or no build graph the check skips with one line.
"""

from __future__ import annotations

import json
import re
import shlex
import subprocess
import sys
import tempfile
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

from bof3.adapters.git import git, merge_base
from bof3.core.paths import ROOT

BUILD = ROOT / "build/meson"
GCC = ROOT / "toolchains/gcc-2.7.2-psx/gcc"
DRAFT = re.compile(r"^NON_MATCHING\b", re.MULTILINE)
DROP = {"--empty-on-failure", "-MMD", "-MP"}


def base_ref() -> str:
    out = subprocess.run(
        ["sh", "-c", ". tools/lib/baseref.sh && newest_base_ref"],
        cwd=ROOT,
        capture_output=True,
        text=True,
        check=False,
    )
    return out.stdout.strip()


def changed_drafts(ref: str) -> list[str]:
    base = merge_base(ref, root=ROOT)
    names = git(
        "diff",
        "--name-only",
        "--diff-filter=ACMR",
        base,
        "HEAD",
        "--",
        "src",
        root=ROOT,
    )
    drafts = []
    for name in names.splitlines():
        path = ROOT / name
        if name.endswith(".c") and path.is_file():
            if DRAFT.search(path.read_text(errors="replace")):
                drafts.append(name)
    return drafts


def draft_commands() -> dict[str, list[str]]:
    """Map each draft source to its compile arguments from the build graph."""
    entries = json.loads((BUILD / "compile_commands.json").read_text())
    commands = {}
    for entry in entries:
        if not entry["output"].startswith("draft+"):
            continue
        source = str((BUILD / entry["file"]).resolve().relative_to(ROOT))
        commands[source] = [a.strip("'") for a in shlex.split(entry["command"])]
    return commands


def arguments_for(source: str, commands: dict[str, list[str]]) -> list[str] | None:
    """The cc.py arguments up to the source, or None when no draft shares its folder."""
    folder = str(Path(source).parent)
    if source in commands:
        donor, args = source, commands[source]
    else:
        donor = next((s for s in commands if str(Path(s).parent) == folder), "")
        if not donor:
            return None
        args = commands[donor]
    out = []
    skip = 0
    for arg in args[2:]:  # after python and cc.py
        if skip:
            skip -= 1
        elif arg in DROP or arg == "--build-dir":
            skip = arg == "--build-dir"
        elif arg == "-MF":
            skip = 1
        elif arg in ("-c", "-o"):
            break
        else:
            out.append(arg.replace(f"-I{Path(donor).parent}", f"-I{folder}"))
    return out


def compile_one(source: str, args: list[str]) -> str:
    """The first compiler error of the draft, or an empty string when it compiles."""
    with tempfile.TemporaryDirectory(prefix="bof3-drafts-") as tmp:
        cmd = [
            sys.executable,
            str(ROOT / "tools/cc.py"),
            "--build-dir",
            str(BUILD),
            *args,
            "-c",
            source,
            "-o",
            f"{tmp}/draft.o",
        ]
        done = subprocess.run(
            cmd, cwd=ROOT, capture_output=True, text=True, check=False
        )
    if done.returncode == 0:
        return ""
    lines = (done.stdout + done.stderr).splitlines()
    errors = [
        x for x in lines if x.strip() and "warning" not in x and "In function" not in x
    ]
    return (
        errors[0].removeprefix(source + ":")
        if errors
        else f"cc.py exited {done.returncode}"
    )


def main(argv: list[str]) -> int:
    if argv and argv[0] in ("-h", "--help"):
        print(__doc__)
        return 0
    ref = argv[0] if argv else base_ref()
    if not ref:
        print("drafts: no public/main or origin/main to compare with", file=sys.stderr)
        return 1
    drafts = changed_drafts(ref)
    if not drafts:
        return 0
    if not GCC.exists() or not (BUILD / "compile_commands.json").exists():
        print("skip  drafts (no toolchains/gcc-2.7.2-psx or build/meson)")
        return 0
    commands = draft_commands()
    if (
        not commands
    ):  # a build graph with no draft targets (CI has no disc): nothing to compile with
        print("skip  drafts (the build graph has no draft targets)")
        return 0
    jobs = []
    failed = 0
    with ThreadPoolExecutor(max_workers=8) as pool:
        for source in drafts:
            args = arguments_for(source, commands)
            if args is None:
                # An image the build graph does not configure (CI has no disc) cannot be compiled here.
                print(
                    f"skip  {source}: its image has no draft target in this build graph"
                )
                continue
            jobs.append((source, pool.submit(compile_one, source, args)))
        for source, job in jobs:
            error = job.result()
            if error:
                print(f"{source}: {error}")
                failed += 1
    return 1 if failed else 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
