"""The Meson build graph of one target: its objects, how each is made, and its link script.

A Meson ``custom_target`` output cannot hold ``/``, so an object ``build/src/a/b.c.o`` is
named ``src+a+b.c.o`` in the build directory. :func:`object_name` is the one place that
spells this; the link script and the graph rows both use it.
"""

from __future__ import annotations

import re
from pathlib import Path

from bof3.core.paths import ASM, BUILD, TOOLCHAINS
from bof3.link.script import parse
from bof3.resolve.ids import asm_dir

__all__ = ["Row", "flat", "link_script", "object_name", "rows", "source_object"]

#: Characters that cannot appear in a path, because the flat name or a Meson/ld
#: script would read them differently.
_RESERVED = re.compile(r"[+@\s]")

#: One graph row: kind, output name, source, ASM_DIR (compile rows only).
Row = tuple[str, ...]


def flat(path: str) -> str:
    """Return the build directory name of a path: no ``build/`` prefix, ``+`` for ``/``."""
    if _RESERVED.search(path):
        raise ValueError(f"path cannot be named in a flat build directory: {path}")
    return path.removeprefix(BUILD + "/").replace("/", "+")


def object_name(root: Path, path: str) -> str:
    """Return how the linker names an input object: its flat name, or a prebuilt object's path."""
    if path.startswith(TOOLCHAINS + "/"):
        return str(root / path)
    return flat(path)


def source_object(relative: Path, *, draft: bool = False) -> str:
    """Return the flat name of the object compiled from ``src/<relative>``.

    A draft is the same source compiled with ``-DNON_MATCHING``, for the progress report.
    """
    return flat(f"{BUILD}/{'draft' if draft else 'src'}/{relative.as_posix()}.o")


def link_script(root: Path, text: str) -> str:
    """Return a Splat linker script with every object input renamed by :func:`object_name`."""
    lines = text.splitlines(keepends=True)
    for entry in parse(text):
        lines[entry.line - 1] = lines[entry.line - 1].replace(
            entry.path, object_name(root, entry.path), 1
        )
    return "".join(lines)


def rows(root: Path, target: str, objects: tuple[str, ...]) -> list[Row]:
    """Return how to build each object of one target.

    ``c`` compiles a source, ``s`` assembles one, and ``b`` wraps a binary asset. A
    prebuilt PsyQ object has no row: the link script names it by path.
    """
    result: list[Row] = []
    for obj in objects:
        stem = obj.removesuffix(".o")
        if obj.startswith(TOOLCHAINS + "/"):
            continue
        name = object_name(root, obj)
        if obj.startswith(f"{BUILD}/src/") and obj.endswith(".c.o"):
            source = stem.removeprefix(BUILD + "/")
            result.append(("c", name, source, asm_dir(root / source, root)))
        elif obj.startswith(f"{BUILD}/{ASM}/") and obj.endswith(".s.o"):
            result.append(("s", name, stem.removeprefix(BUILD + "/")))
        elif obj.startswith(f"{BUILD}/p2/") and obj.endswith(".s.o"):
            result.append(("s", name, stem))
        elif obj.startswith(f"{BUILD}/assets/") and obj.endswith(".bin.o"):
            result.append(("b", name, stem))
        else:
            raise ValueError(f"{target}: no rule for linker input {obj}")
    return result
