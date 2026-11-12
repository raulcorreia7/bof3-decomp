#!/usr/bin/env python3
"""Build one target's native Rizin project (image, types, script, .rzdb).

Usage: tools/rzproject.py TARGET --output build/rz/TARGET.rzdb

An overlay project maps the resident executable plus the overlay bytes at the
overlay's load address; an executable project opens its own image. The script
defines every function in the mapped Splat layouts and symbol rows, flags every
symbol in the mapped images' linker maps (``build/meson/<image>.map``), applies
PsyQ FLIRT signatures, loads the target header with ``to``, and saves project.
Rows in ``config/symbols.toml`` take priority for name, size and type; the map
fills in the rest. With no linker map the project holds rows and layouts only,
and the tool says so.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import struct
import subprocess
import sys
import tomllib
from dataclasses import dataclass
from pathlib import Path

import m2ctx
from bof3.core.io import write_atomic
from bof3.core.psx_exe import HEADER_SIZE
from bof3.core.psx_exe import read as read_exe
from bof3.link import symbols
from bof3.resolve import load_target_manifests
from bof3.resolve.ids import image_header
from bof3.resolve.layout import parse_splat_layout
from bof3.resolve.manifests import TargetManifest
from bof3.state.rows import Row

ROOT = Path(__file__).resolve().parent.parent
RIZIN = ROOT / "toolchains/rizin/bin/rizin"
RZ_SIGN = ROOT / "toolchains/rizin/bin/rz-sign"
SIZE = re.compile(r"\bsize:(0x[0-9A-Fa-f]+)\b")
TYPE = re.compile(r"\btype:(\w+)\b")
WIDTH = {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "s32": 4}
MAP_DIR = "build/meson"


@dataclass(frozen=True, slots=True)
class Outputs:
    """The files one project generation writes beside its ``.rzdb``."""

    image: Path
    types: Path
    script: Path
    project: Path
    log: Path


def read_rows(root: Path, manifest: TargetManifest) -> list[Row]:
    """Return the rows Splat reads for this target, in map order."""
    target = manifest.id.value
    return [
        row
        for owner in symbols.splat_owners(root, target)
        for row in symbols.target_rows(root, owner)
        if not row.alias
    ]


@dataclass(frozen=True, slots=True)
class MapSymbol:
    """One symbol a linker map places: its name, address, size and kind."""

    name: str
    address: int
    size: int
    function: bool


_CONTRIBUTION = re.compile(
    r"^\s+(?:(\.\S+)\s+)?0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+\S+\.o$"
)
_MAP_SECTION = re.compile(r"^ (\.\S+)$")
_MAP_SYMBOL = re.compile(r"^\s+0x([0-9a-f]{8})\s+([A-Za-z_]\w*)$")
_MAP_ABSOLUTE = re.compile(r"^\s+0x([0-9a-f]{8})\s+([A-Za-z_]\w*)\s+=\s+0x([0-9a-f]+)$")
_PLACED = (".text", ".data", ".rodata", ".sdata", ".bss", ".sbss", ".rdata")


def read_map(path: Path) -> list[MapSymbol]:
    """Return the symbols a linker map lists under placed input sections.

    A symbol runs to the next symbol of its input section, or to the section's end.
    A fixed-address assignment (``D_80123456 = 0x80123456``, from the symbol tables) is a symbol
    of unknown size; other linker-script assignments and discarded sections are skipped.
    """
    symbols: list[MapSymbol] = []
    section = ""
    pending = ""
    start = end = 0
    names: list[tuple[int, str]] = []

    def flush() -> None:
        for index, (address, name) in enumerate(names):
            top = names[index + 1][0] if index + 1 < len(names) else end
            symbols.append(MapSymbol(name, address, top - address, section == ".text"))
        names.clear()

    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        wrapped = _MAP_SECTION.match(line)
        if wrapped is not None:
            pending = wrapped[1]
            continue
        match = _CONTRIBUTION.match(line)
        if match is not None:
            flush()
            name = match[1] or pending
            pending = ""
            start, size = int(match[2], 16), int(match[3], 16)
            section = name if name in _PLACED else ""
            end = start + size
            if start < 0x80000000 or not size:
                section = ""
            continue
        absolute = _MAP_ABSOLUTE.match(line)
        if absolute is not None and int(absolute[1], 16) == int(absolute[3], 16):
            symbols.append(MapSymbol(absolute[2], int(absolute[1], 16), 0, False))
            continue
        match = _MAP_SYMBOL.match(line)
        if section and match is not None and start <= int(match[1], 16) < end:
            names.append((int(match[1], 16), match[2]))
    flush()
    return symbols


def read_maps(
    root: Path, targets: tuple[str, ...], spans: list[tuple[int, int]]
) -> list[MapSymbol]:
    """Return the map symbols inside the mapped images' ``spans`` (start, end).

    Every mapped image with a linker map adds its symbols; a fixed address outside the spans
    names bytes this project does not hold. A missing map is reported on stderr: that project holds rows and layouts only.
    """
    symbols: list[MapSymbol] = []
    for target in targets:
        path = root / MAP_DIR / f"{target.replace('/', '+')}.map"
        if path.is_file():
            symbols.extend(
                symbol
                for symbol in read_map(path)
                if any(low <= symbol.address < high for low, high in spans)
            )
        else:
            print(
                f"rzproject: {path.relative_to(root)} is missing; {target} symbols come from "
                "rows and Splat layouts only (build the image to add the map)",
                file=sys.stderr,
            )
    return symbols


def mapped_targets(
    root: Path, manifests: dict[str, TargetManifest], manifest: TargetManifest
) -> tuple[str, ...]:
    """Return the target and resident images visible to it."""
    link = tomllib.loads((root / "config/link.toml").read_text(encoding="utf-8"))
    visible = manifest.id.value
    if manifest.kind == "emi":
        visible = "emi"
    targets = [manifest.id.value]
    for entry in link.get("resident", ()):
        if visible not in entry.get("visible_to", ()):
            continue
        target = entry.get("target")
        if isinstance(target, str) and target in manifests and target not in targets:
            targets.append(target)
    return tuple(targets)


def split_functions(
    root: Path, manifests: dict[str, TargetManifest], targets: tuple[str, ...]
) -> list[tuple[str, int, int]]:
    """Return named function boundaries from each mapped Splat layout."""
    functions = []
    seen: set[int] = set()
    for target in targets:
        manifest = manifests[target]
        layout = parse_splat_layout(root / manifest.splat, manifest.load_address)
        for boundary in layout.boundaries:
            if (
                not boundary.is_function
                or not boundary.name
                or boundary.virtual_end is None
                or boundary.virtual_start in seen
            ):
                continue
            seen.add(boundary.virtual_start)
            functions.append(
                (
                    boundary.name,
                    boundary.virtual_start,
                    boundary.virtual_end - boundary.virtual_start,
                )
            )
    return functions


def image_spans(
    root: Path, manifests: dict[str, TargetManifest], targets: tuple[str, ...]
) -> list[tuple[int, int]]:
    """Return the (start, end) address span each mapped image occupies."""
    spans = []
    for target in targets:
        manifest = manifests[target]
        path = root / manifest.binary
        if manifest.kind == "executable":
            info = read_exe(path)
            if info is not None:
                spans.append((info.load_address, info.load_address + info.text_size))
        else:
            spans.append(
                (manifest.load_address, manifest.load_address + path.stat().st_size)
            )
    return spans


def write_image(
    root: Path,
    manifests: dict[str, TargetManifest],
    targets: tuple[str, ...],
    output: Path,
) -> None:
    """Write the Rizin image with every resident image and the target overlay."""
    exe_target = next(
        target for target in targets if manifests[target].kind == "executable"
    )
    exe_path = root / manifests[exe_target].binary
    info = read_exe(exe_path)
    if info is None:
        raise SystemExit(f"{exe_path}: not a PS-X EXE")
    exe = exe_path.read_bytes()
    regions = [
        (
            target,
            manifests[target].load_address,
            (root / manifests[target].binary).read_bytes(),
        )
        for target in targets
        if manifests[target].kind != "executable"
    ]
    regions.sort(key=lambda region: region[0] == targets[0])
    low = min([info.load_address, *(address for _, address, _ in regions)])
    high = max(
        [info.load_address + info.text_size]
        + [address + len(data) for _, address, data in regions]
    )
    image = bytearray(HEADER_SIZE + high - low)
    header = bytearray(exe[:HEADER_SIZE])
    struct.pack_into("<II", header, 0x18, low, high - low)
    image[:HEADER_SIZE] = header
    start = HEADER_SIZE + info.load_address - low
    image[start : start + info.text_size] = exe[
        HEADER_SIZE : HEADER_SIZE + info.text_size
    ]
    for _, address, data in regions:
        start = HEADER_SIZE + address - low
        image[start : start + len(data)] = data
    write_atomic(output, image)


_SKIP_TYPEDEFS = frozenset(
    {
        "bool",
        "clock_t",
        "gid_t",
        "mode_t",
        "off_t",
        "pid_t",
        "size_t",
        "time_t",
        "uid_t",
        "va_list",
        "wchar_t",
    }
)


def _typedef_name(block: str) -> str | None:
    """Return the name a top-level typedef declares, or None."""
    match = re.search(r"\b([A-Za-z_]\w*)\s*;\s*$", block, re.S)
    return match.group(1) if match else None


def _drop_self_typedef(block: str) -> str:
    """Turn ``typedef struct TAG {...} TAG;`` into a struct tag Rizin accepts."""
    head = block.lstrip()
    match = re.match(
        r"^typedef\s+(?:const\s+|volatile\s+)*(struct|union|enum)\s+([A-Za-z_]\w*)\s*\{",
        head,
    )
    if match is None:
        return block
    kind, tag = match.group(1), match.group(2)
    if re.search(rf"\}}\s*{re.escape(tag)}\s*;\s*$", block) is None:
        return block
    body = block[block.find("{") :]
    body = body[: body.rfind("}")] + "};"
    return f"{kind} {tag} {body}"


def _fix_fields(block: str) -> str:
    """Replace callable and bitfield members Rizin's C parser rejects."""
    callable = re.compile(
        r"^(\s*)([A-Za-z_][\w\s\*]*?)\s*\(\s*\*\s*([A-Za-z_]\w*)\s*"
        r"(\[[^\]]*\])?\s*\)\s*\([^;]*\)\s*;",
        re.M,
    )
    block = callable.sub(r"\1\2 *\3\4;", block)
    bitfield = re.compile(
        r"^(\s*[A-Za-z_][\w\s\*]*?)\s+([A-Za-z_]\w*)\s*:\s*\d+\s*;", re.M
    )
    return bitfield.sub(r"\1 \2;", block)


