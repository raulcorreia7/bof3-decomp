#!/usr/bin/env python3
"""Measure the shapes of the assembly functions and write typed C bodies for the mechanical ones.

    tools/gen_body.py shapes [-o FILE]          count every INCLUDE_ASM function by shape
    tools/gen_body.py show TARGET@NAME          print the lifted events of one function
    tools/gen_body.py SHAPE [ROWS.tsv] [--dry-run]
                                                write a body for each member of SHAPE (or for the
                                                TARGET@NAME rows of ROWS.tsv), keep the exact ones

Shapes (`shapes` prints the counts):

    call-seq     straight-line calls whose arguments are constants or symbol addresses, with
                 constant stores to named globals between them
    store-seq    no call; constant stores to named globals only
    spad         straight-line code through the work pointer at 0x1F800044, no branch
    dispatch     one table call through `jalr`
    straight     other branch-free code
    branch       everything else

A generated body is a lead only when `tools/match.sh` reports an exact result: the tool keeps exact
bodies in the tree and restores the file for every other result. Run `check-<image>` and give the
body its name and shared-body treatment (docs/conventions.md) afterwards. The tool reads the
function index of the built images (`build/func_index.json.gz`) and `asm/<target>/<name>.s`.
"""

from __future__ import annotations

import argparse
import collections
import os
import re
import subprocess
import sys
from dataclasses import dataclass, field
from pathlib import Path

from bof3.source.index import Func, find, load_index

ROOT = Path(__file__).resolve().parent.parent
SHAPES = ("call-seq", "store-seq", "spad", "dispatch", "straight", "branch")
SPAD = "0x1F800044"
ARGS = ("a0", "a1", "a2", "a3")
CLOBBER = (
    "v0",
    "v1",
    "a0",
    "a1",
    "a2",
    "a3",
    "t0",
    "t1",
    "t2",
    "t3",
    "t4",
    "t5",
    "t6",
    "t7",
    "t8",
    "t9",
    "at",
)

INSN = re.compile(r"^\s*/\*[^*]*\*/\s*(\S.*)$")
HI = re.compile(r"^%hi\((\w+)\)$|^\((0x[0-9A-Fa-f]+) >> 16\)$")
LO = re.compile(r"^%lo\((\w+)\)$|^\((0x[0-9A-Fa-f]+) & 0xFFFF\)$")
BRANCH = {
    "beq",
    "bne",
    "beqz",
    "bnez",
    "blez",
    "bgtz",
    "bltz",
    "bgez",
    "b",
    "j",
    "bltzal",
    "bgezal",
}
STORE = {"sb": "u8", "sh": "u16", "sw": "u32"}


@dataclass
class Lift:
    """What one function does, in program order.

    ``events`` are ``("call", name, args, id)`` and ``("store", width, target, value)``. A target
    is ``("g", symbol)``, ``("gi", symbol, index)`` (a table element) or ``("m", offset)`` (a member
    of the work pointer's pointee). Values and arguments are expressions: ``("c", n)``,
    ``("sym", name)``, ``("g", symbol, width, signed)``, ``("gi", symbol, index, width, signed)``,
    ``("m", offset, width, signed)``, ``("add", expr, n)``, ``("bin", op, expr, expr or n)``,
    ``("arg", reg)`` and ``("ret", call id)`` (the value a call returned). A call carries its
    arguments in order, the fifth on from the stack. ``flags`` holds ``branch``, ``jalr``,
    ``spad``, ``load`` and ``other`` (an instruction the lifter cannot express).
    """

    events: list[tuple] = field(default_factory=list)
    flags: set[str] = field(default_factory=set)
    ret: tuple | None = None  # the constant left in v0 at the return
    why: list[str] = field(default_factory=list)  # the instructions that set ``other``


def instructions(text: str) -> list[str]:
    """Return the instruction lines of one assembly file, labels as ``.L...:`` lines."""
    out = []
    for line in text.splitlines():
        m = INSN.match(line)
        if m:
            out.append(re.sub(r"\s+", " ", m.group(1).strip()))
        elif re.match(r"^\s*\.L\w+:", line):
            out.append(line.strip())
    return out


def symbol(operand: str, pattern: re.Pattern) -> str | None:
    """Return the symbol or address named by a ``%hi``/``%lo`` style operand."""
    m = pattern.match(operand)
    return (m.group(1) or m.group(2)) if m else None


VALUE = ("c", "g", "m", "add", "bin", "ret", "gi")
ALU_IMM = {
    "andi": "&",
    "sll": "<<",
    "srl": ">>",
    "sra": ">>",
    "ori": "|",
    "xori": "^",
}
ALU_REG = {"addu": "+", "subu": "-", "or": "|", "and": "&", "xor": "^"}
LOAD = {
    "lw": (4, True),
    "lh": (2, True),
    "lhu": (2, False),
    "lb": (1, True),
    "lbu": (1, False),
}


