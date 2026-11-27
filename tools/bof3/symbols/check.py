"""Check, add and annotate the symbol table rows."""

from __future__ import annotations

import collections
import re
import subprocess
import tempfile
from dataclasses import dataclass

from bof3.adapters.config import SPLIT, symbols_text, write_symbols
from bof3.errors import SymbolError
from bof3.link import symbols
from bof3.source import symtab
from bof3.symbols.context import Context, Table, grep_files


class UnknownImageError(SymbolError):
    """The image is not a folder under ``config/`` with a ``splat.yaml``."""


@dataclass(frozen=True)
class AddRequest:
    image: str
    name: str
    addr: str
    source: str | None
    type: str | None
    size: str | None


def add(ctx: Context, req: AddRequest) -> None:
    """Insert one row."""
    if not (ctx.root / "config" / req.image / "splat.yaml").is_file():
        raise UnknownImageError(
            f"symbol: no image {req.image}; "
            "use a folder id under config/ that holds a splat.yaml"
        )
    addr = int(req.addr, 16)
    row = symtab.format_row(
        req.name, addr, type=req.type, size=int(req.size, 0) if req.size else None,
        source=req.source,
    )  # fmt: skip
    text = symbols_text(ctx.root)
    write_symbols(ctx.root, symtab.add_row(text, req.image, req.name, row, addr))


def params(ctx: Context, func: str, pairs: list[str]) -> None:
    """Rename parameters in one function's unit file and its prototypes."""
    renames = [p.split("=", 1) for p in pairs]
    if any(len(p) != 2 or not p[0] or not p[1] for p in renames):
        raise SymbolError("symbol: write each rename as OLD=NEW")
    prototype = re.compile(r"\S[^=]*\b" + re.escape(func) + r"\s*\(.*\)\s*;")
    for name in grep_files(ctx, func, ["src", "include"]):
        path = ctx.root / name
        lines = path.read_text(encoding="utf-8").split("\n")
        own = path.name == f"{func}.c"
        for i, line in enumerate(lines):
            if own or (name.endswith(".h") and prototype.match(line)):
                for a, b in renames:
                    line = re.sub(r"\b" + re.escape(a) + r"\b", b, line)
                lines[i] = line
        path.write_text("\n".join(lines), encoding="utf-8")


def refs(ctx: Context, dirs: list[str]) -> Table:
    """Return the address-named units with their reference counts, most used first."""
    units = {}
    for folder in dirs:
        for path in sorted((ctx.root / folder).rglob("func_????????.c")):
            units[path.stem] = path.relative_to(ctx.root).as_posix()
    counts: collections.Counter[str] = collections.Counter()
    word = re.compile(r"func_[0-9A-F]{8}")
    for folder in ("build/asm", "asm", "src", "include"):
        for path in (ctx.root / folder).rglob("*"):
            if path.suffix in (".s", ".c", ".h") and path.is_file():
                counts.update(
                    word.findall(path.read_text(encoding="utf-8", errors="replace"))
                )
    rows = [
        {"count": counts[name], "name": name, "unit": units[name]}
        for name in sorted(units, key=lambda n: (-counts[n], n))
    ]
    return Table("count name unit", rows, heads="")


def mentioned(ctx: Context, names: set[str]) -> set[str]:
    """Find tracked mentions outside the symbol tables."""
    if not names:
        return set()
    with tempfile.NamedTemporaryFile("w", suffix=".names", encoding="utf-8") as handle:
        handle.write("\n".join(sorted(names)) + "\n")
        handle.flush()
        result = subprocess.run(
            [
                "git",
                "grep",
                "-h",
                "-o",
                "-w",
                "-f",
                handle.name,
                "--",
                "src",
                "include",
                "asm",
                "config",
                f":(exclude){SPLIT}",
            ],
            cwd=ctx.root,
            capture_output=True,
            text=True,
            check=False,
        )
    return set(result.stdout.split())


def _check_table(
    target: str,
    entries: list[symbols.Entry],
    findings: list[str],
    repeated: dict[tuple[str, int, str], list[str]],
    aliases: list[tuple[str, symbols.Entry]],
) -> int:
    """Append one table's findings; return 1 when any of them fails the check."""
    status = 0
    for before, after in zip(entries, entries[1:], strict=False):
        if before.addr > after.addr:
            findings.append(
                f"order\t{target}\t{after.name} 0x{after.addr:08X} after "
                f"{before.name} 0x{before.addr:08X}"
            )
            status = 1
            break
    addresses: dict[str, set[int]] = collections.defaultdict(set)
    names_at: dict[int, list[str]] = collections.defaultdict(list)
    for entry in entries:
        addresses[entry.name].add(entry.addr)
        if entry.alias:
            aliases.append((target, entry))
        else:
            names_at[entry.addr].append(entry.name)
            repeated[(entry.name, entry.addr, entry.type)].append(target)
        if not entry.source:
            findings.append(f"no-source\t{target}\t{entry.name} 0x{entry.addr:08X}")
    for name, found in addresses.items():
        if len(found) > 1:
            status = 1
            findings.append(
                f"name-two-addresses\t{target}\t{name}\t"
                + " ".join(f"0x{a:08X}" for a in sorted(found))
            )
    for address, names in names_at.items():
        if len(names) > 1:
            status = 1
            findings.append(
                f"address-two-names\t{target}\t0x{address:08X}\t" + " ".join(names)
            )
    return status


@dataclass(frozen=True)
class CheckReport:
    findings: list[str]
    tables: int = 0
    rows: int = 0
    failed: bool = False
    error: str = ""


def check(ctx: Context) -> CheckReport:
    """Report the table's problems; a name at two addresses or an out-of-order table fails."""
    try:
        tables = symbols.load(ctx.root)
    except symbols.LinkError as error:
        return CheckReport([], failed=True, error=str(error))
    findings: list[str] = []
    repeated: dict[tuple[str, int, str], list[str]] = collections.defaultdict(list)
    aliases: list[tuple[str, symbols.Entry]] = []
    failed = False
    for target, entries in tables.items():
        failed |= bool(_check_table(target, entries, findings, repeated, aliases))
    for (name, address, type_), images in sorted(repeated.items()):
        if len(images) > 1:
            findings.append(
                f"repeat\t{len(images)}\t{name}\t0x{address:08X}\t{type_ or '-'}\t"
                + " ".join(images)
            )
    used = mentioned(ctx, {entry.name for _, entry in aliases})
    for target, entry in aliases:
        if entry.name not in used:
            findings.append(f"alias-unused\t{target}\t{entry.name} 0x{entry.addr:08X}")
    rows = sum(len(entries) for entries in tables.values())
    return CheckReport(findings, len(tables), rows, failed)