def types_only(text: str) -> str:
    """Keep top-level typedef, struct, union and enum declarations only.

    Rizin's ``to`` stops the script at the first function prototype it cannot
    parse, so the preprocessed chain is reduced to the declarations it needs
    for ``tp``/``ts``/``tt``: no callables, no data objects and no repeated or
    builtin typedef names.
    """
    blocks: list[str] = []
    current: list[str] = []
    depth = 0
    seen: set[str] = set()
    for line in text.splitlines():
        if not current and (
            not line.strip() or line.lstrip().startswith(("#", "//", "/*", "*"))
        ):
            continue
        current.append(line)
        depth = max(0, depth + line.count("{") - line.count("}"))
        if depth or not line.rstrip().endswith(";"):
            continue
        block = "\n".join(current)
        current = []
        head = block.lstrip()
        if "static_assertion_" in head:
            continue
        if not head.startswith(("typedef ", "struct ", "union ", "enum ")):
            continue
        if head.startswith(("struct ", "union ", "enum ")) and "{" not in block:
            continue
        name = _typedef_name(block)
        if name in _SKIP_TYPEDEFS or (name is not None and name in seen):
            continue
        if name is not None:
            seen.add(name)
        blocks.append(_fix_fields(_drop_self_typedef(block)))
    return "\n".join(blocks) + "\n"


