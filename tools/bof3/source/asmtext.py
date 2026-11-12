"""Read the split assembly of a target: functions, instructions and their dataflow.

The split under ``asm/<image>/`` holds every function, matched or not. Each instruction line
carries its file offset, its address and its word, then the spimdisasm mnemonic with symbol names
in place of raw addresses. ``functions`` reads that text into an instruction list; ``decode``
interprets the register dataflow the evidence verbs need: the registers an instruction writes and
reads, the arguments a function uses and how, the globals and tables it touches, and what it
returns.
"""

from __future__ import annotations

import re
from dataclasses import dataclass, field

_HEADER = re.compile(
    r"^\s*/\*\s*([0-9A-Fa-f]+)\s+([0-9A-Fa-f]{8})\s+([0-9A-Fa-f]{8})\s*\*/\s*"
    r"(\S+)(?:\s+(.*?))?\s*$"
)
_GLABEL = re.compile(r"^\s*glabel\s+(\w+)\s*$")
_SIZE = re.compile(r"^\s*(?:nonmatching|matching)\s+(\w+),\s*(0x[0-9A-Fa-f]+)", re.M)
_COMMENT = re.compile(r"/\*.*?\*/")
_MEMORY = re.compile(r"^(?P<expr>.*?)\((?P<base>\$[A-Za-z0-9]+)\)$")
_HI_LO = re.compile(r"^%(?:hi|lo)\((?P<inner>.+)\)$")
_SHIFT = re.compile(
    r"^\(\s*(?P<value>-?(?:0x[0-9A-Fa-f]+|\d+))\s*>>\s*(?P<amount>\d+)\s*\)$"
)
_MASK = re.compile(
    r"^\(\s*(?P<value>-?(?:0x[0-9A-Fa-f]+|\d+))\s*&\s*(?P<mask>0x[0-9A-Fa-f]+|\d+)\s*\)$"
)
_SYMBOL = re.compile(
    r"^(?P<name>[A-Za-z_.][\w.]*)(?:\s*\+\s*(?P<offset>0x[0-9A-Fa-f]+|\d+))?$"
)
_INTEGER = re.compile(r"^-?(?:0x[0-9A-Fa-f]+|\d+)$")
_REGISTER = re.compile(r"^\$([A-Za-z0-9]+)$")

REGISTERS = {
    name: number
    for number, name in enumerate(
        (
            "zero", "at", "v0", "v1", "a0", "a1", "a2", "a3",
            "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
            "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7",
            "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra",
        )
    )
}  # fmt: skip
REGISTERS.update({str(number): number for number in range(32)})
ARG_REGISTERS = (4, 5, 6, 7)

#: The operand a mnemonic writes, when it writes a general register.
DEST = {
    "lui": 0,
    "lb": 0,
    "lbu": 0,
    "lh": 0,
    "lhu": 0,
    "lw": 0,
    "lwl": 0,
    "lwr": 0,
    "lwc2": 0,
    "addi": 0,
    "addiu": 0,
    "slti": 0,
    "sltiu": 0,
    "andi": 0,
    "ori": 0,
    "xori": 0,
    "sll": 0,
    "srl": 0,
    "sra": 0,
    "sllv": 0,
    "srlv": 0,
    "srav": 0,
    "addu": 0,
    "add": 0,
    "sub": 0,
    "subu": 0,
    "and": 0,
    "or": 0,
    "xor": 0,
    "nor": 0,
    "slt": 0,
    "sltu": 0,
    "negu": 0,
    "not": 0,
    "mflo": 0,
    "mfhi": 0,
    "mfc0": 0,
    "mfc2": 0,
    "cfc2": 0,
}
LOADS = {"lb", "lbu", "lh", "lhu", "lw", "lwl", "lwr", "lwc2"}
STORES = {"sb", "sh", "sw", "swl", "swr", "swc2"}
READ_WIDTH = {
    "lb": (1, True),
    "lbu": (1, False),
    "lh": (2, True),
    "lhu": (2, False),
    "lw": (4, None),
}
WRITE_WIDTH = {"sb": 1, "sh": 2, "sw": 4}
MEMORY_OPS = LOADS | STORES
MAX_STRIDE = 0x400


@dataclass(frozen=True, slots=True)
class Insn:
    """One instruction: its address, its mnemonic and its operand text."""

    address: int
    mnemonic: str
    operands: str


