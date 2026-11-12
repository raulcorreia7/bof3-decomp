from __future__ import annotations

import collections

import symbol
from bof3.source import asmtext

HEADER = """.include "macro.inc"

.set noat
.set noreorder

.section .text, "ax"
"""


def one(text: str) -> asmtext.Function:
    found = asmtext.functions(HEADER + text, "image", "asm/image/unit.s")
    assert len(found) == 1
    return found[0]


def insn(address: int, mnemonic: str, operands: str) -> str:
    return f"    /* 0 {address:08X} 00000000 */  {mnemonic} {operands}"


def function(name: str, size: int, body: list[tuple[int, str, str]]) -> str:
    lines = [f"nonmatching {name}, 0x{size:X}", f"glabel {name}"]
    lines.extend(
        insn(address, mnemonic, operands) for address, mnemonic, operands in body
    )
    lines.append(f"endlabel {name}")
    return "\n".join(lines) + "\n"


def owner_of(*rows: tuple[str, int, int]) -> object:
    """Return an owner function over ``(name, address, size)`` rows."""
    ordered = sorted(rows, key=lambda row: row[1])

    def owner(address: int):
        for name, start, size in ordered:
            if start <= address < start + size:
                return "image", name, address - start
        return None

    return owner


def test_a_multi_function_unit_keeps_names_sizes_and_addresses() -> None:
    text = HEADER + (
        "nonmatching Unit_First, 0x18\n"
        "glabel Unit_First\n"
        "    /* 0 801D1000 00000000 */  jr $ra\n"
        "    /* 0 801D1004 00000000 */  nop\n"
        "endlabel Unit_First\n"
        "nonmatching Unit_Second, 0x8\n"
        "glabel Unit_Second\n"
        "    /* 0 801D1018 00000000 */  jr $ra\n"
        "    /* 0 801D101C 00000000 */  nop\n"
        "endlabel Unit_Second\n"
    )
    found = asmtext.functions(text, "image", "asm/image/Unit.s")
    assert [(item.name, item.address, item.size) for item in found] == [
        ("Unit_First", 0x801D1000, 0x18),
        ("Unit_Second", 0x801D1018, 0x8),
    ]


def test_operands_split_outside_parentheses_and_comments() -> None:
    assert asmtext.operands("$v0, %lo(D_80146000 + 0x4)($at)") == [
        "$v0",
        "%lo(D_80146000 + 0x4)($at)",
    ]
    assert asmtext.operands("$a0, $a1, .L801D1000 /* note */") == [
        "$a0",
        "$a1",
        ".L801D1000",
    ]
    assert asmtext.operands("") == []


def test_integer_resolves_half_addresses_and_symbols_resolve_offsets() -> None:
    assert asmtext.integer("(0x1F800044 >> 16)") == 0x1F80
    assert asmtext.integer("(0x1F800044 & 0xFFFF)") == 0x44
    assert asmtext.integer("-0x18") == -0x18
    assert asmtext.symbol("%lo(g_Actors + 0x32)") == ("g_Actors", 0x32)
    assert asmtext.symbol("%hi(D_80146000)") == ("D_80146000", 0)
    assert asmtext.symbol("$v0") is None


def test_arguments_count_from_the_highest_register_and_keep_their_accesses() -> None:
    function_text = function(
        "Read",
        0x40,
        [
            (0x801D1000, "addiu", "$sp, $sp, -0x18"),
            (0x801D1004, "sw", "$ra, 0x10($sp)"),
            (0x801D1008, "addu", "$v0, $a1, $zero"),
            (0x801D100C, "lbu", "$v1, 0x119($a0)"),
            (0x801D1010, "lhu", "$v0, 0x11A($a0)"),
            (0x801D1014, "jr", "$ra"),
            (0x801D1018, "nop", ""),
        ],
    )
    facts = asmtext.decode(one(function_text), {}, lambda address: None)
    assert sorted(facts.args) == [0, 1]
    assert [
        (item.offset, item.width, item.signed) for item in facts.args[0].accesses
    ] == [
        (0x119, 1, False),
        (0x11A, 2, False),
    ]
    assert facts.args[0].narrow is None


def test_one_pointer_copied_to_a_temporary_counts_and_narrows() -> None:
    function_text = function(
        "Narrow",
        0x20,
        [
            (0x801D1000, "addu", "$t0, $a0, $zero"),
            (0x801D1004, "sll", "$t0, $t0, 16"),
            (0x801D1008, "sra", "$t0, $t0, 16"),
            (0x801D100C, "andi", "$a1, $a1, 0xFF"),
            (0x801D1010, "jr", "$ra"),
            (0x801D1014, "nop", ""),
        ],
    )
    facts = asmtext.decode(one(function_text), {}, lambda address: None)
    assert facts.args[0].narrow == "s16"
    assert facts.args[1].narrow == "u8"


