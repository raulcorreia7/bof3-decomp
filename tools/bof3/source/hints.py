"""Facts in one function's assembly that point at its C form.

Each detector returns Markdown lines for ``seed.py``'s ``hints.md``; every line names the
``docs/matching.md#tactics-for-gcc-272`` row it maps to. A detector reads the parsed instructions
only, so the same code runs on a split ``.s`` file and on a matched function's words.
"""

from __future__ import annotations

import argparse
import contextlib
import io
import re
from collections import Counter
from dataclasses import dataclass, field
from pathlib import Path

from bof3.link import symbols
from bof3.source.index import Func

TACTIC = "docs/matching.md#tactics-for-gcc-272"
ARGUMENTS = frozenset(("a0", "a1", "a2", "a3"))
SAVED = frozenset(f"s{number}" for number in range(8))
SCRATCH = re.compile(r"0x1F80[0-9A-Fa-f]{4}")
MEMORY = re.compile(r"(?P<offset>[^()]*)\((?P<base>\$?\w+)\)")
NUMBER = re.compile(r"-?(?:0x[0-9A-Fa-f]+|\d+)")


@dataclass(frozen=True)
class Insn:
    """One parsed instruction, or a label named by ``label``."""

    op: str
    args: tuple[str, ...] = ()
    addr: int = -1
    label: str = ""
    text: str = ""


@dataclass
class Context:
    """What a detector may read besides the instructions."""

    root: Path
    func: Func
    table: dict[str, list[symbols.Entry]]
    splat: str
    ranked: tuple[tuple[float, Func], ...] = field(default_factory=tuple)
    at: dict[int, str] = field(default_factory=dict)


def parse(text: str) -> list[Insn]:
    """Return the instructions and labels of one assembly function."""
    out: list[Insn] = []
    for raw in text.splitlines():
        stripped = raw.strip()
        if not stripped:
            continue
        label = re.fullmatch(r"(\.L\w+):", stripped)
        if label:
            out.append(Insn("", label=label.group(1)))
            continue
        match = re.match(
            r"^/\*\s*[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})\s+[0-9A-Fa-f]{8}\s*\*/\s+(\S+)(?:\s+(.*))?$",
            stripped,
        )
        if match:
            addr, op, rest = (
                int(match.group(1), 16),
                match.group(2),
                match.group(3) or "",
            )
        else:
            if stripped.startswith(
                (".include", ".set", ".section", "glabel", "endlabel")
            ):
                continue
            parts = re.split(r"\s+", stripped, maxsplit=1)
            addr, op = -1, parts[0]
            rest = parts[1] if len(parts) > 1 else ""
        rest = re.sub(r"/\*.*?\*/", "", rest).strip()
        out.append(
            Insn(
                op,
                tuple(
                    part.strip().lstrip("$") for part in rest.split(",") if part.strip()
                ),
                addr,
                "",
                stripped,
            )
        )
    return out


def _number(operand: str) -> int | None:
    match = NUMBER.fullmatch(operand.strip())
    return int(match.group(), 0) if match else None


def _memory(operand: str) -> tuple[int | None, str] | None:
    match = MEMORY.fullmatch(operand.strip())
    if not match:
        return None
    offset = match.group("offset").strip()
    number = _number(offset)
    return number, match.group("base").lstrip("$")


def _symbol(operand: str) -> str | None:
    match = re.match(r"%hi\((.*?)\)|%lo\((.*?)\)", operand.strip())
    if match:
        return (match.group(1) or match.group(2)).strip()
    stripped = operand.strip()
    if re.fullmatch(r"[A-Za-z_]\w*", stripped):
        return stripped
    return None


def _tactic(fact: str, row: str, write: str) -> str:
    """One hint line: the fact, the tactic row it maps to, and what to write."""
    return f'- {fact}: {write} (tactic: "{row}", {TACTIC})'


