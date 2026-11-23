"""The report scores an INCLUDE_ASM body as unmatched and a compiled body as matched."""

from __future__ import annotations

import re
import struct
from pathlib import Path
from types import SimpleNamespace

import objdiff_config

SUFFIX = ".NON_MATCHING"
#: `jr $ra; nop` and `jr $ra; addiu $v0, $zero, 1`, little-endian.
INCLUDE_BODY = struct.pack("<II", 0x03E00008, 0)
COMPILED_BODY = struct.pack("<II", 0x03E00008, 0x24020001)


def unit_object(path: Path) -> Path:
    """Write a two-function MIPS object whose first function is an INCLUDE_ASM body.

    The compiled object marks an INCLUDE_ASM body with a ``<name>.NON_MATCHING`` alias.
    """
    text = INCLUDE_BODY + COMPILED_BODY
    names = [b"func_A", b"func_A" + SUFFIX.encode(), b"func_B"]
    strings = b"\0" + b"\0".join(names) + b"\0"
    starts = [1 + sum(len(name) + 1 for name in names[:i]) for i in range(len(names))]
    symbols = struct.pack("<IIIBBH", 0, 0, 0, 0, 0, 0)
    for start, value in zip(starts, (0, 0, 8), strict=True):
        symbols += struct.pack("<IIIBBH", start, value, 8, 0x12, 0, 1)
    shstrtab = b"\0.text\0.symtab\0.strtab\0.shstrtab\0"
    bodies = [b"", text, symbols, strings, shstrtab]
    offsets = []
    position = 52
    for body in bodies:
        offsets.append(position)
        position += len(body)
    names_at = [0, 1, 7, 15, 23]
    kinds = [0, 1, 2, 3, 3]
    sections = b"".join(
        struct.pack(
            "<10I",
            names_at[i],
            kinds[i],
            6 if i == 1 else 0,
            0,
            offsets[i],
            len(bodies[i]),
            3 if i == 2 else 0,
            1 if i == 2 else 0,
            4 if i == 1 else 1,
            16 if i == 2 else 0,
        )
        for i in range(len(bodies))
    )
    header = (
        b"\x7fELF\x01\x01\x01"
        + bytes(9)
        + struct.pack(
            "<HHIIIIIHHHHHH", 1, 8, 1, 0, 0, position, 0x1000, 52, 0, 0, 40, 5, 4
        )
    )
    path.write_bytes(header + b"".join(bodies) + sections)
    return path


def project(tmp_path: Path) -> objdiff_config.Project:
    return objdiff_config.Project(tmp_path, tmp_path)


def test_an_include_asm_body_is_overwritten_and_a_compiled_body_is_kept(
    tmp_path: Path,
) -> None:
    built = unit_object(tmp_path / "src+unit.c.o")
    copy, unlifted = project(tmp_path).report_base(built)
    assert unlifted
    assert copy != built
    text = copy.read_bytes()[52:68]
    assert text[:8] != INCLUDE_BODY
    assert text[8:] == COMPILED_BODY
    assert built.read_bytes()[52:68] == INCLUDE_BODY + COMPILED_BODY


def test_a_unit_with_a_draft_is_not_marked_complete(tmp_path: Path) -> None:
    """A MATCH marker claims the unit, but a NON_MATCHING draft in it, or in a header it includes, does not."""
    shared = objdiff_config.Project(
        tmp_path,
        tmp_path,
        re.compile(r"^[ \t]*MATCH\b", re.M),
        re.compile(r"^NON_MATCHING\s", re.M),
    )
    (tmp_path / "Draft.h").write_text("NON_MATCHING void func_B(void) {}\n")
    whole = tmp_path / "whole.c"
    whole.write_text("MATCH void func_A(void) {}\n")
    drafted = tmp_path / "drafted.c"
    drafted.write_text(
        "MATCH void func_A(void) {}\n#ifdef NON_MATCHING\nNON_MATCHING void func_B(void) {}\n#endif\n"
    )
    shared_draft = tmp_path / "shared.c"
    shared_draft.write_text('MATCH void func_A(void) {}\n#include "Draft.h"\n')
    assert not shared.drafted(whole)
    assert shared.drafted(drafted)
    assert shared.drafted(shared_draft)


def test_a_split_asm_source_absent_from_the_link_map_has_no_unit(
    tmp_path: Path,
) -> None:
    """Only a split asm object the image links earns a unit; a leftover one does not."""
    target = "emi/world04/area176/13"
    split = tmp_path / "build/asm" / target
    split.mkdir(parents=True)
    (split / "func_801F3328.s").write_text("")
    (split / "func_801F3329.s").write_text("")
    link_map = tmp_path / "build/meson" / f"{target.replace('/', '+')}.map"
    link_map.parent.mkdir(parents=True)
    link_map.write_text("LOAD asm+emi+world04+area176+13+func_801F3329.s.o\n")
    project = SimpleNamespace(
        root=tmp_path,
        build_dir=tmp_path / "build/meson",
        func_address=objdiff_config.FUNC_ADDRESS,
        assemble=lambda sources, output: output,
    )
    units = objdiff_config._unlifted_units(project, {"id": target}, set(), set())
    assert [unit["name"] for unit in units] == [f"{target}/func_801F3329"]
