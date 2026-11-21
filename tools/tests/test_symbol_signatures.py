from __future__ import annotations

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


def tree_with(*texts: str):
    from bof3.source import decls

    return decls.Tree({f"h{index}.h": text for index, text in enumerate(texts)})


def fake_manifests():
    from types import SimpleNamespace

    return {
        "emi/test/00": SimpleNamespace(source_dir="src/overlays/battle/test/00"),
        "emi/menu/00": SimpleNamespace(source_dir="src/overlays/menu/00"),
        "emi/etc/game/00": SimpleNamespace(source_dir="src/engine/game/00"),
    }
