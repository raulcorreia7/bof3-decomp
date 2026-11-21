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
