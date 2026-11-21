from __future__ import annotations

from pathlib import Path

import pytest

from bof3.link import graph

ROOT = Path("/repo")


def test_flat_names() -> None:
    assert graph.flat("build/src/engine/slus/a.c.o") == "src+engine+slus+a.c.o"
    assert graph.source_object(Path("slus/a.c"), draft=True) == "draft+slus+a.c.o"
    with pytest.raises(ValueError):
        graph.flat("build/src/a+b.c.o")


def test_link_script_renames_objects_and_keeps_directives() -> None:
    text = (
        "    .text 0x80010000 : AT(0)\n"
        "    {\n"
        "        build/src/engine/slus/a.c.o(.text);\n"
        "        toolchains/psyq/3.7/LIBGPU.OBJ/x.o(.text);\n"
        "        . = ALIGN(., 4);\n"
        "    }\n"
    )
    assert graph.link_script(ROOT, text) == (
        "    .text 0x80010000 : AT(0)\n"
        "    {\n"
        "        src+engine+slus+a.c.o(.text);\n"
        "        /repo/toolchains/psyq/3.7/LIBGPU.OBJ/x.o(.text);\n"
        "        . = ALIGN(., 4);\n"
        "    }\n"
    )