def _entry(ctx: Context, addr: int) -> str:
    """Name an address from ``tools/symbol.py at``, else the image's own rows."""
    if addr in ctx.at:
        return ctx.at[addr]
    best: symbols.Entry | None = None
    for image in (ctx.func.image, "exe/slus_004_22"):
        for entry in ctx.table.get(image, ()):
            if entry.addr == addr:
                return f"{entry.name} ({entry.type})" if entry.type else entry.name
            if entry.size and entry.addr <= addr < entry.addr + entry.size:
                if best is None or entry.addr > best.addr:
                    best = entry
    if best is not None:
        offset = addr - best.addr
        kind = f" ({best.type})" if best.type else ""
        return f"{best.name}+0x{offset:X}{kind}"
    return f"0x{addr:08X} (no named owner)"


def scratchpad(insns: list[Insn], ctx: Context) -> list[str]:
    """The scratchpad cell reads: how many base loads, and whether one survives a call."""
    cells: Counter[int] = Counter()
    bases: list[tuple[str, int, int]] = []
    for index, insn in enumerate(insns):
        for address in SCRATCH.findall(insn.text):
            value = int(address, 16)
            if insn.op == "lui":
                bases.append((insn.args[0], index, value))
            else:
                cells[value] += 1
    if not cells:
        return []
    found = []
    for address, uses in sorted(cells.items()):
        found.append(f"0x{address:08X} {_entry(ctx, address)} ({uses} use(s))")
    kept = []
    for reg, at, _ in bases:
        if reg not in SAVED:
            continue
        for index in range(at + 1, len(insns)):
            if insns[index].op == "jal":
                kept.append(f"{reg} spans a jal")
                break
            if any(
                insn.op == "lui" and insn.args and insn.args[0] == reg
                for insn in insns[at + 1 : index + 1]
            ):
                break
    base = (
        f"{len(bases)} lui 0x1F80 load(s); " + ", ".join(found)
        if bases
        else ", ".join(found)
    )
    if kept:
        base += "; " + "; ".join(kept) + " (assign it to a local after the call)"
    else:
        base += "; the base is reloaded before each access"
    return [
        _tactic(
            f"scratchpad: {base}",
            "lui 0x1F800044 and a load before every access",
            "name the cell (or assign it once to a local) and read it directly; do not cast a constant address",
        )
    ]


def narrow_arguments(insns: list[Insn], _ctx: Context) -> list[str]:
    """Masks on an argument: the parameter stays ``s32`` and the use casts."""
    found = []
    seen: set[tuple[str, int]] = set()
    for insn in insns:
        if insn.op == "andi" and len(insn.args) >= 3 and insn.args[1] in ARGUMENTS:
            mask = _number(insn.args[2])
            if mask in (0xFF, 0xFFFF) and (insn.args[1], mask) not in seen:
                seen.add((insn.args[1], mask))
                found.append(
                    f"argument {insn.args[1]} is masked 0x{mask:X} at {_at(insn)}"
                )
        if insn.op == "sll" and len(insn.args) >= 3 and insn.args[1] in ARGUMENTS:
            shift = _number(insn.args[2])
            if shift in (16, 24):
                found.append(
                    f"argument {insn.args[1]} is shifted {shift} bits at {_at(insn)}"
                )
    return [
        _tactic(
            f"narrow argument: {fact}",
            "andi a0, 0xff on an argument",
            "parameter s32 with a (u8)/(u16) cast or mask at the use",
        )
        for fact in found
    ]


def narrow_locals(insns: list[Insn], _ctx: Context) -> list[str]:
    """A mask after an update: the local is one of the narrow integer types."""
    found = []
    for index, insn in enumerate(insns):
        if insn.op != "andi" or len(insn.args) < 3 or insn.args[1] in ARGUMENTS:
            continue
        mask = _number(insn.args[2])
        if mask not in (0xFF, 0xFFFF):
            continue
        before = insns[max(0, index - 8) : index]
        if not any(other.args and other.args[0] == insn.args[1] for other in before):
            continue
        found.append(
            f"local {insn.args[1]} is masked 0x{mask:X} after an update at {_at(insn)}"
        )
    return [
        _tactic(
            f"narrow local: {fact}",
            "an andi mask after a counter update",
            "declare the local u8/u16 (or mask the value); plain char is unsigned",
        )
        for fact in found
    ]