def write_types(root: Path, manifest: TargetManifest, output: Path) -> None:
    """Write the target's flattened header for Rizin's ``to``."""
    header = root / manifest.source_dir / image_header(manifest.id.value)
    if not header.is_file():
        header = root / "include/common.h"
    compiler = os.environ.get("M2CTX_CC", "gcc")
    write_atomic(output, types_only(m2ctx.preprocess(header, compiler)))


def _objects(units: Path) -> list[str]:
    """Return the PsyQ objects the staged library rows name."""
    rows = [
        json.loads(line)
        for line in units.read_text(encoding="utf-8").splitlines()
        if line.strip()
    ]
    return sorted({str(row["object"]) for row in rows if row.get("object")})


def _signature(root: Path, cache: Path, name: str) -> Path | None:
    """Return one object's current FLIRT signature, generating it when stale."""
    source = root / name
    if not source.is_file():
        return None
    try:
        relative = Path(name).relative_to("toolchains/psyq/3.7")
    except ValueError:
        return None
    sig = cache / relative.with_suffix(".sig")
    if sig.is_file() and sig.stat().st_mtime >= source.stat().st_mtime:
        return sig
    sig.parent.mkdir(parents=True, exist_ok=True)
    result = subprocess.run(
        [str(RZ_SIGN), "-q", "-o", str(sig), str(source)],
        cwd=root,
        capture_output=True,
        check=False,
    )
    if result.returncode:
        sig.unlink(missing_ok=True)
        return None
    return sig


