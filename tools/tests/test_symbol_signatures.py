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


def test_a_value_consumed_by_the_return_delay_slot_is_not_a_return() -> None:
    function_text = function(
        "Void",
        0x14,
        [
            (0x801D1000, "lbu", "$v0, 0x3($v1)"),
            (0x801D1004, "addiu", "$v0, $v0, 0x1"),
            (0x801D1008, "jr", "$ra"),
            (0x801D100C, "sb", "$v0, 0x3($v1)"),
        ],
    )
    facts = asmtext.decode(one(function_text), {}, lambda address: None)
    assert facts.return_writes == []


def test_a_delay_slot_write_that_targets_the_epilogue_is_a_return() -> None:
    function_text = function(
        "Value",
        0x24,
        [
            (0x801D1000, "bnez", "$a0, .L801D1014"),
            (0x801D1004, "addu", "$v0, $a1, $zero"),
            (0x801D1008, "nop", ""),
            (0x801D100C, "j", ".L801D1014"),
            (0x801D1010, "nop", ""),
            (0x801D1014, "lw", "$ra, 0x10($sp)"),
            (0x801D1018, "addiu", "$sp, $sp, 0x18"),
            (0x801D101C, "jr", "$ra"),
            (0x801D1020, "nop", ""),
        ],
    )
    facts = asmtext.decode(one(function_text), {}, lambda address: None)
    assert facts.return_writes == [("addu", "$v0, $a1, $zero")]
    assert not facts.ambiguous_return


def test_a_loop_delay_slot_that_writes_v0_makes_the_return_ambiguous() -> None:
    function_text = function(
        "Loop",
        0x20,
        [
            (0x801D1000, "andi", "$v0, $a0, 0xFF"),
            (0x801D1004, "sltiu", "$v0, $v0, 0x2"),
            (0x801D1008, "bnez", "$v0, .L801D1000"),
            (0x801D100C, "andi", "$v0, $a1, 0xFF"),
            (0x801D1010, "lw", "$ra, 0x10($sp)"),
            (0x801D1014, "addiu", "$sp, $sp, 0x18"),
            (0x801D1018, "jr", "$ra"),
            (0x801D101C, "nop", ""),
        ],
    )
    facts = asmtext.decode(one(function_text), {}, lambda address: None)
    assert facts.return_writes == []
    assert facts.ambiguous_return


def test_a_stack_argument_used_as_a_base_is_a_pointer() -> None:
    function_text = function(
        "StackPointer",
        0x20,
        [
            (0x801D1000, "addiu", "$sp, $sp, -0x20"),
            (0x801D1004, "lw", "$t0, 0x30($sp)"),
            (0x801D1008, "lw", "$v0, 0x4($t0)"),
            (0x801D100C, "jr", "$ra"),
            (0x801D1010, "nop", ""),
        ],
    )
    facts = asmtext.decode(one(function_text), {}, lambda address: None)
    assert facts.stack_arguments == 1
    assert facts.stack_pointers == {0}


def tree_with(*texts: str):
    from bof3.source import decls

    return decls.Tree({f"h{index}.h": text for index, text in enumerate(texts)})


def test_a_pointer_forwarded_to_a_declared_pointer_parameter_is_proven() -> None:
    caller_text = function(
        "Forward",
        0x20,
        [
            (0x801D1000, "addu", "$a1, $a0, $zero"),
            (0x801D1004, "jal", "Callee"),
            (0x801D1008, "nop", ""),
            (0x801D100C, "jr", "$ra"),
            (0x801D1010, "nop", ""),
        ],
    )
    caller = one(caller_text)
    facts = asmtext.decode(caller, {}, lambda address: None)
    tree = tree_with(
        "typedef struct Record { u8 a; } Record;", "void Callee(s32 n, Record* r);"
    )
    assert symbol._forwarded_pointer(caller, facts, 0, tree, {"h1.h"}) == "Record"


def test_a_pointer_result_reaching_an_argument_is_a_pointer() -> None:
    caller_text = function(
        "Pass",
        0x28,
        [
            (0x801D1000, "jal", "Message_GetText"),
            (0x801D1004, "nop", ""),
            (0x801D1008, "addiu", "$a0, $zero, 0x2"),
            (0x801D100C, "addiu", "$a1, $zero, 0x30"),
            (0x801D1010, "jal", "AddMessage"),
            (0x801D1014, "addu", "$a2, $v0, $zero"),
            (0x801D1018, "jr", "$ra"),
            (0x801D101C, "nop", ""),
        ],
    )
    caller = one(caller_text)
    facts = asmtext.decode(caller, {}, lambda address: None)
    call = next(call for call in facts.calls if call.callee == "AddMessage")
    tree = tree_with(
        "u8* Message_GetText(s32 id);", "void AddMessage(s32 a, s32 b, u8* text);"
    )
    assert symbol._caller_argument_kind(caller, call, 2, tree, {"h1.h"}) == "pointer"