def jump_table(insns: list[Insn], ctx: Context) -> list[str]:
    """A ``jr`` through a ``jtbl_``: a switch, and whether Splat places the table."""
    found = []
    for insn in insns:
        if insn.op != "jr" or not insn.args or insn.args[0] == "ra":
            continue
        table = next(
            (
                symbol
                for symbol in (_symbol(part) for other in insns for part in other.args)
                if symbol and symbol.startswith(("jtbl_", "jpt_"))
            ),
            None,
        )
        if table is None:
            continue
        placed = table in ctx.splat
        if not placed and re.fullmatch(r"jtbl_[0-9A-Fa-f]{8}", table):
            placed = f"0x{int(table[5:], 16):X}" in ctx.splat
        found.append(
            f"jr through {table} at {_at(insn)}; a switch, table placed in splat.yaml: "
            f"{'yes' if placed else 'no'}"
        )
        break
    return [
        _tactic(
            f"jump table: {fact}",
            "a beq chain on a state byte",
            "write a switch with dense small cases",
        )
        for fact in found
    ]


def twice(insns: list[Insn], _ctx: Context) -> list[str]:
    """The same callee called twice: write the call twice, do not cache a result."""
    calls = Counter(insn.args[0] for insn in insns if insn.op == "jal" and insn.args)
    found = []
    for name, count in calls.items():
        if count < 2:
            continue
        setups = []
        for index, insn in enumerate(insns):
            if insn.op != "jal" or not insn.args or insn.args[0] != name:
                continue
            start = index - 1
            while start >= 0 and insns[start].op != "jal":
                start -= 1
            setups.append(
                tuple(
                    other.text
                    for other in insns[start + 1 : index]
                    if other.args and other.args[0] in ARGUMENTS
                )
            )
        if len(set(setups)) != 1:
            continue
        found.append(f"{name} is called {count} times with the same argument setup")
    return [
        _tactic(
            f"repeated call: {fact}",
            "two jals with the same arguments",
            "write the call twice, no cached local",
        )
        for fact in found
    ]


def rodata_copy(insns: list[Insn], _ctx: Context) -> list[str]:
    """Words copied into the stack before a ``jalr``: a handler-table copy."""
    found = []
    for index, insn in enumerate(insns):
        if insn.op != "jalr":
            continue
        stores = []
        for other in insns[max(0, index - 12) : index]:
            slot = _memory(other.args[-1]) if other.op == "sw" and other.args else None
            if slot is not None and slot[1] == "sp":
                stores.append(other)
        if len(stores) >= 4:
            found.append(
                f"{len(stores)} words stored to the stack before jalr at {_at(insn)}"
            )
    return [
        _tactic(
            f"stack copy: {fact}",
            "N words copied from rodata to the stack, then jalr",
            "copy the table into a stack local (memcpy or a struct assignment), then dispatch through it",
        )
        for fact in found
    ]