def address(regs: dict, operand: str):
    """Resolve ``off(base)`` to ``("g", symbol)``, ``("m", offset)`` or None."""
    m = re.match(r"(.+)\(\$(\w+)\)$", operand)
    if not m:
        return None
    base, off = regs.get(m.group(2)), m.group(1)
    sym = symbol(off, LO)
    if sym and base == ("hi", sym):
        return ("spadcell",) if sym == SPAD else ("g", sym)
    if sym and base and base[0] == "hiidx" and base[1] == sym:
        return ("gi", sym, base[2])
    if base == ("spad",) and re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)", off):
        return ("m", int(off, 0))
    return None


def halve(op: str, src: tuple, n: int) -> tuple:
    """Return the ALU expression; ``x + (x >>u 31)`` shifted right by n reads as ``x / 2^n``."""
    if op == "sra" and src[:2] == ("bin", "+") and src[3] == ("bin", ">>", src[2], 31):
        return ("bin", "/", src[2], 1 << n)
    return ("bin", ALU_IMM[op], src, n)


def lift(lines: list[str]) -> Lift:
    """Run the instructions through a symbolic register file."""
    out, regs, pending, v0_at = Lift(), {}, None, -1
    stack: dict[int, tuple] = {}
    for line in lines:
        if line.endswith(":"):
            out.flags.add("branch")
            continue
        op, _, rest = line.partition(" ")
        o = [x.strip().lstrip("$") for x in rest.split(",")] if rest else []
        if op in ("nop", ".word"):
            pass
        elif op in BRANCH or op == "jr" and o != ["ra"]:
            out.flags.add("branch")
        elif op == "jalr":
            out.flags.add("jalr")
        elif op == "jr":
            if "v0" in regs and v0_at == len(out.events) and regs["v0"][0] == "c":
                out.ret = regs["v0"]
        elif op == "jal":
            pending = o[0]
            continue
        elif op == "lui" and symbol(o[1], HI):
            regs[o[0]] = ("hi", symbol(o[1], HI))
        elif op in ("addiu", "ori") and symbol(o[2], LO):
            sym = symbol(o[2], LO)
            if regs.get(o[1]) == ("hi", sym):
                regs[o[0]] = (
                    ("c", int(sym, 0)) if sym.startswith("0x") else ("sym", sym)
                )
            else:
                out.flags.add("other")
                out.why.append(line)
                regs[o[0]] = ("unk",)
        elif op in ("addiu", "ori") and o[1] == "zero":
            regs[o[0]] = ("c", int(o[2], 0))
        elif op == "addiu" and o[0] == o[1] == "sp":
            pass
        elif (
            op == "addiu"
            and o[1] != "sp"
            and regs.get(o[1], ("unk",))[0] in ("c", "g", "m")
        ):
            regs[o[0]] = ("add", regs[o[1]], int(o[2], 0))
        elif (
            op in ALU_IMM
            and regs.get(o[1], ("unk",))[0] in VALUE
            and re.fullmatch(r"-?(0x[0-9A-Fa-f]+|\d+)", o[2])
        ):
            regs[o[0]] = halve(op, regs[o[1]], int(o[2], 0))
        elif (
            op == "addu"
            and regs.get(o[1], ("",))[0] == "hi"
            and o[0] == o[1]
            and regs.get(o[2], ("unk",))[0] in VALUE
        ):
            regs[o[0]] = ("hiidx", regs[o[1]][1], regs[o[2]])
        elif (
            op in ALU_REG
            and regs.get(o[1], ("unk",))[0] in VALUE
            and regs.get(o[2], ("unk",))[0] in VALUE
        ):
            regs[o[0]] = ("bin", ALU_REG[op], regs[o[1]], regs[o[2]])
        elif op == "addu" and o[1] == "zero" and o[2] == "zero":
            regs[o[0]] = ("c", 0)
        elif op == "addu" and o[2] == "zero":
            regs[o[0]] = regs.get(o[1], ("arg", o[1]))
        elif (
            op in ("sw", "lw")
            and o[1].endswith("($sp)")
            and (o[0] == "ra" or o[0][0] == "s")
        ):
            pass
        elif op == "sw" and (m := re.fullmatch(r"(0x[0-9A-Fa-f]+|\d+)\(\$sp\)", o[1])):
            # An argument beyond the fourth, stored for the next call.
            val = ("c", 0) if o[0] == "zero" else regs.get(o[0], ("arg", o[0]))
            if val[0] == "unk" or int(m.group(1), 0) < 0x10:
                out.flags.add("other")
                out.why.append(line)
            else:
                stack[int(m.group(1), 0)] = val
        elif op in STORE:
            target = address(regs, o[1])
            val = ("c", 0) if o[0] == "zero" else regs.get(o[0], ("arg", o[0]))
            if target and target[0] in ("g", "m", "gi") and val[0] != "unk":
                out.events.append(("store", STORE[op], target, val))
                if target[0] == "m":
                    out.flags.add("spad")
            else:
                out.flags.add("other")
                out.why.append(line)
        elif op in LOAD:
            width, signed = LOAD[op]
            target = address(regs, o[1])
            out.flags.add("load")
            if target and target[0] == "spadcell":
                regs[o[0]] = ("spad",)
            elif target and target[0] == "gi":
                regs[o[0]] = ("gi", target[1], target[2], width, signed)
            elif target and target[0] in ("g", "m"):
                regs[o[0]] = (target[0], target[1], width, signed)
                if target[0] == "m":
                    out.flags.add("spad")
            else:
                out.flags.add("other")
                out.why.append(line)
                regs[o[0]] = ("unk",)
        else:
            out.flags.add("other")
            out.why.append(line)
            if o:
                regs[o[0]] = ("unk",)
        if o and o[0] == "v0" and op not in STORE and op != "jr":
            v0_at = len(out.events)
        if pending and op != "jal":
            # The delay slot ran before the call, so the arguments are final now.
            args = tuple(regs.get(r, ("arg", r)) for r in ARGS)
            if stack:
                if sorted(stack) != list(range(0x10, 0x10 + 4 * len(stack), 4)):
                    out.flags.add("other")
                    out.why.append("sw: stack arguments with a gap")
                args += tuple(stack[k] for k in sorted(stack))
                stack = {}
            calls = sum(e[0] == "call" for e in out.events)
            out.events.append(("call", pending, args, calls))
            for r in CLOBBER:
                regs.pop(r, None)
            regs["v0"] = ("ret", calls)
            pending = None
    return out