def signatures(root: Path, cache: Path) -> list[Path]:
    """Generate or reuse the FLIRT signatures for the staged PsyQ objects."""
    units = root / "config/sdk/library-units.jsonl"
    if not units.is_file():
        return []
    return [
        sig
        for name in _objects(units)
        if (sig := _signature(root, cache, name)) is not None
    ]


def _relative(root: Path, path: Path) -> str:
    """Return one generated path as the script's repository-relative spelling."""
    return path.relative_to(root).as_posix()


_ASM_SIZE = re.compile(r"^\s*nonmatching\s+\S+,\s*(0x[0-9A-Fa-f]+)", re.M)
_SIZE_DIRECTIVE = re.compile(r"^\s*\.size\s+\S+,\s*(0x[0-9A-Fa-f]+)", re.M)


def _row_size(comment: str) -> int | None:
    """Return a row's ``size:0x...`` value, or None when it names none."""
    match = SIZE.search(comment)
    return int(match.group(1), 16) if match is not None else None


def function_size(root: Path, targets: tuple[str, ...], name: str) -> int | None:
    """Return a function's split-assembly size, or None when no file names it."""
    for target in targets:
        for directory in (root / "asm" / target, root / "asm" / target / "hand"):
            path = directory / f"{name}.s"
            if not path.is_file():
                continue
            text = path.read_text(encoding="utf-8", errors="replace")
            for pattern in (_ASM_SIZE, _SIZE_DIRECTIVE):
                match = pattern.search(text)
                if match is not None:
                    return int(match.group(1), 16)
    return None


def write_function_commands(
    lines: list[str],
    targets: tuple[str, ...],
    rows: list[Row],
    functions: list[tuple[str, int, int]],
    mapped: list[MapSymbol],
) -> list[str]:
    """Write Rizin function analysis commands; return the name flags to set after FLIRT.

    FLIRT renames a matched function, so the game name goes in a flag of its own afterwards.
    """
    names = {row.address: row.name for row in rows if "type:func" in row.comment}
    defined: set[int] = set()
    owners: dict[str, int] = {}

    def unique(name: str, address: int) -> str:
        """One shared body carries one game name in several images; Rizin needs one per address."""
        owner = owners.setdefault(name, address)
        return name if owner == address else f"{name}_{address:08X}"

    for name, address, size in functions:
        if address in defined:
            continue
        defined.add(address)
        symbol_name = unique(names.get(address, name), address)
        lines.extend([f"s 0x{address:08X}", f"af+ {symbol_name}"])
        lines.append(f"afb+ 0x{address:08X} 0x{address:08X} 0x{size:x}")
    for row in rows:
        if "type:func" not in row.comment or row.address in defined:
            continue
        size = function_size(ROOT, targets, row.name) or _row_size(row.comment)
        if size is None:
            size = 1
        defined.add(row.address)
        lines.extend([f"s 0x{row.address:08X}", f"af+ {unique(row.name, row.address)}"])
        lines.append(f"afb+ 0x{row.address:08X} 0x{row.address:08X} 0x{size:x}")
    for symbol in mapped:
        if not symbol.function or symbol.address in defined:
            continue
        defined.add(symbol.address)
        lines.extend(
            [
                f"s 0x{symbol.address:08X}",
                f"af+ {unique(symbol.name, symbol.address)}",
                f"afb+ 0x{symbol.address:08X} 0x{symbol.address:08X} 0x{max(symbol.size, 1):x}",
            ]
        )
    flags = [f"f {name} {size} @ 0x{address:08X}" for name, address, size in functions]
    for row in rows:
        if "type:func" not in row.comment:
            continue
        size = function_size(ROOT, targets, row.name) or _row_size(row.comment) or 1
        flags.append(f"f {row.name} {size} @ 0x{row.address:08X}")
    return flags


def unique_flags(lines: list[str]) -> list[str]:
    """Keep one flag per name and address.

    Rizin refuses a second flag of one name. The resident executable's rows arrive once per
    mapped target and again from the function list, so the same flag repeats and is dropped;
    one name at another address (a shared body, a local label) takes its address as a suffix.
    """
    seen: dict[str, int] = {}
    kept: list[str] = []
    for line in lines:
        if line.startswith("f "):
            head, tail = line.split(" @ ")
            _, name, size = head.split(" ")
            address = int(tail, 16)
            if seen.get(name) == address:
                continue
            if name in seen:
                name = f"{name}_{address:08X}"
                if seen.get(name) == address:
                    continue
            seen[name] = address
            line = f"f {name} {size} @ {tail}"
        kept.append(line)
    return kept