@dataclass(slots=True)
class Function:
    """One split function and its instructions."""

    image: str
    name: str
    address: int
    size: int
    source: str
    insns: list[Insn] = field(default_factory=list)


@dataclass(frozen=True, slots=True)
class Value:
    """A register's known value: a constant, a symbol's address, an argument or an index."""

    kind: str  # "imm", "sym", "arg" or "index"
    name: str = ""
    offset: int = 0
    number: int = 0
    argument: int = 0


@dataclass(frozen=True, slots=True)
class Access:
    """One load or store that reaches a symbol or an argument: offset, width and sign."""

    name: str
    table: str
    offset: int
    width: int
    signed: bool | None
    mnemonic: str
    address: int
    write: bool


@dataclass(slots=True)
class ArgUse:
    """How a function uses one of its argument registers."""

    index: int
    accesses: list[Access] = field(default_factory=list)
    narrow: str | None = None


@dataclass(slots=True)
class Call:
    """One call: the callee name and the argument registers set before it."""

    callee: str
    address: int
    arguments: list[int] = field(default_factory=list)


@dataclass(slots=True)
class Facts:
    """What one function's instructions prove about its signature and its data uses."""

    accesses: list[Access] = field(default_factory=list)
    symbols: list[tuple[str, str]] = field(default_factory=list)
    strides: dict[tuple[str, str], set[int]] = field(default_factory=dict)
    calls: list[Call] = field(default_factory=list)
    indirect: bool = False
    args: dict[int, ArgUse] = field(default_factory=dict)
    stack_arguments: int = 0
    return_writes: list[tuple[str, str]] = field(default_factory=list)
    return_width: tuple[int, bool | None] | None = None


def functions(text: str, image: str, source: str) -> list[Function]:
    """Read one split assembly file into its functions, in the order they appear."""
    sizes = {match.group(1): int(match.group(2), 16) for match in _SIZE.finditer(text)}
    found: list[Function] = []
    current: Function | None = None
    for line in text.split("\n"):
        label = _GLABEL.match(line)
        if label:
            current = Function(
                image, label.group(1), 0, sizes.get(label.group(1), 0), source
            )
            found.append(current)
            continue
        if current is None:
            continue
        match = _HEADER.match(line)
        if match:
            address = int(match.group(2), 16)
            if not current.insns:
                current.address = address
            current.insns.append(
                Insn(address, match.group(4), (match.group(5) or "").strip())
            )
        elif line.startswith("endlabel"):
            current = None
    for function in found:
        if function.insns:
            function.address = function.address or function.insns[0].address
    return found


def operands(text: str) -> list[str]:
    """Split operand text on the commas outside parentheses and comments."""
    text = _COMMENT.sub("", text).strip()
    if not text:
        return []
    parts: list[str] = []
    depth = 0
    start = 0
    for index, char in enumerate(text):
        if char == "(":
            depth += 1
        elif char == ")":
            depth -= 1
        elif char == "," and depth == 0:
            parts.append(text[start:index].strip())
            start = index + 1
    parts.append(text[start:].strip())
    return [part for part in parts if part]


def register(text: str) -> int | None:
    """Return a register's number from ``$name``, else None."""
    match = _REGISTER.match(text.strip())
    return REGISTERS.get(match.group(1)) if match else None


def integer(text: str) -> int | None:
    """Return an integer operand's value, resolving the high and low halves of an address."""
    text = text.strip()
    if _INTEGER.match(text):
        return int(text, 0)
    shift = _SHIFT.match(text)
    if shift:
        return int(shift.group("value"), 0) >> int(shift.group("amount"))
    mask = _MASK.match(text)
    if mask:
        return int(mask.group("value"), 0) & int(mask.group("mask"), 0)
    return None


def symbol(text: str) -> tuple[str, int] | None:
    """Return a symbol operand's name and offset, resolving ``%hi``/``%lo``."""
    text = text.strip()
    wrapped = _HI_LO.match(text)
    if wrapped:
        text = wrapped.group("inner").strip()
    match = _SYMBOL.match(text)
    if not match:
        return None
    offset = int(match.group("offset"), 0) if match.group("offset") else 0
    return match.group("name"), offset


def memory(text: str) -> tuple[str, int] | None:
    """Return a memory operand's expression and base register number."""
    match = _MEMORY.match(text.strip())
    if not match:
        return None
    base = register(match.group("base"))
    if base is None:
        return None
    return match.group("expr").strip(), base


