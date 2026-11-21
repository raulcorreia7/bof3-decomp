"""Check, add and annotate the symbol table rows."""

from __future__ import annotations

import argparse
import collections
import json
import re
import subprocess
import sys
import tempfile

from bof3.adapters.config import symbols_text, write_symbols
from bof3.errors import SymbolError
from bof3.link import symbols
from bof3.source import symtab
from bof3.symbols.context import Context, grep_files


def add(ctx: Context, args: argparse.Namespace) -> int:
    """Insert one row."""
    if not (ctx.root / "config" / args.image / "splat.yaml").is_file():
        print(
            f"symbol: no image {args.image}; "
            "use a folder id under config/ that holds a splat.yaml",
            file=sys.stderr,
        )
        return 2
    addr = int(args.addr, 16)
    row = symtab.format_row(
        args.name, addr, type=args.type, size=int(args.size, 0) if args.size else None,
        source=args.source, alias=args.alias,
    )  # fmt: skip
    text = symbols_text(ctx.root)
    write_symbols(ctx.root, symtab.add_row(text, args.image, args.name, row, addr))
    print(f"added {args.name} to [{args.image}]")
    return 0


def params(ctx: Context, args: argparse.Namespace) -> int:
    """Rename parameters in one function's unit file and its prototypes."""
    pairs = [p.split("=", 1) for p in args.pairs]
    if any(len(p) != 2 or not p[0] or not p[1] for p in pairs):
        raise SymbolError("symbol: write each rename as OLD=NEW")
    prototype = re.compile(r"\S[^=]*\b" + re.escape(args.func) + r"\s*\(.*\)\s*;")
    for name in grep_files(ctx, args.func, ["src", "include"]):
        path = ctx.root / name
        lines = path.read_text(encoding="utf-8").split("\n")
        own = path.name == f"{args.func}.c"
        for i, line in enumerate(lines):
            if own or (name.endswith(".h") and prototype.match(line)):
                for a, b in pairs:
                    line = re.sub(r"\b" + re.escape(a) + r"\b", b, line)
                lines[i] = line
        path.write_text("\n".join(lines), encoding="utf-8")
    return 0


def ref_rows(ctx: Context, dirs: list[str]) -> list[dict]:
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
    return [
        {"count": counts[name], "name": name, "unit": units[name]}
        for name in sorted(units, key=lambda n: (-counts[n], n))
    ]


def refs(ctx: Context, args: argparse.Namespace) -> int:
    """Print the address-named units with their reference counts, most used first."""
    for row in ref_rows(ctx, args.dirs or ["src"]):
        if args.jsonl:
            print(json.dumps(row, ensure_ascii=False))
        else:
            print(row["count"], row["name"], row["unit"], sep="\t")
    return 0


def mentioned(ctx: Context, names: set[str]) -> set[str]:
    """Return the names that a tracked file under ``src``, ``include``, ``asm`` or ``config`` uses."""
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
                ":(exclude)config/symbols/<image>.toml",
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


def check(ctx: Context, args: argparse.Namespace) -> int:
    """Report the table's problems; a name at two addresses or an out-of-order table exits 1."""
    try:
        tables = symbols.load(ctx.root)
    except symbols.LinkError as error:
        print(f"symbols: {error}")
        return 1
    findings: list[str] = []
    repeated: dict[tuple[str, int, str], list[str]] = collections.defaultdict(list)
    aliases: list[tuple[str, symbols.Entry]] = []
    status = 0
    rows = 0
    for target, entries in tables.items():
        rows += len(entries)
        status |= _check_table(target, entries, findings, repeated, aliases)
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
    print("\n".join(findings))
    sys.stderr.write(
        f"symbols: {len(tables)} tables, {rows} rows, {len(findings)} findings; "
        f"{'FAIL' if status else 'ok'}\n"
    )
    return status
