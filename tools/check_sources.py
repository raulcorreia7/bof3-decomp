#!/usr/bin/env python3
"""Fail when a tracked source under src/ is not a row of its image's Splat layout.

The layout rows are the build graph: a source no row names is never compiled. When it holds a
function the image also defines, the build links the copy in the image's unit, and the progress
report asks for an object that was never made.
"""

from __future__ import annotations

import subprocess
import sys
from pathlib import Path

from bof3.core.io import repo_layout
from bof3.resolve.layout import read_splat


def layout_names(document: dict) -> set[str]:
    """Return the source stem of every row of one layout, segment rows included."""
    names: set[str] = set()

    def add(value: object) -> None:
        # A numeric row name is the source stem as written, unquoted in the YAML.
        if isinstance(value, bool) or value is None:
            return
        if isinstance(value, (int, str)):
            names.add(str(value))

    for segment in document.get("segments", []):
        if isinstance(segment, (list, tuple)):
            if len(segment) >= 3:
                add(segment[2])
            continue
        rows = segment.get("subsegments")
        if not rows:
            add(segment.get("name"))
            continue
        for row in rows:
            if isinstance(row, (list, tuple)):
                if len(row) >= 3:
                    add(row[2])
            elif isinstance(row, dict):
                add(row.get("name"))
    return names


def images(root: Path) -> dict[str, tuple[str, set[str]]]:
    """Return each source folder under src/ with its layout and the source stems it names."""
    found: dict[str, tuple[str, set[str]]] = {}
    for splat in sorted(root.glob("config/**/splat.yaml")):
        document = read_splat(splat)[1]
        src_path = document.get("options", {}).get("src_path")
        if not src_path:
            continue
        found[src_path.removeprefix("src/")] = (
            splat.relative_to(root).as_posix(),
            layout_names(document),
        )
    return found


def orphans(
    sources: list[str], known: dict[str, tuple[str, set[str]]]
) -> list[tuple[str, str]]:
    """Return each source no row of its image's layout names, with that layout's path."""
    found = []
    for source in sources:
        folder = Path(source).parent.relative_to("src").as_posix()
        image = known.get(folder)
        if image is None or Path(source).stem not in image[1]:
            found.append((source, image[0] if image else f"src/{folder}"))
    return found


def tracked_sources() -> list[str]:
    out = subprocess.check_output(["git", "ls-files", "src"], text=True)
    return [name for name in out.split("\n") if name.endswith(".c")]


def main() -> int:
    if len(sys.argv) > 1 and sys.argv[1] in ("-h", "--help"):
        print(__doc__.strip())
        return 0
    root = repo_layout().root
    bad = orphans(tracked_sources(), images(root))
    for source, where in bad:
        print(f"{source}: no row of {where} compiles it")
    if bad:
        print(
            "check-sources: name the source in its image's layout, or delete it",
            file=sys.stderr,
        )
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