def frame(insns: list[Insn], _ctx: Context) -> list[str]:
    """Frame size, saved registers and stack locals, the three most logged miss causes."""
    size = None
    saves: list[str] = []
    save_slots: set[int] = set()
    for insn in insns[:20]:
        if insn.op == "addiu" and len(insn.args) >= 3:
            if insn.args[0] == insn.args[1] == "sp":
                value = _number(insn.args[2])
                if value is not None and value < 0:
                    size = -value
        if insn.op == "sw" and len(insn.args) >= 2:
            slot = _memory(insn.args[1])
            if slot and slot[1] == "sp":
                reg = insn.args[0]
                if reg in SAVED or reg in ("ra", "fp"):
                    saves.append(reg)
                    if slot[0] is not None:
                        save_slots.add(slot[0])
    if size is None:
        return [
            "- frame 0, saves none, 0 stack words: a leaf function; declare no locals."
        ]
    slots = {
        slot[0]
        for insn in insns
        if insn.op in ("sw", "lw")
        for slot in (_memory(insn.args[-1]),)
        if slot and slot[1] == "sp" and slot[0] is not None
    }
    slots = sorted(slot for slot in slots if slot not in save_slots and slot >= 0x10)
    saved = _saves(saves)
    return [
        f"- frame 0x{size:X}, saves {saved}, {len(slots)} stack slot(s): "
        "the draft's locals and frame follow from this shape."
    ]


def addresses(insns: list[Insn], ctx: Context) -> list[str]:
    """Every address the assembly reads, resolved through ``config/symbols.toml``."""
    found: dict[int, str] = {}
    pending: dict[str, int] = {}
    for insn in insns:
        if insn.op == "lui" and len(insn.args) >= 2:
            target = (insn.args[0], _number(insn.args[1]))
            if target[1] is not None and 0x8000 <= target[1] <= 0xFFFF:
                pending[insn.args[0]] = target[1] << 16
            symbol = _symbol(insn.args[1])
            if symbol and re.search(r"^(D_|g_|jtbl_|s_)", symbol):
                address = _symbol_address(ctx, symbol)
                if address is not None and not SCRATCH.fullmatch(f"0x{address:08X}"):
                    found.setdefault(address, "")
        if insn.op in ("addiu", "lw", "sw", "lhu", "lh", "lbu", "lb"):
            symbol = next((_symbol(part) for part in insn.args if _symbol(part)), None)
            if symbol and re.search(r"^(D_|g_|jtbl_|s_)", symbol):
                address = _symbol_address(ctx, symbol)
                if address is not None and not SCRATCH.fullmatch(f"0x{address:08X}"):
                    found.setdefault(address, "")
        if (
            insn.op in ("addiu", "lw", "sw", "lhu", "lh", "lbu", "lb")
            and len(insn.args) >= 2
        ):
            base = insn.args[1]
            number = _number(insn.args[2]) if len(insn.args) >= 3 else None
            if base in pending and number is not None:
                address = pending[base] + number
                if not SCRATCH.fullmatch(f"0x{address:08X}"):
                    found.setdefault(address, "")
    if not found:
        return []
    lines = [
        f"- address 0x{address:08X} -> {_entry(ctx, address)}"
        for address in sorted(found)[:12]
    ]
    if len(found) > 12:
        lines.append(f"- {len(found) - 12} more address(es), see the assembly")
    return lines


def twin(ctx: Context) -> list[str]:
    """The closest matched body and whether it lives in a shared header."""
    if not ctx.ranked:
        return []
    score, closest = ctx.ranked[0]
    path = closest.src or ""
    headers = sorted(ctx.root.glob(f"src/**/{closest.name}.h"))
    if headers:
        body = f"shared body {headers[0].relative_to(ctx.root)}"
    elif path.endswith(".h"):
        body = f"shared body {path}"
    else:
        body = f"body in {path}, not shared"
    return [
        f"- closest twin {closest.ref} {closest.name} ({score:.3f}), {body}: "
        "read the twin first; share its body if it matches."
    ]


def _saves(regs: list[str]) -> str:
    """Return ``s0-s2 ra``, or each saved register when the s range has a gap."""
    numbers = sorted({int(reg[1:]) for reg in regs if re.fullmatch(r"s\d", reg)})
    names = [f"s{number}" for number in numbers]
    parts = []
    if names:
        start = previous = numbers[0]
        for number in numbers[1:] + [None]:
            if number is not None and number == previous + 1:
                previous = number
                continue
            parts.append(f"s{start}" if start == previous else f"s{start}-s{previous}")
            if number is not None:
                start = previous = number
    if "ra" in regs:
        parts.append("ra")
    if "fp" in regs:
        parts.append("fp")
    return " ".join(parts) if parts else "none"


