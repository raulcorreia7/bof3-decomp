from __future__ import annotations

from pathlib import Path

from bof3.link import graph

ROOT = Path("/repo")


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
