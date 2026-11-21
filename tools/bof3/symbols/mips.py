"""Decode the memory accesses of one function's instructions."""

from __future__ import annotations

import bisect
from dataclasses import dataclass

MIPS_READ = {
    "lb": (1, True),
    "lbu": (1, False),
    "lh": (2, True),
    "lhu": (2, False),
    "lw": (4, None),
}


MIPS_WRITE = {"sb": 1, "sh": 2, "sw": 4}


MIPS_WRITE_OPS = {0x28, 0x29, 0x2B}


MIPS_OPCODES = {
    0x08: "addi",
    0x09: "addiu",
    0x0A: "slti",
    0x0B: "sltiu",
    0x0C: "andi",
    0x0D: "ori",
    0x0F: "lui",
    0x20: "lb",
    0x21: "lh",
    0x23: "lw",
    0x24: "lbu",
    0x25: "lhu",
    0x28: "sb",
    0x29: "sh",
    0x2B: "sw",
    0x04: "beq",
    0x05: "bne",
    0x03: "jal",
}


REG_NAMES = [
    "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
    "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
    "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
    "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra",
]  # fmt: skip


CALLER_SAVED = set(range(1, 16)) | {24, 25}


@dataclass(frozen=True)
class AccessRange:
    """A global object an instruction can address: its extent, name and record type."""

    start: int
    end: int
    name: str
    type_name: str | None


@dataclass
class MipsAccess:
    """One load or store that lands in a target object or a traced pointer."""

    image: str
    function: str
    offset: int
    width: int
    mnemonic: str
    write: bool
    signed: bool | None
    instruction: str
    global_name: str | None = None
    type_name: str | None = None
    constant: int | None = None
    slot: str | None = None


def _signed16(value: int) -> int:
    return value - 0x10000 if value & 0x8000 else value


def _reg_name(number: int) -> str:
    return REG_NAMES[number] if 0 <= number < len(REG_NAMES) else f"r{number}"


def _offset_text(offset: int) -> str:
    return f"-0x{-offset:x}" if offset < 0 else f"0x{offset:x}"


def _instruction(word: int, call_name: str | None = None) -> str:
    op = word >> 26
    rs = (word >> 21) & 31
    rt = (word >> 16) & 31
    rd = (word >> 11) & 31
    imm = word & 0xFFFF
    funct = word & 63
    name = MIPS_OPCODES.get(op)
    if op == 0:
        if funct in (0x20, 0x21):
            return f"{'add' if funct == 0x20 else 'addu'} {_reg_name(rd)}, {_reg_name(rs)}, {_reg_name(rt)}"
        if funct == 0x08:
            return f"jr {_reg_name(rs)}"
        if funct == 0x09:
            return f"jalr {_reg_name(rs)}"
        return f"0x{word:08x}"
    if name == "lui":
        return f"lui {_reg_name(rt)}, 0x{imm:x}"
    if name in MIPS_READ or name in MIPS_WRITE:
        return (
            f"{name} {_reg_name(rt)}, {_offset_text(_signed16(imm))}({_reg_name(rs)})"
        )
    if name == "jal":
        return f"jal {call_name or f'0x{word & 0x03FFFFFF:08x}'}"
    if name in ("addi", "addiu", "slti", "sltiu"):
        return (
            f"{name} {_reg_name(rt)}, {_reg_name(rs)}, {_offset_text(_signed16(imm))}"
        )
    if name in ("andi", "ori"):
        return f"{name} {_reg_name(rt)}, {_reg_name(rs)}, 0x{imm:x}"
    if name in ("beq", "bne"):
        return (
            f"{name} {_reg_name(rs)}, {_reg_name(rt)}, {_offset_text(_signed16(imm))}"
        )
    return f"0x{word:08x}"


def _range_at(
    ranges: list[AccessRange], starts: list[int], address: int
) -> AccessRange | None:
    index = bisect.bisect_right(starts, address) - 1
    if index >= 0:
        found = ranges[index]
        if address < found.end:
            return found
    return None


