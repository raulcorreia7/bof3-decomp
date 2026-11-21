from __future__ import annotations

from bof3.symbols import mips


def lui(rt: int, imm: int) -> int:
    return 0x3C000000 | (rt << 16) | (imm & 0xFFFF)


def lw(rt: int, rs: int, offset: int) -> int:
    return 0x8C000000 | (rs << 21) | (rt << 16) | (offset & 0xFFFF)


def test_a_pointer_register_is_followed_to_its_offsets() -> None:
    words = (lui(4, 0x8014), lw(4, 4, 0x6304), lw(2, 4, 0x10))
    found, traced, untraced = mips.decode_accesses(
        "exe/x",
        "Func",
        0x80000000,
        words,
        [],
        {0x80146304: "PartyMember"},
        {},
    )
    assert traced == 1
    assert [(a.offset, a.type_name) for a in found] == [(0x10, "PartyMember")]