def read_write(mnemonic: str, ops: list[str]) -> tuple[int | None, list[int]]:
    """Return the register an instruction writes and every register it reads."""
    if mnemonic == "jal":
        return None, []
    if mnemonic == "jalr":
        regs = [reg for reg in map(register, ops) if reg is not None]
        if len(regs) == 2:
            return regs[0], [regs[1]]
        return None, regs[:1]
    if mnemonic in ("mult", "multu", "div", "divu", "mtlo", "mthi", "mtc2", "ctc2"):
        return None, [reg for reg in map(register, ops) if reg is not None]
    index = DEST.get(mnemonic)
    written = register(ops[index]) if index is not None and index < len(ops) else None
    reads: list[int] = []
    for position, operand in enumerate(ops):
        if position == index:
            continue
        part = memory(operand)
        if part is not None:
            reads.append(part[1])
            continue
        reg = register(operand)
        if reg is not None:
            reads.append(reg)
    return written, reads


def _operand_value(text: str) -> Value | None:
    """Return an operand expression's value: a symbol or a constant, else None."""
    if _INTEGER.match(text.strip()):
        return Value("imm", number=int(text.strip(), 0))
    named = symbol(text)
    if named is not None:
        return Value("sym", named[0], named[1])
    return None


def _plus(value: Value | None, delta: int) -> Value | None:
    if value is None:
        return None
    if value.kind == "imm":
        return Value("imm", number=value.number + delta)
    if value.kind == "sym":
        return Value("sym", value.name, value.offset + delta)
    if value.kind == "arg":
        return Value("arg", offset=value.offset + delta, argument=value.argument)
    return None


def _arg_use(facts: Facts, register_number: int) -> ArgUse:
    index = register_number - ARG_REGISTERS[0]
    return facts.args.setdefault(index, ArgUse(index))