def test_a_register_loaded_from_a_symbol_is_not_an_argument() -> None:
    function_text = function(
        "Copy",
        0x20,
        [
            (0x801D1000, "lui", "$a1, %hi(g_Cursor)"),
            (0x801D1004, "lw", "$a1, %lo(g_Cursor)($a1)"),
            (0x801D1008, "lhu", "$v0, 0x11A($a1)"),
            (0x801D100C, "jr", "$ra"),
            (0x801D1010, "nop", ""),
        ],
    )
    facts = asmtext.decode(one(function_text), {}, lambda address: None)
    assert facts.args == {}
    assert [(item.name, item.offset) for item in facts.accesses] == [("g_Cursor", 0)]


def test_stack_arguments_count_from_the_frame() -> None:
    function_text = function(
        "Stack",
        0x20,
        [
            (0x801D1000, "addiu", "$sp, $sp, -0x38"),
            (0x801D1004, "lbu", "$v0, 0x48($sp)"),
            (0x801D1008, "lbu", "$v1, 0x50($sp)"),
            (0x801D100C, "jr", "$ra"),
            (0x801D1010, "nop", ""),
        ],
    )
    facts = asmtext.decode(one(function_text), {}, lambda address: None)
    assert facts.stack_arguments == 3


def test_a_void_function_has_no_return_write_past_its_epilogue() -> None:
    function_text = function(
        "Void",
        0x20,
        [
            (0x801D1000, "lw", "$v0, 0x0($a0)"),
            (0x801D1004, "sw", "$v0, 0x0($a0)"),
            (0x801D1008, "lw", "$ra, 0x10($sp)"),
            (0x801D100C, "addiu", "$sp, $sp, 0x18"),
            (0x801D1010, "jr", "$ra"),
            (0x801D1014, "nop", ""),
        ],
    )
    facts = asmtext.decode(one(function_text), {}, lambda address: None)
    assert facts.return_writes == []
    assert facts.return_width is None


def test_the_value_before_the_epilogue_is_the_return_with_its_width() -> None:
    function_text = function(
        "Half",
        0x20,
        [
            (0x801D1000, "sll", "$v0, $a0, 16"),
            (0x801D1004, "sra", "$v0, $v0, 16"),
            (0x801D1008, "lw", "$ra, 0x10($sp)"),
            (0x801D100C, "addiu", "$sp, $sp, 0x18"),
            (0x801D1010, "jr", "$ra"),
            (0x801D1014, "nop", ""),
        ],
    )
    facts = asmtext.decode(one(function_text), {}, lambda address: None)
    assert facts.return_writes == [("sra", "$v0, $v0, 16")]
    assert facts.return_width == (2, True)
    assert asmtext.bool_write("sltu", "$v0, $v0, $v1")
    assert not asmtext.bool_write("sra", "$v0, $v0, 16")


def test_a_symbol_access_through_a_constant_base_uses_the_owner_lookup() -> None:
    function_text = function(
        "Raw",
        0x20,
        [
            (0x801D1000, "lui", "$v0, 0x8014"),
            (0x801D1004, "lw", "$v1, 0x630C($v0)"),
            (0x801D1008, "jr", "$ra"),
            (0x801D100C, "nop", ""),
        ],
    )
    facts = asmtext.decode(
        one(function_text), {}, owner_of(("D_8014630C", 0x8014630C, 0x10))
    )
    assert [(item.name, item.offset, item.width) for item in facts.accesses] == [
        ("D_8014630C", 0, 4)
    ]


def test_a_shifted_index_records_its_stride_on_the_symbol() -> None:
    function_text = function(
        "Stride",
        0x20,
        [
            (0x801D1000, "lui", "$t0, %hi(g_Actors)"),
            (0x801D1004, "addiu", "$t0, $t0, %lo(g_Actors)"),
            (0x801D1008, "sll", "$t1, $a0, 2"),
            (0x801D100C, "addu", "$t2, $t0, $t1"),
            (0x801D1010, "lw", "$v0, 0x0($t2)"),
            (0x801D1014, "jr", "$ra"),
            (0x801D1018, "nop", ""),
        ],
    )
    facts = asmtext.decode(
        one(function_text), {"g_Actors": ("image", 0x8014A000)}, lambda address: None
    )
    assert facts.strides == {("image", "g_Actors"): {4}}