def test_a_narrow_declared_argument_caps_a_proven_row_at_likely() -> None:
    function_text = function(
        "Take",
        0x20,
        [
            (0x801D1000, "andi", "$a0, $a0, 0xFF"),
            (0x801D1004, "jr", "$ra"),
            (0x801D1008, "nop", ""),
        ],
    )
    target = one(function_text)
    facts = asmtext.decode(target, {}, lambda address: None)
    caller_text = function(
        "Caller",
        0x18,
        [
            (0x801D1000, "addiu", "$a0, $zero, 0x4"),
            (0x801D1004, "jal", "Take"),
            (0x801D1008, "nop", ""),
            (0x801D100C, "jr", "$ra"),
            (0x801D1010, "nop", ""),
        ],
    )
    caller = one(caller_text)
    tree = tree_with("void Take(u8 value);")
    row = symbol._function_signature(
        target,
        facts,
        [(caller, asmtext.Call("Take", 0x801D1004, [4]))],
        None,
        tree,
        {"h0.h"},
    )
    assert row["args"][0]["kind"] == "u8"
    assert row["confidence"] == "likely"


def fake_manifests():
    from types import SimpleNamespace

    return {
        "emi/test/00": SimpleNamespace(source_dir="src/overlays/battle/test/00"),
        "emi/menu/00": SimpleNamespace(source_dir="src/overlays/menu/00"),
        "emi/etc/game/00": SimpleNamespace(source_dir="src/engine/game/00"),
    }


def test_three_callers_move_a_function_to_their_system() -> None:
    function = asmtext.Function(
        "emi/test/00", "func_801F0000", 0x801F0000, 4, "asm/x.s"
    )
    facts = asmtext.Facts()
    callers = {
        ("emi/test/00", "func_801F0000"): [
            (asmtext.Function("emi/test/00", "Menu_First", 0x801F1000, 4, "x"), None),
            (asmtext.Function("emi/test/00", "Menu_Second", 0x801F2000, 4, "x"), None),
            (asmtext.Function("emi/menu/00", "Menu_Third", 0x801F3000, 4, "x"), None),
        ]
    }
    rules = symbol._function_candidates(
        function,
        facts,
        None,
        fake_manifests(),
        callers,
        {},
        {},
        None,
        None,
        "Battle",
        False,
    )
    assert any(line.startswith("rule a") for line in rules["Menu"])


def test_a_single_writer_with_foreign_readers_moves_a_function() -> None:
    function = asmtext.Function(
        "emi/test/00", "func_801F0000", 0x801F0000, 4, "asm/x.s"
    )
    facts = asmtext.Facts(
        accesses=[
            asmtext.Access(
                "g_MenuChoice", "emi/test/00", 0, 4, None, "sw", 0x801F0000, True
            )
        ]
    )
    key = ("g_MenuChoice", 0x801F4000)

    class Index:
        def resolve(self, image, name):
            from types import SimpleNamespace

            return SimpleNamespace(addr=0x801F4000)

    writers = {key: {("emi/test/00", "func_801F0000")}}
    readers = {key: {("emi/menu/00", "Menu_Read")}}
    rules = symbol._function_candidates(
        function,
        facts,
        Index(),
        fake_manifests(),
        {},
        writers,
        readers,
        None,
        None,
        "Battle",
        False,
    )
    assert any(line.startswith("rule b") for line in rules["Menu"])


def test_a_function_between_two_system_functions_moves_with_no_local_caller() -> None:
    function = asmtext.Function(
        "emi/test/00", "func_801F0000", 0x801F0000, 4, "asm/x.s"
    )
    previous = asmtext.Function("emi/test/00", "Menu_Left", 0x801EF000, 4, "asm/x.s")
    following = asmtext.Function("emi/test/00", "Menu_Right", 0x801F1000, 4, "asm/x.s")
    rules = symbol._function_candidates(
        function,
        asmtext.Facts(),
        None,
        fake_manifests(),
        {},
        {},
        {},
        previous,
        following,
        "Battle",
        True,
    )
    assert any(line.startswith("rule c") for line in rules["Menu"])


def test_an_overlay_local_function_ignores_caller_and_writer_rules() -> None:
    function = asmtext.Function("emi/test/00", "Battle_Step", 0x801F0000, 4, "asm/x.s")
    facts = asmtext.Facts(
        accesses=[
            asmtext.Access("g_MenuChoice", "emi/test/00", 0, 4, None, "sw", 0, True)
        ]
    )

    class Index:
        def resolve(self, image, name):
            from types import SimpleNamespace

            return SimpleNamespace(addr=0x801F4000)

    callers = {
        ("emi/test/00", "Battle_Step"): [
            (asmtext.Function("emi/test/00", "Menu_One", 0x801F1000, 4, "x"), None),
            (asmtext.Function("emi/test/00", "Menu_Two", 0x801F2000, 4, "x"), None),
            (asmtext.Function("emi/test/00", "Menu_Three", 0x801F3000, 4, "x"), None),
        ]
    }
    writers = {("g_MenuChoice", 0x801F4000): {("emi/test/00", "Battle_Step")}}
    readers = {("g_MenuChoice", 0x801F4000): {("emi/menu/00", "Menu_Read")}}
    rules = symbol._function_candidates(
        function,
        facts,
        Index(),
        fake_manifests(),
        callers,
        writers,
        readers,
        None,
        None,
        "Battle",
        True,
    )
    assert rules == {}