def decode(
    function: Function,
    symbols: dict[str, tuple[str, int]],
    owner,
) -> Facts:
    """Interpret one function's register dataflow into its signature and data evidence.

    ``symbols`` maps a name the image can see to its ``(table, address)``; ``owner`` maps an
    address to ``(table, name, offset)`` so arithmetic on a constant base resolves to a symbol.
    """
    facts = Facts()
    values: dict[int, Value] = {}
    known: set[int] = set()
    pending_narrow: dict[int, tuple[int, int]] = {}
    frame = 0
    frame_seen = False
    seen: set[tuple[str, str]] = set()

    def add_access(name: str, table: str, offset: int, insn: Insn, write: bool) -> None:
        width, signed = READ_WIDTH.get(insn.mnemonic, (4, None))
        if insn.mnemonic in STORES:
            width = WRITE_WIDTH.get(insn.mnemonic, 4)
        facts.accesses.append(
            Access(
                name, table, offset, width, signed, insn.mnemonic, insn.address, write
            )
        )
        if name and (table, name) not in seen:
            seen.add((table, name))
            facts.symbols.append((table, name))

    for index, insn in enumerate(function.insns):
        mnemonic = insn.mnemonic
        if mnemonic.startswith("."):
            continue
        ops = operands(insn.operands)
        dest, reads = read_write(mnemonic, ops)
        prior = frozenset(known)
        for reg in reads:
            if reg in ARG_REGISTERS and reg not in known:
                _arg_use(facts, reg)

        if mnemonic == "lui" and len(ops) >= 2:
            if dest is not None:
                known.add(dest)
            value = _operand_value(ops[1])
            constant = integer(ops[1])
            if dest is None:
                continue
            if value is not None and value.kind == "sym":
                values[dest] = value
            elif constant is not None:
                values[dest] = Value("imm", number=(constant & 0xFFFF) << 16)
            else:
                values.pop(dest, None)
            continue

        if mnemonic in ("addi", "addiu", "ori", "xori") and len(ops) >= 3:
            base_register = register(ops[1])
            base_known = base_register in known
            base = values.get(base_register)
            constant = integer(ops[2]) or 0
            if dest is not None:
                known.add(dest)
                if base is not None and base.kind == "imm":
                    values[dest] = Value("imm", number=base.number + constant)
                elif base is not None and base.kind == "sym":
                    if dest == base_register and 0 < abs(constant) <= MAX_STRIDE:
                        table = symbols.get(base.name, ("", 0))[0]
                        facts.strides.setdefault((table, base.name), set()).add(
                            abs(constant)
                        )
                    values[dest] = _plus(base, constant)
                elif base is not None and base.kind == "arg":
                    values[dest] = _plus(base, constant)
                elif base_register in ARG_REGISTERS and not base_known:
                    values[dest] = _plus(_arg_value(base_register), constant)
                else:
                    values.pop(dest, None)
            if base_register == 29 and constant < 0 and not frame_seen:
                frame = -constant
                frame_seen = True
            continue

        if mnemonic in ("addu", "add") and len(ops) >= 3:
            left = _reg_value(values, register(ops[1]), prior)
            right = _reg_value(values, register(ops[2]), prior)
            if dest is not None:
                known.add(dest)
            if (
                left is not None
                and left.kind == "imm"
                and right is not None
                and right.kind == "imm"
            ):
                values[dest] = Value("imm", number=left.number + right.number)
            elif left is not None and left.kind == "sym" and right is not None:
                _record_stride(facts, symbols, left.name, right)
                values[dest] = Value("sym", left.name, left.offset)
            elif right is not None and right.kind == "sym" and left is not None:
                _record_stride(facts, symbols, right.name, left)
                values[dest] = Value("sym", right.name, right.offset)
            elif left is not None and left.kind == "arg" and right is not None:
                values[dest] = Value("arg", offset=left.offset, argument=left.argument)
            elif right is not None and right.kind == "arg" and left is not None:
                values[dest] = Value(
                    "arg", offset=right.offset, argument=right.argument
                )
            elif dest is not None:
                values.pop(dest, None)
            continue

        if mnemonic in ("sll", "srl", "sra") and len(ops) >= 3:
            amount = integer(ops[2])
            source = register(ops[1])
            base = values.get(source)
            if dest is not None:
                known.add(dest)
                if base is not None and base.kind == "imm" and amount is not None:
                    values[dest] = Value(
                        "imm",
                        number=base.number << amount
                        if mnemonic == "sll"
                        else base.number >> amount,
                    )
                elif mnemonic == "sll" and amount in (1, 2, 3):
                    values[dest] = Value("index", number=1 << amount)
                else:
                    values.pop(dest, None)
            narrow = _narrowing(mnemonic, amount)
            if narrow is not None:
                argument = (
                    source - ARG_REGISTERS[0]
                    if source in ARG_REGISTERS and source not in prior
                    else base.argument
                    if base is not None and base.kind == "arg"
                    else None
                )
                if argument is not None:
                    if narrow[0] == "u":
                        _arg_use(facts, argument + ARG_REGISTERS[0]).narrow = (
                            _arg_use(facts, argument + ARG_REGISTERS[0]).narrow
                            or narrow[1]
                        )
                    else:
                        pending_narrow[dest] = (argument, amount)
            elif mnemonic == "sra" and source in pending_narrow:
                argument, shift = pending_narrow[source]
                if shift == amount:
                    arg = _arg_use(facts, argument + ARG_REGISTERS[0])
                    arg.narrow = arg.narrow or narrow_sign(shift)
            continue

        if mnemonic in ("mult", "multu") and len(ops) >= 2:
            stride = 0
            for operand in ops[:2]:
                value = values.get(register(operand))
                if (
                    value is not None
                    and value.kind == "imm"
                    and 0 < value.number <= MAX_STRIDE
                ):
                    stride = value.number
            values[-2] = Value("index", number=stride)
            continue

        if mnemonic == "mflo" and dest is not None:
            known.add(dest)
            values[dest] = values.get(-2, Value("index", number=0))
            continue

        if mnemonic == "andi" and len(ops) >= 3:
            source = register(ops[1])
            base = values.get(source)
            mask = integer(ops[2])
            if dest is not None:
                known.add(dest)
                values.pop(dest, None)
            if mask in (0xFF, 0xFFFF):
                argument = (
                    source - ARG_REGISTERS[0]
                    if source in ARG_REGISTERS and source not in prior
                    else base.argument
                    if base is not None and base.kind == "arg"
                    else None
                )
                if argument is not None:
                    _arg_use(facts, argument + ARG_REGISTERS[0]).narrow = (
                        "u8" if mask == 0xFF else "u16"
                    )
            continue

        if mnemonic in MEMORY_OPS and len(ops) >= 2:
            part = memory(ops[1])
            if dest is not None:
                known.add(dest)
                values.pop(dest, None)
            if part is not None:
                _record_memory(
                    facts,
                    insn,
                    part,
                    values,
                    symbols,
                    owner,
                    frame,
                    prior,
                    add_access,
                )
            continue

        if dest is not None:
            known.add(dest)
            values.pop(dest, None)
        if mnemonic == "jal" and ops:
            named = symbol(ops[0])
            if named is not None:
                facts.calls.append(
                    Call(named[0], insn.address, _call_registers(function.insns, index))
                )
        if mnemonic in ("jal", "jalr"):
            if mnemonic == "jalr":
                facts.indirect = True
            known.update(ARG_REGISTERS)
    facts.return_writes = return_writes(function)
    facts.return_width = return_width(function)
    return facts