def test_an_indirect_call_is_marked() -> None:
    function_text = function(
        "Dispatch",
        0x18,
        [
            (0x801D1000, "lw", "$v0, %lo(g_Modes)($v0)"),
            (0x801D1004, "jalr", "$v0"),
            (0x801D1008, "nop", ""),
            (0x801D100C, "jr", "$ra"),
            (0x801D1010, "nop", ""),
        ],
    )
    facts = asmtext.decode(one(function_text), {}, lambda address: None)
    assert facts.indirect


def test_a_name_states_its_system_or_none_for_an_address() -> None:
    assert symbol._name_system("SYS_SetFlag") == "SYS"
    assert symbol._name_system("Actor_FindFree") == "Actor"
    assert symbol._name_system("func_801D1228") is None
    assert symbol._name_system("D_8014630C") is None
    assert symbol._name_system("get_input") is None


def test_a_global_takes_the_system_its_camel_case_name_starts_with() -> None:
    systems = frozenset({"Battle", "Menu", "Game"})
    assert symbol._symbol_system("g_BattleWork", systems) == "Battle"
    assert symbol._symbol_system("g_Game", systems) == "Game"
    assert symbol._symbol_system("g_InputPressed", systems) is None
    assert symbol._symbol_system("D_8014630C", systems) is None


def test_a_folder_states_its_subsystem() -> None:
    assert symbol._folder_system("src/overlays/battle/battle/03") == "Battle"
    assert symbol._folder_system("src/overlays/bmagic/magic001/00") == "Battle magic"
    assert symbol._folder_system("src/engine/slus") == "Executable"
    assert symbol._folder_system("src/unknown/place") == "Other"


def test_a_declared_type_and_a_found_width_are_written_the_same_way() -> None:
    assert symbol._declared_kind("u8") == "u8"
    assert symbol._declared_kind("PartyMember *") == "pointer"
    assert symbol._declared_kind("s32") == "s32"
    assert symbol._declared_return_kind("void") == "void"
    assert symbol._declared_return_kind("Actor *") == "pointer"
    assert symbol._return_type({"kind": "value", "width": 2, "sign": True}) == "s16"
    assert symbol._return_type({"kind": "value", "width": 1, "sign": False}) == "u8"
    assert symbol._return_type({"kind": "pointer", "width": 4, "sign": None}) == "void*"


def test_a_confidence_needs_agreement_to_be_proven() -> None:
    assert symbol._confidence(collections.Counter({"Battle": 3}), "Battle") == "proven"
    assert (
        symbol._confidence(collections.Counter({"Battle": 4, "Menu": 1}), "Battle")
        == "likely"
    )
    assert (
        symbol._confidence(collections.Counter({"Battle": 1, "Menu": 1}), "Battle")
        == "open"
    )
    assert symbol._confidence(collections.Counter(), "Battle") == "open"


def test_a_majority_tie_goes_to_the_lowest_layer_then_the_name() -> None:
    votes = collections.Counter({"Battle": 2, "Menu": 2})
    assert symbol._majority(votes, {"Battle": 4, "Menu": 2}, 0) == "Menu"
    assert symbol._majority(votes, {}, 0) == "Battle"
    assert symbol._majority(collections.Counter(), {}, 0) == ""


def test_a_caller_that_dereferences_the_result_proves_a_pointer() -> None:
    function_text = function(
        "Caller",
        0x24,
        [
            (0x801D1000, "jal", "Battle_Alloc"),
            (0x801D1004, "nop", ""),
            (0x801D1008, "lw", "$v1, 0x8($v0)"),
            (0x801D100C, "jr", "$ra"),
            (0x801D1010, "nop", ""),
        ],
    )
    caller = one(function_text)
    call = asmtext.Call("Battle_Alloc", 0x801D1000, [])
    assert symbol._v0_after_call(caller, call) == "pointer"


def test_a_caller_that_branches_on_the_result_proves_a_bool() -> None:
    function_text = function(
        "Caller",
        0x1C,
        [
            (0x801D1000, "jal", "Is_Ready"),
            (0x801D1004, "nop", ""),
            (0x801D1008, "beqz", "$v0, .L801D1014"),
            (0x801D100C, "nop", ""),
        ],
    )
    caller = one(function_text)
    call = asmtext.Call("Is_Ready", 0x801D1000, [])
    assert symbol._v0_after_call(caller, call) == "bool"