def _at(insn: Insn) -> str:
    return f"+0x{insn.addr:X}" if insn.addr >= 0 else "in the body"


def _symbol_address(ctx: Context, name: str) -> int | None:
    match = re.fullmatch(r"(?:[A-Z][A-Z0-9]*_)*(?:D|jtbl)_([0-9A-Fa-f]{8})", name)
    if match:
        return int(match.group(1), 16)
    for image in (ctx.func.image, "exe/slus_004_22"):
        for entry in ctx.table.get(image, ()):
            if entry.name == name:
                return entry.addr
    return None


def _addresses(insns: list[Insn], ctx: Context) -> set[int]:
    """The addresses the detectors can name."""
    found = {int(text, 16) for insn in insns for text in SCRATCH.findall(insn.text)}
    pending: dict[str, int] = {}
    for insn in insns:
        if insn.op == "lui" and len(insn.args) >= 2:
            value = _number(insn.args[1])
            if value is not None and 0x8000 <= value <= 0xFFFF:
                pending[insn.args[0]] = value << 16
            symbol = _symbol(insn.args[1])
            if symbol:
                address = _symbol_address(ctx, symbol)
                if address is not None:
                    found.add(address)
        if len(insn.args) >= 3 and insn.args[1] in pending:
            value = _number(insn.args[2])
            if value is not None:
                found.add(pending[insn.args[1]] + value)
        for arg in insn.args:
            symbol = _symbol(arg)
            if symbol and re.search(r"^(D_|g_|jtbl_|s_)", symbol):
                address = _symbol_address(ctx, symbol)
                if address is not None:
                    found.add(address)
    return found


def _at_strings(root: Path, image: str, addresses: set[int]) -> dict[int, str]:
    """Return ``tools/symbol.py at``'s owner line for each address."""
    if not addresses:
        return {}
    try:
        import symbol
    except ImportError:
        return {}
    args = argparse.Namespace(
        diff=None, image=image, addresses=[f"0x{address:08X}" for address in addresses]
    )
    buffer = io.StringIO()
    try:
        with contextlib.redirect_stdout(buffer):
            symbol.at(args)
    except (SystemExit, Exception):
        return {}
    found = {}
    for line in buffer.getvalue().splitlines():
        match = re.match(r"0x([0-9A-Fa-f]+)\s+(.*?)\s+\(([^)]*)\)\s+\[", line)
        if match:
            path = re.sub(r"\+0x0$", "", match.group(2))
            kind = match.group(3)
            found[int(match.group(1), 16)] = (
                f"{path} ({kind})" if kind != "untyped" else path
            )
            continue
        match = re.match(r"0x([0-9A-Fa-f]+)\s+no named owner", line)
        if match:
            address = int(match.group(1), 16)
            found[address] = f"0x{address:08X} (no named owner)"
    return found


def build(
    root: Path,
    func: Func,
    asm_text: str,
    ranked: tuple[tuple[float, Func], ...] = (),
) -> str:
    """Return ``hints.md`` for one function: each fact and the tactic row it maps to."""
    table = symbols.load(root)
    splat = (root / "config" / func.image / "splat.yaml").read_text(encoding="utf-8")
    ctx = Context(root, func, table, splat, tuple(ranked))
    insns = parse(asm_text)
    ctx.at = _at_strings(root, func.image, _addresses(insns, ctx))
    lines = [f"# Hints for {func.ref} {func.name}", ""]
    for detector in (
        scratchpad,
        narrow_arguments,
        narrow_locals,
        jump_table,
        twice,
        rodata_copy,
        addresses,
        frame,
    ):
        lines += detector(insns, ctx)
    lines += twin(ctx)
    if len(lines) == 2:
        lines.append("- no assembly pattern matched; draft from the tactics table.")
    return "\n".join(lines) + "\n"