def _arg_value(number: int) -> Value:
    return Value("arg", argument=number - ARG_REGISTERS[0])


def _reg_value(values: dict[int, Value], number: int | None, known) -> Value | None:
    """Return a register's value, reading an argument register or zero as what it supplies."""
    if number is None:
        return None
    if number == 0:
        return Value("imm", number=0)
    value = values.get(number)
    if value is None and number in ARG_REGISTERS and number not in known:
        return _arg_value(number)
    return value


def narrow_sign(shift: int) -> str:
    """Return the type a sign-extending shift amounts to: 24 is a byte and 16 a halfword."""
    return "s8" if shift == 24 else "s16"


def _narrowing(mnemonic: str, amount: int | None) -> tuple[str, str] | None:
    """Return the narrow type an ``andi`` or ``sll`` proves, else None."""
    if amount is None:
        return None
    if mnemonic == "andi" and amount in (0xFF, 0xFFFF):
        return ("u", "u8" if amount == 0xFF else "u16")
    if mnemonic == "sll" and amount in (24, 16):
        return ("s", narrow_sign(amount))
    return None


def _record_stride(
    facts: Facts,
    symbols: dict[str, tuple[str, int]],
    name: str,
    index_value: Value,
) -> None:
    if index_value.kind == "index" and index_value.number:
        table = symbols.get(name, ("", 0))[0]
        facts.strides.setdefault((table, name), set()).add(index_value.number)


def _record_memory(
    facts: Facts,
    insn: Insn,
    part: tuple[str, int],
    values: dict[int, Value],
    symbols: dict[str, tuple[str, int]],
    owner,
    frame: int,
    known: frozenset[int],
    add_access,
) -> None:
    """Record what one load or store proves: a symbol access, an argument use or a stack use."""
    expression, base = part
    write = insn.mnemonic in STORES
    named = symbol(expression)
    if named is not None and not _INTEGER.match(expression):
        name, offset = named
        add_access(name, symbols.get(name, ("", 0))[0], offset, insn, write)
        return
    constant = integer(expression) or 0
    value = values.get(base)
    if value is not None and value.kind == "sym":
        add_access(
            value.name,
            symbols.get(value.name, ("", 0))[0],
            value.offset + constant,
            insn,
            write,
        )
        return
    if value is not None and value.kind == "imm":
        found = owner(value.number + constant)
        if found is not None:
            add_access(found[1], found[0], found[2], insn, write)
        return
    if value is not None and value.kind == "arg":
        argument = value.argument
        offset = value.offset + constant
    elif base in ARG_REGISTERS and base not in known:
        argument = base - ARG_REGISTERS[0]
        offset = constant
    else:
        argument = None
        offset = constant
    if argument is not None and base not in (29, 30):
        _arg_use(facts, ARG_REGISTERS[0] + argument).accesses.append(
            Access(
                "",
                "",
                offset,
                _width(insn),
                _signed(insn),
                insn.mnemonic,
                insn.address,
                write,
            )
        )
        return
    if base == 29 and constant >= frame + 0x10:
        facts.stack_arguments = max(
            facts.stack_arguments, (constant - frame - 0x10) // 4 + 1
        )


def _width(insn: Insn) -> int:
    if insn.mnemonic in STORES:
        return WRITE_WIDTH.get(insn.mnemonic, 4)
    return READ_WIDTH.get(insn.mnemonic, (4, None))[0]


def _signed(insn: Insn) -> bool | None:
    return READ_WIDTH.get(insn.mnemonic, (4, None))[1]


