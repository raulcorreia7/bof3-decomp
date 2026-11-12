from __future__ import annotations

import symbol
from symbol import AccessRange, Layout, Member


def lui(rt: int, imm: int) -> int:
    return 0x3C000000 | (rt << 16) | (imm & 0xFFFF)


def addiu(rt: int, rs: int, imm: int) -> int:
    return 0x24000000 | (rs << 21) | (rt << 16) | (imm & 0xFFFF)


def lw(rt: int, rs: int, offset: int) -> int:
    return 0x8C000000 | (rs << 21) | (rt << 16) | (offset & 0xFFFF)


def lh(rt: int, rs: int, offset: int) -> int:
    return 0x84000000 | (rs << 21) | (rt << 16) | (offset & 0xFFFF)


def sw(rt: int, rs: int, offset: int) -> int:
    return 0xAC000000 | (rs << 21) | (rt << 16) | (offset & 0xFFFF)


def addu(rd: int, rs: int, rt: int) -> int:
    return (rs << 21) | (rt << 16) | (rd << 11) | 0x21


def jal(target: int) -> int:
    return 0x0C000000 | ((target >> 2) & 0x03FFFFFF)


def test_a_direct_global_access() -> None:
    ranges = [AccessRange(0x80145E90, 0x80145E94, "g_Game", "GameState")]
    words = (lui(16, 0x8014), lw(2, 16, 0x5E90))
    found, traced, untraced = symbol.decode_accesses(
        "exe/x", "Func", 0x80000000, words, ranges, {}, {}
    )
    assert traced == 1 and untraced == 0
    assert len(found) == 1
    access = found[0]
    assert (access.offset, access.width, access.mnemonic, access.write) == (
        0,
        4,
        "lw",
        False,
    )
    assert access.global_name == "g_Game"


def test_a_pointer_register_is_followed_to_its_offsets() -> None:
    words = (lui(4, 0x8014), lw(4, 4, 0x6304), lw(2, 4, 0x10))
    found, traced, untraced = symbol.decode_accesses(
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


def test_a_stored_constant_and_a_call_slot() -> None:
    target = 0x80001000
    words = (
        lui(4, 0x8014),
        addiu(4, 4, 0x6304),
        addiu(2, 0, 0x3A),
        sw(2, 4, 0x44),
        lw(2, 4, 0x10),
        addu(4, 2, 0),
        jal(target),
    )
    ranges = [AccessRange(0x80146304, 0x80146404, "g_State", "State")]
    found, _, _ = symbol.decode_accesses(
        "exe/x",
        "Func",
        0x80000000,
        words,
        ranges,
        {},
        {target: "Callee"},
    )
    store = next(a for a in found if a.mnemonic == "sw")
    assert store.offset == 0x44 and store.write and store.constant == 0x3A
    load = next(a for a in found if a.mnemonic == "lw")
    assert load.slot == "Callee[a0]"


def test_the_problems_follow_the_member_widths() -> None:
    layout = Layout(
        4,
        (
            Member(0, "a", "u8", 1),
            Member(1, "pad_01", "u8", 1),
            Member(2, "b", "u16", 2),
        ),
        True,
    )
    accesses = [
        symbol.MipsAccess("exe/x", "F", 0, 2, "lh", False, True, "line"),
        symbol.MipsAccess("exe/x", "F", 2, 4, "lw", False, None, "line"),
    ]
    rows = {
        row["offset"]: row for row in symbol._aggregate_accesses(layout, accesses, {})
    }
    assert "width differs" in rows[0]["problem"]
    assert "signedness differs" in rows[0]["problem"]
    assert "straddles members" in rows[0]["problem"]
    assert "past the end" in rows[2]["problem"]
    assert "unknown member" in rows[1]["problem"]
    assert "never accessed" in rows[1]["problem"]


def test_a_leading_zero_constant_is_octal() -> None:
    assert symbol._member_constants("if (actor.step == 06) {", "step") == [6]