def decode_accesses(
    image: str,
    function: str,
    address: int,
    words: tuple[int, ...],
    ranges: list[AccessRange],
    pointer_cells: dict[int, str],
    function_names: dict[int, str],
) -> tuple[list[MipsAccess], int, int]:
    """Decode one function: the accesses it makes into ranges or traced pointer types."""
    starts = [item.start for item in ranges]
    registers: dict[int, object] = {}
    loaded: dict[int, int] = {}
    moves: dict[int, tuple[int, int]] = {}
    accesses: list[MipsAccess] = []
    traced = 0
    untraced = 0
    for index, word in enumerate(words):
        op = word >> 26
        rs = (word >> 21) & 31
        rt = (word >> 16) & 31
        rd = (word >> 11) & 31
        imm = word & 0xFFFF
        simm = _signed16(imm)
        funct = word & 63
        pc = address + index * 4
        if op == 0x0F:
            registers[rt] = imm << 16
            loaded.pop(rt, None)
            moves.pop(rt, None)
            continue
        if op == 0x09:
            base = registers.get(rs)
            if isinstance(base, int):
                registers[rt] = base + simm
            elif isinstance(base, tuple):
                registers[rt] = (base[0], base[1] + simm)
            elif rs == 0:
                registers[rt] = simm
            else:
                registers.pop(rt, None)
            loaded.pop(rt, None)
            moves.pop(rt, None)
            continue
        if op == 0x0D:
            base = registers.get(rs)
            if isinstance(base, int):
                registers[rt] = base | imm
            elif rs == 0:
                registers[rt] = imm
            else:
                registers.pop(rt, None)
            loaded.pop(rt, None)
            moves.pop(rt, None)
            continue
        if op in (0x0A, 0x0B, 0x0C):
            if rs in loaded:
                access = accesses[loaded[rs]]
                if access.constant is None:
                    access.constant = simm if op in (0x0A, 0x0B) else imm
            registers.pop(rt, None)
            loaded.pop(rt, None)
            continue
        if op == 0:
            if funct in (0x20, 0x21):
                first = registers.get(rs)
                second = registers.get(rt)
                if rs == 0:
                    value = second
                elif rt == 0:
                    value = first
                else:
                    value = None
                if value is None:
                    registers.pop(rd, None)
                else:
                    registers[rd] = value
                loaded.pop(rd, None)
                if rd in (4, 5, 6, 7) and (rs == 0 or rt == 0):
                    moves[rd] = (rt if rs == 0 else rs, index)
                continue
            if funct == 0x08 and rs == 31:
                break
            if funct == 0x09:
                _attach_slots(accesses, moves, loaded, index, "jalr")
                _after_call(registers, loaded, moves)
                continue
            continue
        if op in (0x20, 0x21, 0x23, 0x24, 0x25, 0x28, 0x29, 0x2B):
            mnemonic = MIPS_OPCODES[op]
            base = registers.get(rs)
            found: AccessRange | None = None
            access: MipsAccess | None = None
            address_value = 0
            if isinstance(base, int):
                address_value = base + simm
                found = _range_at(ranges, starts, address_value)
                if found is not None:
                    traced += 1
                    access = MipsAccess(
                        image,
                        function,
                        address_value - found.start,
                        4,
                        mnemonic,
                        op in MIPS_WRITE_OPS,
                        None,
                        _instruction(word),
                        found.name,
                        found.type_name,
                    )
            elif isinstance(base, tuple):
                type_name, base_offset = base
                traced += 1
                access = MipsAccess(
                    image,
                    function,
                    base_offset + simm,
                    4,
                    mnemonic,
                    op in MIPS_WRITE_OPS,
                    None,
                    _instruction(word),
                    None,
                    type_name,
                )
            elif rs not in (29, 30):
                untraced += 1
            if access is not None:
                if mnemonic in MIPS_READ:
                    access.width, access.signed = MIPS_READ[mnemonic]
                else:
                    access.width = MIPS_WRITE[mnemonic]
                stored = registers.get(rt)
                if access.write and isinstance(stored, int):
                    access.constant = stored
                accesses.append(access)
                if not access.write:
                    loaded[rt] = len(accesses) - 1
                elif rt in loaded:
                    loaded.pop(rt, None)
            else:
                loaded.pop(rt, None)
            if isinstance(base, int) and address_value in pointer_cells:
                registers[rt] = (pointer_cells[address_value], 0)
            else:
                registers.pop(rt, None)
            continue
        if op == 0x03:
            target = ((word & 0x03FFFFFF) << 2) | (pc & 0xF0000000)
            name = function_names.get(target)
            _attach_slots(accesses, moves, loaded, index, name or f"0x{target:08X}")
            registers[31] = None
            _after_call(registers, loaded, moves)
            continue
        if op in (0x04, 0x05):
            if rs == 0 or rt == 0:
                other = rt if rs == 0 else rs
                if other in loaded:
                    access = accesses[loaded[other]]
                    if access.constant is None:
                        access.constant = 0
            else:
                first, second = registers.get(rs), registers.get(rt)
                if isinstance(first, int) and rt in loaded:
                    accesses[loaded[rt]].constant = first
                elif isinstance(second, int) and rs in loaded:
                    accesses[loaded[rs]].constant = second
            continue
    return accesses, traced, untraced


def _attach_slots(
    accesses: list[MipsAccess],
    moves: dict[int, tuple[int, int]],
    loaded: dict[int, int],
    index: int,
    callee: str,
) -> None:
    for slot, (source, position) in moves.items():
        if index - position > 4 or source not in loaded:
            continue
        access = accesses[loaded[source]]
        label = f"{callee}[{_reg_name(slot)}]"
        if access.slot is None:
            access.slot = label
        elif label not in access.slot.split(","):
            access.slot += "," + label


def _after_call(
    registers: dict[int, object],
    loaded: dict[int, int],
    moves: dict[int, tuple[int, int]],
) -> None:
    for reg in list(registers):
        if reg in CALLER_SAVED or isinstance(registers[reg], tuple):
            registers.pop(reg, None)
    for reg in list(loaded):
        if reg in CALLER_SAVED:
            loaded.pop(reg, None)
    moves.clear()
