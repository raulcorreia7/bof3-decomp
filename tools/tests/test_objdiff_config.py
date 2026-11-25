"""The report scores an INCLUDE_ASM body as unmatched and a compiled body as matched."""

from __future__ import annotations

import re
import struct
from pathlib import Path
from types import SimpleNamespace

import pytest

import objdiff_config

SUFFIX = ".NON_MATCHING"
#: `jr $ra; nop` and `jr $ra; addiu $v0, $zero, 1`, little-endian.
INCLUDE_BODY = struct.pack("<II", 0x03E00008, 0)
COMPILED_BODY = struct.pack("<II", 0x03E00008, 0x24020001)


def unit_object(
    path: Path,
    text: bytes = INCLUDE_BODY + COMPILED_BODY,
    entries: tuple[tuple[bytes, int, int], ...] = (
        (b"func_A", 0, 8),
        (b"func_A" + SUFFIX.encode(), 0, 8),
        (b"func_B", 8, 8),
    ),
) -> Path:
    """Write a minimal MIPS text object with sized function symbols."""
    names = [name for name, _, _ in entries]
    strings = b"\0" + b"\0".join(names) + b"\0"
    starts = [1 + sum(len(name) + 1 for name in names[:i]) for i in range(len(names))]
    symbols = struct.pack("<IIIBBH", 0, 0, 0, 0, 0, 0)
    for start, (_, value, size) in zip(starts, entries, strict=True):
        symbols += struct.pack("<IIIBBH", start, value, size, 0x12, 0, 1)
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
    path.parent.mkdir(parents=True, exist_ok=True)
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


@pytest.mark.parametrize(
    "image,entry,extra,expected",
    [
        (
            "emi/etc/commu02/08",
            0x801D92F4,
            (),
            {"func_801D92F4": "Party_GetJoinedCharacter"},
        ),
        ("emi/etc/commu02/09", 0x801D92F4, (), {}),
        ("emi/etc/commu02/08", 0x801D92F8, (), {}),
        ("emi/etc/commu02/08", 0x801D92F4, ((b"other_entry", 4, 4),), {}),
        ("emi/etc/commu02/08", 0x801D92F4, ((b"alias", 0, 0x54),), {}),
    ],
    ids=[
        "verified owner",
        "different image",
        "wrong address",
        "overlapping span",
        "ambiguous entry",
    ],
)
def test_report_pairs_only_the_linked_unit_span(
    tmp_path: Path,
    image: str,
    entry: int,
    extra: tuple[tuple[bytes, int, int], ...],
    expected: dict[str, str],
) -> None:
    p = project(tmp_path)
    relative = Path("overlays/commu/commu02/08/794.c")
    source = p.root / "src" / relative
    source.parent.mkdir(parents=True)
    source.write_text(
        "MATCH unsigned char Party_GetJoinedCharacter(unsigned char arg) {}\n"
    )
    linked_name = objdiff_config.source_object(relative)
    body = bytes(0x54)
    linked = unit_object(
        p.build_dir / linked_name, body, ((b"Party_GetJoinedCharacter", 0, 0x54),)
    )
    target = unit_object(
        p.build_dir / "target.o", body, ((b"func_801D92F4", 0, 0x54), *extra)
    )
    (p.build_dir / f"{image.replace('/', '+')}.map").write_text(
        f" .text 0x801d92f4 0x54 {linked_name}\n"
        f"        {entry:#x} Party_GetJoinedCharacter\n"
    )

    assert (
        objdiff_config._report_aliases(p, image, source, relative, linked, target)
        == expected
    )


def test_icon_hand_source_can_have_an_address_filename(tmp_path: Path) -> None:
    p = project(tmp_path)
    image = "exe/slus_004_22"
    relative = Path("engine/ui/text/UI_IconDrawCell.c")
    source = p.root / "src" / relative
    source.parent.mkdir(parents=True)
    source.write_text("/* Port model */\nHAND_ASM void UI_IconDrawCell(void) {}\n")
    hand = p.root / "asm" / image / "hand/func_801644D8.s"
    hand.parent.mkdir(parents=True)
    hand.write_text(".globl UI_IconDrawCell\nUI_IconDrawCell:\n")
    linked_name = objdiff_config.source_object(relative)
    unit_object(
        p.build_dir / linked_name, bytes(0x2EC), ((b"UI_IconDrawCell", 0, 0x2EC),)
    )
    (p.build_dir / "exe+slus_004_22.map").write_text(
        f" .text 0x801644d8 0x2ec {linked_name}\n        0x801644d8 UI_IconDrawCell\n"
    )

    assert p.source_asm(image, source) == ([hand], "hand-asm")


@pytest.mark.parametrize(
    "size,body",
    [(0x8C, COMPILED_BODY), (0x84, COMPILED_BODY), (0x8C, INCLUDE_BODY)],
    ids=["covers tail", "stops before tail", "different tail bytes"],
)
def test_sdk_tail_coverage_keeps_the_adjacent_function(
    tmp_path: Path, size: int, body: bytes
) -> None:
    image = "exe/slus_004_22"
    p = objdiff_config.Project(tmp_path, tmp_path / "build/meson")
    p.build_dir.mkdir(parents=True)
    split = tmp_path / "build/asm" / image
    split.mkdir(parents=True)
    member = "toolchains/psyq/3.7/libgte/msc02.o"
    unit_object(
        tmp_path / member,
        bytes(0x84) + body,
        ((b"InvSquareRoot", 0, 0),),
    )
    link_map = p.build_dir / "exe+slus_004_22.map"
    lines = [
        " .text 0x80178764 0x98 src+engine+slus+func_80178764.c.o\n",
        "        0x80178778 InvSquareRoot\n",
    ]
    for address in (0x801787FC, 0x80178804):
        name = f"func_{address:08X}"
        (split / f"{name}.s").touch()
        lines.append(
            f" .text {address:#x} 0x8 asm+exe+slus_004_22+{name}.s.o\n"
            f"        {address:#x} {name}\n"
        )
    link_map.write_text("".join(lines))
    library = [
        {
            "id": f"{image}@0x80178778",
            "object": member,
            "symbol": "InvSquareRoot",
            "size": size,
        }
    ]

    class FixtureProject(objdiff_config.Project):
        def assemble(
            self,
            sources: list[Path],
            output: Path,
            readable: dict[str, int] | None = None,
        ) -> Path:
            return unit_object(
                output, COMPILED_BODY, ((sources[0].stem.encode(), 0, 8),)
            )

    units = objdiff_config._unlifted_units(
        FixtureProject(p.root, p.build_dir), {"id": image}, set(), set(), library
    )
    expected = [f"{image}/func_80178804"]
    if size != 0x8C or body != COMPILED_BODY:
        expected.insert(0, f"{image}/func_801787FC")
    assert [unit["name"] for unit in units] == expected