def _call_registers(insns: list[Insn], index: int) -> list[int]:
    """Return the argument registers a caller sets in the block before a call."""
    found: set[int] = set()
    positions = [index + 1] if index + 1 < len(insns) else []
    for step in range(1, 13):
        position = index - step
        if position < 0:
            break
        mnemonic = insns[position].mnemonic
        if mnemonic in ("jal", "jalr", "jr", "j"):
            break
        positions.append(position)
    for position in positions:
        insn = insns[position]
        dest, _ = read_write(insn.mnemonic, operands(insn.operands))
        if dest in ARG_REGISTERS:
            found.add(dest)
    return sorted(found)


def v0_writes(function: Function) -> list[tuple[str, str]]:
    """Return every instruction that writes v0, in order."""
    writes: list[tuple[str, str]] = []
    for insn in function.insns:
        dest, _ = read_write(insn.mnemonic, operands(insn.operands))
        if dest == 2:
            writes.append((insn.mnemonic, insn.operands))
    return writes


def return_writes(function: Function) -> list[tuple[str, str]]:
    """Return the writes of v0 that reach a ``jr ra``: the function's returned values.

    The compiler leaves the result in v0 just before the epilogue, so a write up to four
    instructions before the return, or in its delay slot, is the returned value; earlier
    writes to v0 are scratch.
    """
    insns = function.insns
    found: list[tuple[str, str]] = []
    for index, insn in enumerate(insns):
        if insn.mnemonic != "jr":
            continue
        ops = operands(insn.operands)
        if not ops or register(ops[0]) != 31:
            continue
        for position in range(index + 1, max(-1, index - 12), -1):
            if position == index:
                continue
            if not 0 <= position < len(insns):
                continue
            earlier = insns[position]
            if _epilogue(earlier):
                continue
            dest, _ = read_write(earlier.mnemonic, operands(earlier.operands))
            if dest == 2:
                found.append((earlier.mnemonic, earlier.operands))
            break
    return found


def _epilogue(insn: Insn) -> bool:
    """Whether an instruction only restores the frame before the return."""
    if insn.mnemonic == "nop":
        return True
    ops = operands(insn.operands)
    if (
        insn.mnemonic == "addiu"
        and len(ops) >= 2
        and register(ops[0]) == 29
        and register(ops[1]) == 29
    ):
        return True
    for operand in ops:
        part = memory(operand)
        if part is not None and part[1] == 29:
            return insn.mnemonic in LOADS or insn.mnemonic == "addiu"
    return False


def bool_write(mnemonic: str, operands_text: str) -> bool:
    """Whether one write of v0 produces 0 or 1."""
    if mnemonic in ("slt", "sltu", "slti", "sltiu"):
        return True
    if mnemonic in ("addiu", "ori", "addi"):
        ops = operands_text.split(",")
        return len(ops) >= 3 and register(ops[1]) == 0 and integer(ops[2]) in (0, 1)
    return False


def width_of(mnemonic: str, operands_text: str) -> tuple[int, bool | None] | None:
    """Return the width and sign a write gives the value, else None."""
    if mnemonic in READ_WIDTH:
        return READ_WIDTH[mnemonic]
    if mnemonic in ("andi", "ori"):
        constant = integer(operands_text.split(",")[-1])
        if constant == 0xFF:
            return (1, False)
        if constant == 0xFFFF:
            return (2, False)
        return (4, None)
    if mnemonic in ("sll", "srl", "sra"):
        constant = integer(operands_text.split(",")[-1])
        if constant == 24:
            return (1, mnemonic == "sra")
        if constant == 16:
            return (2, mnemonic == "sra")
        return (4, None)
    if mnemonic in ("slt", "sltu", "slti", "sltiu"):
        return (1, False)
    if mnemonic.startswith(("add", "sub", "and", "or", "xor", "nor")):
        return (4, None)
    return None


def return_width(function: Function) -> tuple[int, bool | None] | None:
    """Return the width of the returned value, from the write that reaches ``jr ra``."""
    for mnemonic, text in return_writes(function):
        found = width_of(mnemonic, text)
        if found is not None:
            return found
    return None


def _write_width(insn: Insn) -> tuple[int, bool | None] | None:
    dest, _ = read_write(insn.mnemonic, operands(insn.operands))
    if dest != 2:
        return None
    return width_of(insn.mnemonic, insn.operands)
