"""gen_body lifts straight-line assembly, sorts it into shapes and writes typed C."""

from __future__ import annotations

from pathlib import Path

import pytest

import gen_body

CALLS = """\
addiu $sp, $sp, -0x18
sw $ra, 0x10($sp)
addiu $a0, $zero, 0x7
jal Party_JoinMember
addu $a1, $zero, $zero
lui $at, %hi(g_PartySize)
sb $zero, %lo(g_PartySize)($at)
lw $ra, 0x10($sp)
jr $ra
addiu $sp, $sp, 0x18
""".splitlines()

SPAD = """\
lui $v0, (0x1F800044 >> 16)
lw $v0, (0x1F800044 & 0xFFFF)($v0)
nop
lbu $v1, 0x2($v0)
nop
addiu $v1, $v1, 0x1
sb $v1, 0x2($v0)
jr $ra
nop
""".splitlines()


def ctx(members: dict[int, tuple[str, int]] | None = None) -> dict:
    return {
        "tree": gen_body.Tree(Path(".")),
        "files": [],
        "members": members or {},
        "names": None,
        "image": "emi/test",
    }


def test_a_call_sequence_keeps_constant_arguments_and_global_stores() -> None:
    lifted = gen_body.lift(CALLS)
    assert gen_body.classify(lifted) == "call-seq"
    assert gen_body.statements(lifted, ctx()) == [
        "Party_JoinMember(7, 0);",
        "g_PartySize = 0;",
    ]


def test_a_member_increment_reads_as_postfix_increment() -> None:
    lifted = gen_body.lift(SPAD)
    assert gen_body.classify(lifted) == "spad"
    assert gen_body.statements(lifted, ctx({2: ("unk_02", 1)})) == [
        "g_SpadWork->unk_02++;"
    ]


def test_a_member_without_a_known_offset_is_unsupported() -> None:
    with pytest.raises(gen_body.Unsupported):
        gen_body.statements(gen_body.lift(SPAD), ctx())


def test_a_branch_makes_the_branch_shape() -> None:
    assert gen_body.classify(gen_body.lift(["beqz $v0, .L1", "nop"])) == "branch"


def test_a_jalr_makes_the_dispatch_shape() -> None:
    assert gen_body.classify(gen_body.lift(["jalr $v0", "nop"])) == "dispatch"


def test_a_constant_left_in_v0_is_the_return_value() -> None:
    lifted = gen_body.lift(["jal f", "nop", "addu $v0, $zero, $zero", "jr $ra", "nop"])
    assert lifted.ret == ("c", 0)


def test_struct_members_take_their_offset_from_the_name_or_the_note() -> None:
    body = "u8 flags_00;\nu8 slot; /* +0x05 slot */\ns32 unk_0C;\n"
    assert gen_body.Tree(Path(".")).parse(body, []) == {
        0: ("flags_00", 1),
        5: ("slot", 1),
        12: ("unk_0C", 4),
    }


RESULT = """\
addiu $sp, $sp, -0x18
sw $ra, 0x10($sp)
jal rand
nop
andi $v0, $v0, 0xF
lui $at, %hi(g_Table)
addu $at, $at, $v0
lbu $v1, %lo(g_Table)($at)
lui $at, %hi(g_Pick)
sb $v1, %lo(g_Pick)($at)
lw $ra, 0x10($sp)
jr $ra
addiu $sp, $sp, 0x18
""".splitlines()


def test_a_call_result_gets_a_local_and_a_table_element_reads_by_index() -> None:
    lifted = gen_body.lift(RESULT)
    assert gen_body.rets_used(lifted.events) == {0}
    assert gen_body.statements(lifted, ctx()) == [
        "r0 = rand();",
        "g_Pick = g_Table[r0 & 15];",
    ]


def test_an_argument_beyond_the_fourth_comes_from_the_stack() -> None:
    lifted = gen_body.lift(
        [
            "addiu $v0, $zero, 0x9",
            "sw $v0, 0x10($sp)",
            "addiu $a0, $zero, 0x1",
            "addiu $a1, $zero, 0x2",
            "addiu $a2, $zero, 0x3",
            "jal f",
            "addiu $a3, $zero, 0x4",
        ]
    )
    assert gen_body.statements(lifted, ctx()) == ["f(1, 2, 3, 4, 9);"]


def test_register_arithmetic_and_halving_lift_to_expressions() -> None:
    lifted = gen_body.lift(
        [
            "lui $v0, %hi(g_A)",
            "lw $v0, %lo(g_A)($v0)",
            "lui $v1, %hi(g_B)",
            "lw $v1, %lo(g_B)($v1)",
            "subu $v0, $v0, $v1",
            "srl $v1, $v0, 31",
            "addu $v0, $v0, $v1",
            "sra $v0, $v0, 1",
            "lui $at, %hi(g_Out)",
            "sw $v0, %lo(g_Out)($at)",
        ]
    )
    assert gen_body.statements(lifted, ctx()) == ["g_Out = (g_A - g_B) / 2;"]


def test_a_store_that_rereads_its_target_reads_as_a_compound_assignment() -> None:
    lifted = gen_body.lift(
        [
            "lui $v0, %hi(g_Flags)",
            "lbu $v0, %lo(g_Flags)($v0)",
            "nop",
            "andi $v0, $v0, 0xFE",
            "lui $at, %hi(g_Flags)",
            "sb $v0, %lo(g_Flags)($at)",
        ]
    )
    assert gen_body.statements(lifted, ctx()) == ["g_Flags &= 254;"]


def test_a_stride_index_is_a_multiple_of_one_variable() -> None:
    x = ("g", "g_Slot", 1, False)
    index = ("bin", "<<", ("bin", "+", ("bin", "<<", x, 2), x), 3)
    assert gen_body.linear(index) == (40, x)
    assert gen_body.linear(("bin", "-", ("bin", "<<", x, 3), x)) == (7, x)


def test_a_struct_layout_follows_natural_alignment(tmp_path: Path) -> None:
    (tmp_path / "t.h").write_text(
        "#define N 2\ntypedef struct {\n u8 a;\n u16 b;\n u8 c[N];\n u32 d;\n} T;\n",
        encoding="utf-8",
    )
    tree = gen_body.Tree(tmp_path)
    tree.text["t.h"] = (tmp_path / "t.h").read_text(encoding="utf-8")
    gen_body._HEADERS[:] = ["t.h"]
    try:
        assert tree.layout("T", ["t.h"]) == (
            12,
            [(0, "a", 1, 1), (2, "b", 2, 1), (4, "c", 1, 2), (8, "d", 4, 1)],
        )
    finally:
        gen_body._HEADERS.clear()