def map_flags(mapped: list[MapSymbol]) -> list[str]:
    """Return the commands that flag every map symbol, one flagspace per name at an address.

    Rizin keeps one flag per address in a flagspace, and a row or layout name may already hold
    that address, so the map names live in ``bof3_map`` and a second name at an address goes to
    ``bof3_alias``.
    """
    lines = ["fs bof3_map"]
    aliases: list[str] = []
    placed: set[int] = set()
    names: set[str] = set()
    for symbol in mapped:
        if symbol.name in names:
            continue
        names.add(symbol.name)
        line = f"f {symbol.name} {max(symbol.size, 1)} @ 0x{symbol.address:08X}"
        if symbol.address in placed:
            aliases.append(line)
        else:
            placed.add(symbol.address)
            lines.append(line)
    return [*lines, "fs bof3_alias", *aliases]


def write_script(
    outputs: Outputs,
    targets: tuple[str, ...],
    rows: list[Row],
    functions: list[tuple[str, int, int]],
    mapped: list[MapSymbol],
    sigs: list[Path],
) -> None:
    """Write the native Rizin command script."""
    lines = [
        "# Generated by tools/rzproject.py; do not edit.",
        "e asm.arch=mips",
        "e asm.bits=32",
        "e asm.cpu=r3000a",
        "e cfg.bigendian=false",
        "e scr.color=0",
        "e str.encoding=ascii",
        f"o {_relative(ROOT, outputs.image)}",
    ]
    function_flags = write_function_commands(lines, targets, rows, functions, mapped)
    lines.extend(f"Fs {_relative(ROOT, sig)}" for sig in sigs)
    lines.append("fs bof3")
    lines.extend(function_flags)
    lines.append("fs bof3_data")
    sizes = {symbol.address: symbol.size for symbol in mapped}
    for row in rows:
        if "type:func" in row.comment:
            continue
        kind = TYPE.search(row.comment)
        size = (
            _row_size(row.comment)
            or (WIDTH.get(kind[1]) if kind else None)
            or sizes.get(row.address)
            or 1
        )
        lines.append(f"f {row.name} {size} @ 0x{row.address:08X}")
        if kind is not None:
            lines.append(f"CCu type:{kind[1]} @ 0x{row.address:08X}")
    lines[:] = unique_flags(lines)
    lines.extend(map_flags(mapped))
    lines.extend(
        [
            f"to {_relative(ROOT, outputs.types)}",
            f"Ps {_relative(ROOT, outputs.project)}",
        ]
    )
    write_atomic(outputs.script, "\n".join(lines) + "\n")


def run_rizin(root: Path, outputs: Outputs) -> None:
    """Replay the script and fail when it does not save a complete project."""
    if not RIZIN.is_file():
        raise SystemExit(
            f"{RIZIN}: rizin is missing; install it as docs/toolchain.md#matching-tools says"
        )
    outputs.project.unlink(missing_ok=True)
    result = subprocess.run(
        [str(RIZIN), "-q", "-N", "-i", str(outputs.script), "--"],
        cwd=root,
        capture_output=True,
        text=True,
        check=False,
    )
    log = result.stdout + result.stderr
    write_atomic(outputs.log, log)
    if (
        result.returncode
        or "Failed to run script" in log
        or not outputs.project.is_file()
    ):
        outputs.project.unlink(missing_ok=True)
        raise SystemExit(f"rizin failed for {outputs.project}; see {outputs.log}")


def main() -> int:
    """Build the project at ``--output`` for one target."""
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("target", help="target id, for example emi/battle/battle/03")
    parser.add_argument("--output", type=Path, required=True)
    args = parser.parse_args()
    manifests = load_target_manifests(ROOT)
    manifest = manifests.get(args.target)
    if manifest is None:
        raise SystemExit(f"unknown target: {args.target}")
    output = args.output if args.output.is_absolute() else ROOT / args.output
    outputs = Outputs(
        image=output.with_suffix(".image"),
        types=output.with_suffix(".types.c"),
        script=output.with_suffix(".rz"),
        project=output,
        log=output.with_suffix(".log"),
    )
    targets = mapped_targets(ROOT, manifests, manifest)
    write_image(ROOT, manifests, targets, outputs.image)
    write_types(ROOT, manifest, outputs.types)
    functions = split_functions(ROOT, manifests, targets)
    rows = [row for target in targets for row in read_rows(ROOT, manifests[target])]
    write_script(
        outputs,
        targets,
        rows,
        functions,
        read_maps(ROOT, targets, image_spans(ROOT, manifests, targets)),
        signatures(ROOT, ROOT / "build/rz/sig"),
    )
    run_rizin(ROOT, outputs)
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