def classify(lifted: Lift) -> str:
    """Return the shape name of a lifted function."""
    f = lifted.flags
    if "jalr" in f:
        return "dispatch"
    if "branch" in f:
        return "branch"
    calls = any(e[0] == "call" for e in lifted.events)
    if "spad" in f:
        return "spad"
    if "other" in f or "load" in f:
        return "straight"
    if calls:
        return "call-seq"
    return "store-seq" if lifted.events else "straight"


def asm_functions(root: Path = ROOT) -> list[Func]:
    """Return the functions that are still assembly."""
    return [f for f in load_index(root) if f.status == "ASM"]


def lifted_function(f: Func, root: Path = ROOT) -> Lift:
    """Lift one assembly function from its ``asm/`` file."""
    path = root / "asm" / f.image / f"{f.name}.s"
    return lift(instructions(path.read_text(encoding="utf-8")))


def measure(funcs: list[Func]) -> list[tuple[str, Func, int]]:
    """Return ``(shape, function, words)`` for each function."""
    return [(classify(lifted_function(f)), f, len(f.words)) for f in funcs]


class Tree:
    """The headers of the C tree: member tables of work structs, declared names and arrays."""

    VIEW = re.compile(
        r"#\s*define\s+g_SpadWork\s+\(\((?:volatile\s+)?(\w+)\s*\*\)\s*g_SpadWork\)"
    )
    INCLUDE = re.compile(r'^\s*#\s*include\s+"([^"]+)"', re.M)
    SCALAR = {
        "u8": 1,
        "s8": 1,
        "char": 1,
        "u16": 2,
        "s16": 2,
        "u32": 4,
        "s32": 4,
        "int": 4,
    }

    def __init__(self, root: Path = ROOT) -> None:
        self.root = root
        self.text: dict[str, str] = {}

    def read(self, name: str) -> str:
        if name not in self.text:
            path = self.root / name
            self.text[name] = (
                path.read_text(encoding="utf-8", errors="replace")
                if path.is_file()
                else ""
            )
        return self.text[name]

    def closure(self, src: str) -> list[str]:
        """Return ``src`` and the in-tree files it includes, transitively."""
        seen, todo = [], [src]
        while todo:
            name = todo.pop(0)
            if name in seen or not self.read(name):
                continue
            seen.append(name)
            for inc in self.INCLUDE.findall(self.read(name)):
                for base in (str(Path(name).parent), "src/shared", "src", "include"):
                    cand = (Path(base) / inc).as_posix()
                    if (self.root / cand).is_file():
                        todo.append(cand)
                        break
        return seen

    def work_type(self, files: list[str]) -> str | None:
        for name in files:
            m = self.VIEW.search(self.read(name))
            if m:
                return m.group(1)
        return None

    def members(self, type_name: str, files: list[str]) -> dict[int, tuple[str, int]]:
        """Return ``{offset: (member, width)}`` of a struct whose members carry their offset."""
        for name in files + [n for n in tracked_headers(self.root) if n not in files]:
            m = re.search(
                r"typedef struct \w*\s*\{(.*?)\}\s*" + type_name + r"\s*;",
                self.read(name),
                re.S,
            )
            if m:
                return self.parse(m.group(1), files)
        return {}

    def parse(self, body: str, files: list[str]) -> dict[int, tuple[str, int]]:
        out = {}
        for line in body.splitlines():
            m = re.match(r"\s*(\w+)\s+(\w+)\s*;\s*(?:/\*\s*\+?(0x[0-9A-Fa-f]+))?", line)
            if not m:
                continue
            typ, name, note = m.groups()
            width = self.SCALAR.get(typ) or self.alias(typ, files)
            off = re.search(r"_([0-9A-F]{2})$", name)
            where = int(note, 16) if note else int(off.group(1), 16) if off else None
            if width and where is not None:
                out[where] = (name, width)
        return out

    def alias(self, typ: str, files: list[str]) -> int | None:
        for name in files + tracked_headers(self.root):
            m = re.search(
                r"typedef\s+(u8|s8|u16|s16|u32|s32)\s+" + typ + r"\s*;", self.read(name)
            )
            if m:
                return self.SCALAR[m.group(1)]
        return None

    def count(self, text: str) -> int | None:
        """Return an array length written as a number or as a ``#define`` of one."""
        if re.fullmatch(r"0x[0-9A-Fa-f]+|\d+", text):
            return int(text, 0)
        for name in tracked_headers(self.root):
            m = re.search(
                r"^\s*#\s*define\s+" + re.escape(text) + r"\s+(0x[0-9A-Fa-f]+|\d+)\b",
                self.read(name),
                re.M,
            )
            if m:
                return int(m.group(1), 0)
        return None

    def layout(
        self, type_name: str, files: list[str]
    ) -> tuple[int, list[tuple[int, str, int, int]]] | None:
        """Return ``(size, [(offset, member, width, count)])`` of a struct of scalars and scalar arrays."""
        for name in files + [n for n in tracked_headers(self.root) if n not in files]:
            m = re.search(
                r"typedef struct \w*\s*\{(.*?)\}\s*" + type_name + r"\s*;",
                self.read(name),
                re.S,
            )
            if not m:
                continue
            body = re.sub(r"/\*.*?\*/|//[^\n]*", "", m.group(1), flags=re.S)
            off, rows, biggest = 0, [], 1
            for decl in filter(None, (x.strip() for x in body.split(";"))):
                d = re.fullmatch(r"(\w+)\s+(\w+)\s*(?:\[(\w+)\])?", decl)
                width = d and (
                    self.SCALAR.get(d.group(1)) or self.alias(d.group(1), files)
                )
                n = 1 if not d or not d.group(3) else self.count(d.group(3))
                if not d or not width or not n:
                    return None
                off = -(-off // width) * width
                rows.append((off, d.group(2), width, n))
                off += width * n
                biggest = max(biggest, width)
            return -(-off // biggest) * biggest, rows
        return None

    def declared(self, files: list[str], name: str) -> str | None:
        """Return ``array``, ``func`` or ``object`` when a header of ``files`` declares ``name``."""
        for f in files:
            if not f.endswith(".h"):
                continue
            m = re.search(
                r"^[^\n#()=]*\b" + re.escape(name) + r"\b\s*(\[|\(|;)",
                self.read(f),
                re.M,
            )
            if m:
                return {"[": "array", "(": "func"}.get(m.group(1), "object")
        return None


_HEADERS: list[str] = []


def tracked_headers(root: Path) -> list[str]:
    if not _HEADERS:
        from bof3.source.ctext import tracked

        _HEADERS.extend(n for n in tracked(root) if n.endswith(".h"))
    return _HEADERS


class Names:
    """Game names from ``config/symbols.toml``: the asm still says ``func_<ADDR>`` for renamed symbols."""

    ADDRESS = re.compile(r"^(?:func|D|jtbl)_([0-9A-F]{8})$")

    def __init__(self, root: Path = ROOT) -> None:
        import tomllib

        table = tomllib.loads(
            (root / "config/symbols.toml").read_text(encoding="utf-8")
        )
        self.by_image: dict[str, dict[int, str]] = {}
        self.spans: dict[str, list[tuple[int, int, str]]] = {}
        for image, rows in table.items():
            self.spans[image] = sorted(
                (r["addr"], r["size"], n)
                for n, r in rows.items()
                if "addr" in r and r.get("size")
            )
            self.by_image[image] = {
                r["addr"]: n
                for n, r in rows.items()
                if not r.get("alias") and "addr" in r
            }

    def of(self, image: str, name: str) -> str:
        """Return the game name of an address-named symbol, or ``name`` itself."""
        m = self.ADDRESS.match(name)
        if not m:
            return name
        addr = int(m.group(1), 16)
        for table in (image, "exe/slus_004_22"):
            if addr in self.by_image.get(table, {}):
                return self.by_image[table][addr]
        found = {t[addr] for t in self.by_image.values() if addr in t}
        return found.pop() if len(found) == 1 else name

    def container(self, image: str, addr: int) -> tuple[int, int, str] | None:
        """Return the sized symbol that holds ``addr`` strictly inside it."""
        for table in (image, "exe/slus_004_22"):
            for base, size, name in self.spans.get(table, []):
                if base < addr < base + size:
                    return base, size, name
        return None


def rename(e, names: Names, image: str):
    """Return the expression or event with every symbol replaced by its game name."""
    if not isinstance(e, tuple) or not e:
        return e
    if e[0] in ("sym", "g") and isinstance(e[1], str):
        return (e[0], names.of(image, e[1]), *e[2:])
    if e[0] == "gi":
        return ("gi", names.of(image, e[1]), rename(e[2], names, image), *e[3:])
    if e[0] == "call":
        return (
            "call",
            names.of(image, e[1]),
            tuple(rename(a, names, image) for a in e[2]),
            e[3],
        )
    return tuple(rename(x, names, image) if isinstance(x, tuple) else x for x in e)


class Unsupported(Exception):
    """The body cannot be written from what the lifter knows."""


def number(n: int) -> str:
    return str(n) if -0x10000 < n < 0x10000 else f"0x{n & 0xFFFFFFFF:X}"


def render(e: tuple, ctx: dict) -> str:
    """Write one expression as C."""
    kind = e[0]
    if kind == "c":
        return number(e[1])
    if kind == "sym":
        return (
            e[1]
            if ctx["tree"].declared(ctx["files"], e[1]) in ("array", "func")
            or e[1].startswith("func_")
            else "&" + e[1]
        )
    if kind == "g":
        return global_text(e[1], ctx, e[2])
    if kind == "m":
        return member(e[1], e[2], ctx)
    if kind == "ret":
        return ctx.get("inline", {}).get(e[1], f"r{e[1]}")
    if kind == "gi":
        return element(e[1], e[2], e[3], ctx)
    if kind == "add":
        return (
            f"{render(e[1], ctx)} + {e[2]}"
            if e[2] >= 0
            else f"{render(e[1], ctx)} - {-e[2]}"
        )
    if kind == "bin":
        left, right = e[2], e[3] if isinstance(e[3], tuple) else ("c", e[3])
        text = [render(x, ctx) for x in (left, right)]
        text = [
            f"({t})" if x[0] in ("add", "bin") else t
            for t, x in zip(text, (left, right), strict=True)
        ]
        return f"{text[0]} {e[1]} {text[1]}"
    raise Unsupported(f"expression {kind}")


def global_text(name: str, ctx: dict, width: int) -> str:
    """Write a global; one that sits inside a sized array of scalars is an element of it."""
    m = re.fullmatch(r"D_([0-9A-F]{8})", name)
    found = (
        m and ctx["names"] and ctx["names"].container(ctx["image"], int(m.group(1), 16))
    )
    if found:
        base, _, holder = found
        decl = re.compile(r"\b(\w+)\s+" + re.escape(holder) + r"\s*\[")
        files, tree = ctx["files"], ctx["tree"]
        kind = next(
            (d.group(1) for f in files if (d := decl.search(tree.read(f)))), None
        )
        if kind and (tree.SCALAR.get(kind) or tree.alias(kind, files)) == width:
            rel = int(m.group(1), 16) - base
            if rel % width == 0:
                return f"{holder}[{rel // width}]"
    return name + "[0]" if ctx["tree"].declared(ctx["files"], name) == "array" else name


def linear(e: tuple) -> tuple[int, tuple]:
    """Return ``(k, x)`` when ``e`` is ``k * x`` built from shifts, sums and differences of ``x``."""
    if e[0] == "bin" and e[1] == "<<" and isinstance(e[3], int):
        k, x = linear(e[2])
        return k << e[3], x
    if e[0] == "bin" and e[1] in "+-" and isinstance(e[3], tuple):
        (k, x), (j, y) = linear(e[2]), linear(e[3])
        if x == y:
            return (k + j if e[1] == "+" else k - j), x
    return 1, e


def struct_element(name: str, index: tuple, width: int, ctx: dict) -> str | None:
    """Write ``Array[x].member`` for a table symbol that sits inside a sized array of structs."""
    m = re.fullmatch(r"D_([0-9A-F]{8})", name)
    found = m and ctx["names"].container(ctx["image"], int(m.group(1), 16))
    if not found:
        return None
    base, _, holder = found
    decl = re.compile(r"\b(\w+)\s+" + re.escape(holder) + r"\s*\[")
    kind = next(
        (d.group(1) for f in ctx["files"] if (d := decl.search(ctx["tree"].read(f)))),
        None,
    )
    lay = kind and ctx["tree"].layout(kind, ctx["files"])
    if not lay:
        raise Unsupported(
            f"{name} lies inside {holder}, which is not a typed struct array"
        )
    stride, rows = lay
    k, x = linear(index)
    rel = int(m.group(1), 16) - base
    if k != stride:
        raise Unsupported(f"index of {name} is not a stride of {holder}")
    for off, member_name, w, n in rows:
        if w == width and off <= rel < off + w * n and (rel - off) % w == 0:
            tail = f"[{(rel - off) // w}]" if n > 1 else ""
            return f"{holder}[{render(x, ctx)}].{member_name}{tail}"
    raise Unsupported(f"no {width}-byte member at 0x{rel:X} of {kind}")


def element(name: str, index: tuple, width: int, ctx: dict) -> str:
    """Write ``name[index]``; the register held the byte offset, so undo the scaling."""
    typed = struct_element(name, index, width, ctx)
    if typed:
        return typed
    if ctx["tree"].declared(ctx["files"], name) not in (None, "array"):
        raise Unsupported(f"{name} is declared as a scalar, not a table")
    shift = {1: 0, 2: 1, 4: 2}[width]
    if re.search(r"'bin', '[+-]'", str(index)):
        raise Unsupported(f"index of {name} is a stride of an untyped table")
    if shift and not (index[0] == "bin" and index[1] == "<<" and index[3] == shift):
        raise Unsupported(f"table index of {name} is not scaled by {width}")
    return f"{name}[{render(index[2] if shift else index, ctx)}]"


def member(offset: int, width: int, ctx: dict) -> str:
    row = ctx["members"].get(offset)
    if not row or row[1] != width:
        raise Unsupported(f"no {width}-byte member at 0x{offset:X}")
    return f"g_SpadWork->{row[0]}"


WIDTH = {"u8": 1, "u16": 2, "u32": 4}


def rets_used(events: list[tuple], inline: bool = False) -> set[int]:
    """Return the ids of the calls whose result an event reads.

    With ``inline`` the ones read once, by the next event, are left out: they need no local.
    """
    counts: collections.Counter = collections.Counter()
    first: dict[int, int] = {}
    for i, event in enumerate(events):
        stack = list(event[2] if event[0] == "call" else event[2:])
        while stack:
            e = stack.pop()
            if isinstance(e, tuple) and e:
                if e[0] == "ret":
                    counts[e[1]] += 1
                    first.setdefault(e[1], i)
                stack.extend(e[1:])
    found = set(counts)
    if inline:
        found -= {
            k
            for k, n in counts.items()
            if n == 1 and first[k] == call_at(events, k) + 1
        }
    return found


def call_at(events: list[tuple], ident: int) -> int:
    """Return the position of the call with this id."""
    return next(i for i, e in enumerate(events) if e[0] == "call" and e[3] == ident)


def statements(lifted: Lift, ctx: dict) -> list[str]:
    """Write the events of a straight-line function as C statements."""
    out, used = [], rets_used(lifted.events, inline=True)
    ctx = {**ctx, "inline": {}}
    for e in lifted.events:
        if e[0] == "call":
            args = []
            for i, a in enumerate(e[2]):
                if i < 4 and a == ("arg", ARGS[i]):
                    if any(b != ("arg", ARGS[j]) for j, b in enumerate(e[2]) if j > i):
                        raise Unsupported("argument registers skip one")
                    break
                args.append(render(a, ctx))
            call = f"{e[1]}({', '.join(args)});"
            if e[3] in used:
                out.append(f"r{e[3]} = {call}")
            elif e[3] in rets_used(lifted.events):
                ctx["inline"][e[3]] = call.removesuffix(";")
            else:
                out.append(call)
            continue
        _, kind, target, value = e
        left = (
            global_text(target[1], ctx, WIDTH[kind])
            if target[0] == "g"
            else element(target[1], target[2], WIDTH[kind], ctx)
            if target[0] == "gi"
            else member(target[1], WIDTH[kind], ctx)
        )
        if value[0] == "add" and value[1][0] == target[0] and value[1][1] == target[1]:
            step = value[2]
            out.append(
                f"{left}++;"
                if step == 1
                else f"{left}--;"
                if step == -1
                else f"{left} += {step};"
            )
        elif (
            value[0] == "bin"
            and value[1] in ("&", "|", "^", "<<", ">>")
            and isinstance(value[3], int)
            and render(value[2], ctx) == left
        ):
            out.append(f"{left} {value[1]}= {number(value[3])};")
        else:
            out.append(f"{left} = {render(value, ctx)};")
    return out


def names_used(event: tuple):
    """Yield ``(symbol, width)`` for each global an event touches."""
    stack = [event]
    while stack:
        e = stack.pop()
        if not isinstance(e, tuple) or not e:
            continue
        if e[0] == "g":
            yield e[1], e[2]
        elif e[0] == "gi":
            yield e[1] + "[]", e[3]
            stack.append(e[2])
        elif e[0] == "store":
            if e[2][0] == "g":
                yield e[2][1], WIDTH[e[1]]
            elif e[2][0] == "gi":
                yield e[2][1] + "[]", WIDTH[e[1]]
                stack.append(e[2][2])
            stack.append(e[3])
        elif e[0] == "call":
            stack.extend(e[2])
        elif e[0] == "add":
            stack.append(e[1])
        elif e[0] == "bin":
            stack.append(e[2])


def body_for(f: Func, tree: Tree, names: Names) -> tuple[str, list[tuple[str, int]]]:
    """Return the C definition and the globals it needs declared, or raise Unsupported."""
    if not f.src:
        raise Unsupported("no C file holds its INCLUDE_ASM")
    lifted = lifted_function(f)
    lifted.events = [rename(e, names, f.image) for e in lifted.events]
    if lifted.flags & {"branch", "jalr", "other"}:
        raise Unsupported(
            lifted.why[0] if "other" in lifted.flags else "not straight-line"
        )
    files = tree.closure(f.src)
    ctx = {
        "tree": tree,
        "files": files,
        "members": {},
        "names": names,
        "image": f.image,
    }
    if "spad" in lifted.flags:
        work = tree.work_type(files)
        if not work:
            raise Unsupported("no g_SpadWork view in this image")
        ctx["members"] = tree.members(work, files)
    lines = statements(lifted, ctx)
    externs = [
        (s, w)
        for e in lifted.events
        for s, w in names_used(e)
        if not tree.declared(files, s.removesuffix("[]"))
        and not names.container(
            f.image, int(s[2:10], 16) if re.match(r"D_[0-9A-F]{8}", s) else 0
        )
    ]
    kind = "void"
    if lifted.ret:
        kind = "s32"
        lines.append(f"return {render(lifted.ret, ctx)};")
    used = sorted(rets_used(lifted.events, inline=True))
    lines = [f"s32 r{i};" for i in used] + ([""] if used else []) + lines
    body = "\n".join(f"    {x}" if x else "" for x in lines)
    return f"MATCH {kind} {f.name}(void) {{\n{body}\n}}", externs


@dataclass
class Item:
    """One generated body for one assembly function."""

    func: Func
    body: str
    externs: list[tuple[str, int]]

    @property
    def text(self) -> str:
        """The body with its own name masked, to compare twins."""
        return self.body.replace(self.func.name, "@")

    @property
    def statements(self) -> int:
        return self.body.count(";\n")


def shared_header(items: list[Item]) -> str:
    """Return the path of the shared body of same-address twins, at the lowest folder holding all."""
    dirs = [str(Path(i.func.src).parent) for i in items]
    common = Path(os.path.commonpath(dirs)).as_posix()
    where = common if common.count("/") >= 2 else "src/shared"
    return f"{where}/{items[0].func.name}.h"


def restore(saved: dict[Path, str | None]) -> None:
    for path, text in saved.items():
        if text is None:
            path.unlink(missing_ok=True)
        else:
            path.write_text(text, encoding="utf-8")


def apply(items: list[Item], tree: Tree, shared: str | None) -> list[str]:
    """Write the bodies of one group, check each, keep all or none; return report lines."""
    saved: dict[Path, str | None] = {}

    def edit(path: Path, text: str) -> None:
        saved.setdefault(
            path, path.read_text(encoding="utf-8") if path.is_file() else None
        )
        path.write_text(text, encoding="utf-8")

    if shared:
        first = items[0]
        edit(
            ROOT / shared,
            "/* Straight-line sequence shared by the overlays that include it; every change must\n"
            " * verify every one of them. */\n" + first.body + "\n",
        )
    for item in items:
        f = item.func
        path, marker = ROOT / f.src, f"INCLUDE_ASM({f.name});"
        text = path.read_text(encoding="utf-8")
        if marker not in text:
            restore(saved)
            return [f"SKIP {f.ref} {f.name}: has a body"]
        header = ROOT / next((n for n in tree.closure(f.src) if n.endswith(".h")), "")
        if item.externs and header.is_file():
            old, types = (
                header.read_text(encoding="utf-8"),
                {1: "u8", 2: "u16", 4: "u32"},
            )
            decl = "".join(
                f"extern {types[w]} {s};\n" for s, w in dict(item.externs).items()
            )
            end = old.rindex("#endif")
            edit(header, old[:end] + decl + "\n" + old[end:])
            tree.text.pop(str(header.relative_to(ROOT)), None)
        include = f'#include "{shared.removeprefix("src/")}"' if shared else item.body
        edit(path, text.replace(marker, include))
    out = []
    for item in items:
        f = item.func
        result = subprocess.run(
            ["sh", "tools/match.sh", f.image, f.name],
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=False,
        )
        if result.returncode:
            restore(saved)
            tail = " | ".join(
                x.strip()
                for x in (result.stdout + result.stderr).strip().splitlines()[-2:]
            )
            return [f"FAIL {f.ref} {f.name}: {tail[:200]}"]
        out.append(f"EXACT {f.ref} {f.name} in {f.src}")
    return out


def run(rows: list[Func], tree: Tree, dry: bool) -> None:
    """Write each body, run match.sh, keep the exact ones and restore the rest.

    Twins with one body at one address share ``<func>.h``. Twins at several addresses need one
    game name first, so they are reported as ``TWIN`` and left alone.
    """
    names, items = Names(), []
    for f in rows:
        try:
            items.append(Item(f, *body_for(f, tree, names)))
        except Unsupported as why:
            print(f"SKIP {f.ref} {f.name}: {why}", flush=True)
    groups: dict[str, list[Item]] = collections.defaultdict(list)
    for item in items:
        groups[item.text].append(item)
    for group in groups.values():
        by_addr = collections.defaultdict(list)
        for item in group:
            by_addr[item.func.addr].append(item)
        shareable = group[0].statements > 1 and len(group) > 1
        if shareable and len(by_addr) > 1:
            for item in group:
                print(
                    f"TWIN {item.func.ref} {item.func.name}: needs one name for {len(group)} copies",
                    flush=True,
                )
            continue
        for twins in by_addr.values():
            share = shared_header(twins) if shareable and len(twins) > 1 else None
            if dry:
                print(
                    f"DRY {twins[0].func.ref} {len(twins)}x {share or ''}\n{twins[0].body}"
                )
                continue
            for line in apply(twins, tree, share):
                print(line, flush=True)


def cmd_run(args: argparse.Namespace) -> None:
    funcs = load_index(ROOT)
    if args.rows:
        lines = args.rows.read_text(encoding="utf-8").splitlines()
        picked = [find(funcs, r.split("\t")[0]) for r in lines if r.strip()]
    else:
        picked = [
            f
            for shape, f, _ in measure([x for x in funcs if x.status == "ASM"])
            if shape == args.shape
        ]
    run(sorted(picked, key=lambda f: (len(f.words), f.ref)), Tree(), args.dry_run)


def cmd_shapes(args: argparse.Namespace) -> None:
    rows = measure(asm_functions())
    counts = collections.Counter(shape for shape, _, _ in rows)
    lines = ["shape\timage\tfunction\twords"]
    for shape in SHAPES:
        ordered = sorted(
            (r for r in rows if r[0] == shape), key=lambda r: (r[2], r[1].ref)
        )
        lines += [f"{shape}\t{f.image}\t{f.name}\t{n}" for _, f, n in ordered]
    text = "\n".join(lines) + "\n"
    if args.out:
        Path(args.out).write_text(text, encoding="utf-8")
    else:
        sys.stdout.write(text)
    for shape in SHAPES:
        print(f"{shape}\t{counts[shape]}", file=sys.stderr)
    print(f"total\t{len(rows)}", file=sys.stderr)


def cmd_show(args: argparse.Namespace) -> None:
    f = find(load_index(ROOT), args.ref)
    lifted = lifted_function(f)
    print(classify(lifted), sorted(lifted.flags))
    for event in lifted.events:
        print(event)


def main() -> None:
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    sub = parser.add_subparsers(dest="verb", required=True)
    p = sub.add_parser("shapes")
    p.add_argument("-o", "--out")
    p.set_defaults(run=cmd_shapes)
    p = sub.add_parser("show")
    p.add_argument("ref")
    p.set_defaults(run=cmd_show)
    for shape in SHAPES:
        p = sub.add_parser(shape)
        p.add_argument(
            "rows",
            nargs="?",
            type=Path,
            help="TSV of TARGET@NAME rows (default: the whole shape)",
        )
        p.add_argument("--dry-run", action="store_true")
        p.set_defaults(run=cmd_run, shape=shape)
    args = parser.parse_args()
    args.run(args)


if __name__ == "__main__":
    main()
