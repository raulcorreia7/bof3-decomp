#!/usr/bin/env python3
"""Write objdiff's project file and the progress report.

``generate`` walks every compiled C source in every target manifest, assembles
the split asm into a target object, pairs it with the compiled object,
and writes ``objdiff.json``. The compiled objects, the project and the generated
objects live flat in the Meson build directory ``--build-dir``. SDK library rows and
hand-written assembly units carry their own progress categories, so the game totals stay
game-only. ``report`` runs objdiff's report step and stamps ``build/report.json``
with its provenance and one row per image.

A function whose body is an ``INCLUDE_ASM`` is the split assembly the target comes from,
so it is not lifted C. The compiled object marks each such body with a
``<name>.NON_MATCHING`` alias; the report compares a copy of the object with those
bodies overwritten, so they score 0%, and no unit holding one is complete. The copy
feeds the report only: the images link the compiled objects.
"""

from __future__ import annotations

import argparse
import json
import os
import re
import struct
import subprocess
import sys
from collections import Counter
from dataclasses import dataclass
from datetime import UTC, datetime
from pathlib import Path
from typing import Any

import quality
from bof3.adapters.config import symbol_files
from bof3.core.paths import ROOT
from bof3.link import symbols
from bof3.link.graph import source_object
from bof3.resolve import load_target_manifests
from bof3.status.claims import DRAFT_RE, QUOTE_INCLUDE_RE, source_text

#: The source and split-assembly folders, and the report the status site reads.
SRC = "src"
ASM = "asm"
SPLIT = "build/asm"
REPORT = "build/report.json"
LIBRARY_UNITS = "config/sdk/library-units.jsonl"
#: The pinned binutils wrappers and the flags the images assemble with.
ASSEMBLER = "bin/internal/binutils/as"
NM = "bin/internal/binutils/nm"
OBJCOPY = "bin/internal/binutils/objcopy"
ASSEMBLER_FLAGS = ("-G0", "-EL", "-mips1")
ASM_INCLUDE = ("include/match",)
#: What a source claims about its unit, and how its split asm and marker are named.
MATCH_MARKER = re.compile(r"^[ \t]*MATCH\b", re.MULTILINE)
FUNC_ADDRESS = re.compile(r"^func_([0-9A-Fa-f]{8})$")
DATA_ADDRESS = re.compile(r"^(?:D|T|jtbl)_([0-9A-Fa-f]+)$")
NONMATCHING_SUFFIX = ".NON_MATCHING"
DATA_LABEL = "dlabel"
HAND_MARKER = "\nHAND_ASM "
HAND_DIR = "hand"
DATA_DIR = "data"
#: objdiff's progress categories: the game totals read `game` only.
GAME_CATEGORY = "game"
SDK_CATEGORY = "sdk"
HAND_CATEGORY = "hand-asm"
CATEGORIES = (
    {"id": GAME_CATEGORY, "name": "Game code rebuilt in C"},
    {"id": SDK_CATEGORY, "name": "PsyQ SDK (shown apart)"},
    {"id": HAND_CATEGORY, "name": "Hand-written assembly (shown apart)"},
)
#: objdiff's own project schema; the generated file is not a tracked config.
SCHEMA_URL = (
    "https://raw.githubusercontent.com/encounter/objdiff/main/config.schema.json"
)
#: Characters an SDK symbol cannot carry in a GAS label.
SAFE_SYMBOL = re.compile(r"[^A-Za-z0-9_]")
#: ELF32 little-endian header, section-header and symbol layouts.
ELF_HEADER = struct.Struct("<16xHHIIIIIHHHHHH")
ELF_SECTION = struct.Struct("<10I")
ELF_SYMBOL = struct.Struct("<IIIBBH")
SHT_SYMTAB = 2


@dataclass(frozen=True)
class Project:
    """One checkout and the Meson build directory the project and units live in."""

    root: Path
    build_dir: Path
    match: re.Pattern[str] = MATCH_MARKER
    draft: re.Pattern[str] = DRAFT_RE
    func_address: re.Pattern[str] = FUNC_ADDRESS
    data_address: re.Pattern[str] = DATA_ADDRESS

    def command(self, argv: list[str]) -> str:
        """Run one tool and return stdout; a failure exits with its stderr."""
        proc = subprocess.run(argv, capture_output=True, text=True, check=False)
        if proc.returncode:
            detail = proc.stderr.strip() or proc.stdout.strip()
            raise SystemExit(f"{argv[0]} failed: {detail}")
        return proc.stdout

    def assemble(
        self,
        sources: list[Path],
        output: Path,
        readable: dict[str, int] | None = None,
    ) -> Path:
        """Assemble one unit's split asm, reusing an object that is already current."""
        output.parent.mkdir(parents=True, exist_ok=True)
        inputs = [*sources, *symbol_files(self.root)]
        if output.is_file() and all(
            source.stat().st_mtime <= output.stat().st_mtime for source in inputs
        ):
            return output
        source = self._combine(sources, output)
        self._assemble(source, output)
        self._resolve_data(source, output, readable or {})
        self._strip(source, output)
        output.touch()
        return output

    def _assemble(
        self, source: Path, output: Path, definitions: tuple[str, ...] = ()
    ) -> None:
        """Run the assembler over one source, with optional ``--defsym`` pins."""
        argv = [str(self.root / ASSEMBLER), *ASSEMBLER_FLAGS]
        argv.extend(f"-I{self.root / include}" for include in ASM_INCLUDE)
        argv.extend(definitions)
        argv.extend(["-o", str(output), str(source)])
        self.command(argv)

    def _resolve_data(
        self, source: Path, output: Path, readable: dict[str, int]
    ) -> None:
        """Resolve data relocations to their addresses so a base constant can match."""
        definitions = []
        for line in self.command([str(self.root / NM), "-u", str(output)]).splitlines():
            if not line.split():
                continue
            name = line.split()[-1]
            match = self.data_address.match(name)
            if match is not None:
                definitions.append(f"--defsym={name}=0x{match.group(1)}")
            elif name in readable:
                definitions.append(f"--defsym={name}=0x{readable[name]:08X}")
        if definitions:
            self._assemble(source, output, tuple(definitions))

    def _strip(self, source: Path, output: Path) -> None:
        """Remove the ``.NON_MATCHING`` alias that would count as a unit symbol."""
        names = [
            fields[-1]
            for line in self.command(
                [str(self.root / NM), "-g", "--defined-only", str(output)]
            ).splitlines()
            if (fields := line.split()) and fields[-1].endswith(NONMATCHING_SUFFIX)
        ]
        if names:
            argv = [
                str(self.root / OBJCOPY),
                *[f"--strip-symbol={name}" for name in names],
                str(output),
            ]
            self.command(argv)

    def _combine(self, sources: list[Path], output: Path) -> Path:
        """Return one assembler input, hiding data labels that are not functions."""
        pieces = [
            source.read_text(encoding="utf-8", errors="replace") for source in sources
        ]
        prelude = bool(pieces) and not any(
            '.include "macro.inc"' in piece or '.include "labels.inc"' in piece
            for piece in pieces
        )
        if prelude:
            pieces.insert(0, '.include "macro.inc"\n')
        label = re.compile(rf"^\s*{re.escape(DATA_LABEL)}\s+(\S+)", re.M)
        hidden = sorted(
            {match.group(1) for piece in pieces for match in label.finditer(piece)}
        )
        if len(sources) == 1 and not hidden and not prelude:
            return sources[0]
        combined = output.with_suffix(".s")
        text = "\n".join(pieces)
        if hidden:
            text += "\n" + "\n".join(f".hidden {name}" for name in hidden) + "\n"
        combined.write_text(text, encoding="utf-8")
        return combined

    def source_asm(self, target: str, source: Path) -> tuple[list[Path], str]:
        """Return a C source's split asm files and its progress category."""
        stem = source.stem
        hand = self.root / ASM / target / HAND_DIR / f"{stem}.s"
        if hand.is_file():
            return [hand], HAND_CATEGORY
        directory = self.root / SPLIT / target
        found = [directory / f"{stem}.s"] if (directory / f"{stem}.s").is_file() else []
        data = directory / DATA_DIR
        if data.is_dir():
            found.extend(sorted(data.glob(f"{stem}.*.s")))
        found.extend(sorted(directory.glob(f"{stem}.*.s")))
        return _unique(found), GAME_CATEGORY

    def report_base(self, base: Path) -> tuple[Path, bool]:
        """Return the object the report compares and whether it holds ``INCLUDE_ASM`` bodies."""
        output = self.build_dir / "objdiff/base" / base.name
        if output.is_file() and base.stat().st_mtime <= output.stat().st_mtime:
            return output, True
        suffix = NONMATCHING_SUFFIX
        data = base.read_bytes()
        if suffix.encode("ascii") in data:
            patched = bytearray(data)
            for offset, size in _unlifted_ranges(data, suffix, base):
                patched[offset : offset + size] = b"\xff" * size
            output.parent.mkdir(parents=True, exist_ok=True)
            output.write_bytes(patched)
            return output, True
        output.unlink(missing_ok=True)
        return base, False

    def marked(self, source: Path) -> bool:
        return bool(self.match.search(source_text(source)))

    def drafted(self, source: Path) -> bool:
        return bool(self.draft.search(source_text(source)))

    def hand_complete(self, source: Path) -> bool:
        """Return True for a hand-written unit marked `HAND_ASM`."""
        text = source.read_text(encoding="utf-8", errors="replace")
        return HAND_MARKER in text


def _elf_sections(data: bytes, path: Path) -> list[tuple]:
    """Return the section headers of an ELF32 little-endian object."""
    if data[:5] != b"\x7fELF\x01" or data[5] != 1:
        raise SystemExit(f"{path} is not an ELF32 little-endian object")
    fields = ELF_HEADER.unpack_from(data)
    return [
        ELF_SECTION.unpack_from(data, fields[5] + index * fields[10])
        for index in range(fields[11])
    ]


def _unlifted_ranges(data: bytes, suffix: str, path: Path) -> list[tuple[int, int]]:
    """Return the file offset and size of every body the object marks with ``suffix``."""
    sections = _elf_sections(data, path)
    tag = suffix.encode("ascii")
    ranges: list[tuple[int, int]] = []
    for _, kind, _, _, offset, size, link, *_ in sections:
        strings = sections[link][4]
        for position in (
            range(offset, offset + size, ELF_SYMBOL.size) if kind == SHT_SYMTAB else ()
        ):
            name, value, length, _, _, index = ELF_SYMBOL.unpack_from(data, position)
            if not 0 < index < len(sections):
                continue
            if not data[strings + name : data.index(b"\0", strings + name)].endswith(
                tag
            ):
                continue
            if not length:
                raise SystemExit(f"{path}: a {suffix} marker has no size")
            ranges.append((sections[index][4] + value, length))
    return ranges


def _unique(paths: list[Path]) -> list[Path]:
    """Return the paths in order without duplicates."""
    seen: set[Path] = set()
    out: list[Path] = []
    for path in paths:
        resolved = path.resolve()
        if resolved not in seen:
            seen.add(resolved)
            out.append(path)
    return out


def _relative(path: Path, start: Path) -> str:
    return Path(os.path.relpath(path, start)).as_posix()


def _target_rows(root: Path) -> list[dict[str, Any]]:
    return [
        {
            "id": manifest.id.value,
            "type": manifest.type,
            "binary": manifest.binary,
            "source_dir": manifest.source_dir,
            "outside_sources": manifest.outside_sources,
            "load_address": manifest.load_address,
        }
        for manifest in load_target_manifests(root).values()
    ]


def _library_rows(root: Path) -> list[dict[str, Any]]:
    """Return the SDK library rows, or an empty list when the file is absent."""
    path = root / LIBRARY_UNITS
    if not path.is_file():
        return []
    return [
        json.loads(line)
        for line in path.read_text(encoding="utf-8").splitlines()
        if line.strip()
    ]


def _unit(
    project: Project,
    name: str,
    target: Path,
    base: Path | None,
    metadata: dict[str, Any],
) -> dict[str, Any]:
    """Return one objdiff unit with paths relative to the project directory."""
    project_dir = project.build_dir
    unit: dict[str, Any] = {
        "name": name,
        "target_path": _relative(target, project_dir),
        "metadata": metadata,
    }
    if base is not None:
        unit["base_path"] = _relative(base, project_dir)
    return unit


def _base_object(project: Project, source: Path, relative: Path) -> Path:
    """Return the object objdiff compares against: the draft build's for a draft source.

    A draft that does not compile leaves an empty object; the matching build's object
    then keeps the source's matched functions in the report.
    """
    draft = project.draft.search(source.read_text(encoding="utf-8", errors="replace"))
    base = project.build_dir / source_object(relative, draft=bool(draft))
    if draft and base.is_file() and base.stat().st_size == 0:
        return project.build_dir / source_object(relative)
    return base


def _game_unit(
    project: Project,
    target_id: str,
    source: Path,
    asm: Path,
    category: str,
    readable: dict[str, int],
) -> dict[str, Any]:
    """Return the unit of one C source and assemble its target object."""
    relative = source.relative_to(project.root / SRC)
    base = _base_object(project, source, relative)
    if not base.is_file():
        raise SystemExit(
            f"missing {base}; build the images first, and if {source} gained "
            "its NON_MATCHING marker since the last configure, run `meson setup "
            "--reconfigure` so Meson builds its draft object"
        )
    broken = base.stat().st_size == 0
    unlifted = False
    if not broken and category != HAND_CATEGORY:
        base, unlifted = project.report_base(base)
    target_object = project.build_dir / "objdiff/target" / relative.with_suffix(".o")
    project.assemble(asm, target_object, readable)
    complete = (
        project.hand_complete(source)
        if category == HAND_CATEGORY
        else project.marked(source) and not project.drafted(source)
    )
    metadata = {
        "complete": complete and not broken and not unlifted,
        "source_path": str(relative),
        "progress_categories": [category],
    }
    return _unit(
        project,
        f"{target_id}/{source.stem}",
        target_object,
        None if broken or category == HAND_CATEGORY else base,
        metadata,
    )


def _included_sources(sources: list[Path]) -> set[Path]:
    """Return the C sources another source includes: they build inside that unit's object."""
    return {
        (source.parent / name).resolve()
        for source in sources
        for name in QUOTE_INCLUDE_RE.findall(
            source.read_text(encoding="utf-8", errors="replace")
        )
        if name.endswith(".c")
    }


def _claimed_functions(sources: list[Path]) -> set[str]:
    return {
        f"func_{match}"
        for source in sources
        for match in re.findall(
            r"\bfunc_([0-9A-Fa-f]{8})\b",
            source.read_text(encoding="utf-8", errors="replace"),
        )
    }


def _game_units(
    project: Project,
    target: dict[str, Any],
    library_ids: set[str],
    library_symbols: set[tuple[str, str]],
) -> tuple[list[dict[str, Any]], int]:
    """Return one target's game units and its C sources with no split asm target."""
    target_id = str(target["id"])
    source_dir = project.root / str(target["source_dir"])
    sources = sorted(
        [
            *source_dir.glob("*.c"),
            *(project.root / path for path in target["outside_sources"]),
        ]
    )
    readable = _readable_data(project.root, target_id)
    asm_dir = project.root / SPLIT / target_id
    if not asm_dir.is_dir() and any(
        project.func_address.match(source.stem) for source in sources
    ):
        raise SystemExit(f"missing {asm_dir}; run `meson setup build/meson`")
    units: list[dict[str, Any]] = []
    skipped = 0
    included = _included_sources(sources)
    for source in sources:
        if source.resolve() in included:
            continue
        match = project.func_address.match(source.stem)
        if match and f"{target_id}@0x{int(match.group(1), 16):08X}" in library_ids:
            continue
        if (target_id, source.stem) in library_symbols:
            continue
        asm, category = project.source_asm(target_id, source)
        if not asm:
            skipped += 1
            continue
        units.append(_game_unit(project, target_id, source, asm, category, readable))
    units.extend(
        _unlifted_units(
            project,
            target,
            {source.stem for source in sources} | _claimed_functions(sources),
            library_ids,
        )
    )
    return units, skipped


def _linked_objects(project: Project, target_id: str) -> set[str] | None:
    """Return the objects an image links, or None when its link map is missing."""
    path = project.root / "build/meson" / f"{target_id.replace('/', '+')}.map"
    if not path.is_file():
        return None
    return set(path.read_text(encoding="utf-8", errors="replace").split())


def _unlifted_units(
    project: Project,
    target: dict[str, Any],
    c_stems: set[str],
    library_ids: set[str],
) -> list[dict[str, Any]]:
    """Return reviewed code with no C source: target-only and never complete."""
    target_id = str(target["id"])
    directory = project.root / SPLIT / target_id
    units: list[dict[str, Any]] = []
    if not directory.is_dir():
        return units
    linked = _linked_objects(project, target_id)
    flat = target_id.replace("/", "+")
    for source in sorted(directory.glob("*.s")):
        match = project.func_address.match(source.stem)
        if match is None or source.stem in c_stems:
            continue
        if f"{target_id}@0x{int(match.group(1), 16):08X}" in library_ids:
            continue
        if linked is not None and f"asm+{flat}+{source.stem}.s.o" not in linked:
            continue
        output = project.build_dir / "objdiff/target" / target_id / f"{source.stem}.o"
        project.assemble([source], output)
        units.append(
            _unit(
                project,
                f"{target_id}/{source.stem}",
                output,
                None,
                {
                    "complete": False,
                    "progress_categories": [GAME_CATEGORY],
                },
            )
        )
    return units


def _readable_data(root: Path, target: str) -> dict[str, int]:
    """Return ``name -> address`` for the readable data rows an image links against."""
    table = symbols.load(root)
    found: dict[str, set[int]] = {}
    for owner in symbols.link_owners(root, target):
        for entry in table.get(owner, ()):
            if entry.type != "func" and symbols.address_of(entry.name) is None:
                found.setdefault(entry.name, set()).add(entry.addr)
    return {name: addrs.pop() for name, addrs in found.items() if len(addrs) == 1}


def _sdk_source(row: dict[str, Any], payload: bytes, output: Path) -> Path:
    """Write one SDK unit's one-symbol target assembly and payload slice."""
    address = int(str(row["id"]).rsplit("@", 1)[1], 16)
    symbol = SAFE_SYMBOL.sub("_", str(row.get("symbol") or ""))
    if not symbol or symbol[0].isdigit():
        symbol = f"sdk_{address:08X}"
    source = output.with_suffix(".s")
    binary = output.with_suffix(".bin")
    binary.parent.mkdir(parents=True, exist_ok=True)
    binary.write_bytes(payload)
    text = (
        '.section .text, "ax"\n'
        f".globl {symbol}\n"
        f".type {symbol}, @function\n"
        f"{symbol}:\n"
        f'.incbin "{binary.resolve()}"\n'
        f".size {symbol}, . - {symbol}\n"
    )
    source.write_text(text, encoding="utf-8")
    return source


@dataclass(frozen=True)
class SdkBinary:
    """One target's payload bytes and the timestamp a unit object must beat."""

    target_id: str
    target: dict[str, Any]
    data: bytes
    stamp: float


def _sdk_binary(
    project: Project,
    target_id: str,
    target: dict[str, Any],
    cache: dict[str, SdkBinary],
    library_stamp: float,
) -> SdkBinary:
    """Return one target's payload, loading it once per generation."""
    cached = cache.get(target_id)
    if cached is not None:
        return cached
    path = project.root / str(target["binary"])
    try:
        data = path.read_bytes()
    except OSError as error:
        raise SystemExit(f"missing {path}: {error}; run tools/setup.sh") from error
    binary = SdkBinary(
        target_id, target, data, max(library_stamp, path.stat().st_mtime)
    )
    cache[target_id] = binary
    return binary


def _split_offsets(project: Project, target_id: str) -> set[int]:
    """Return the file offsets of a target's SDK units that stay split assembly."""
    path = project.root / "config" / target_id / "splat.yaml"
    if not path.is_file():
        return set()
    text = path.read_text(encoding="utf-8")
    return {
        int(match.group(1), 16)
        for match in re.finditer(r"\[0x([0-9A-Fa-f]+),\s*asm\b", text)
    }


def _sdk_linkage(
    row: dict[str, Any], binary: SdkBinary, split: set[int], address: int
) -> str:
    """Return how one SDK unit enters the image: ``object``, ``split-assembly`` or ``assembly``."""
    if not row.get("object"):
        return "assembly"
    offset = address - int(binary.target["load_address"])
    if str(binary.target.get("type")) == "executable":
        offset += 0x800
    return "split-assembly" if offset in split else "object"


def _sdk_info(row: dict[str, Any], linkage: str) -> dict[str, str]:
    """Return the library, member object and linkage the status site shows for one SDK unit."""
    parts = Path(str(row.get("object") or "")).parts
    return {
        "library": parts[-2] if len(parts) >= 2 else "",
        "member": Path(parts[-1]).stem if parts else "",
        "linkage": linkage,
    }


def _sdk_unit(
    project: Project, row: dict[str, Any], binary: SdkBinary
) -> tuple[int, dict[str, Any]] | None:
    """Build one SDK unit's target object, or None when the row is outside the payload."""
    address = int(str(row["id"]).rsplit("@", 1)[1], 16)
    size = int(str(row["size"]), 0)
    offset = address - int(binary.target["load_address"])
    if str(binary.target.get("type")) == "executable":
        offset += 0x800
    if size <= 0 or offset < 0 or offset + size > len(binary.data):
        return None
    output = project.build_dir / "objdiff/sdk" / binary.target_id / f"{address:08X}.o"
    if not output.is_file() or output.stat().st_mtime < binary.stamp:
        source = _sdk_source(row, binary.data[offset : offset + size], output)
        project.assemble([source], output)
    name = f"{binary.target_id}/{row.get('symbol') or f'0x{address:08X}'}"
    return address, _unit(
        project,
        name,
        output,
        None,
        {
            "complete": True,
            "source_path": str(row.get("object") or ""),
            "progress_categories": [SDK_CATEGORY],
        },
    )


def _sdk_units(
    project: Project,
    library: list[dict[str, Any]],
    targets: dict[str, dict[str, Any]],
) -> tuple[list[dict[str, Any]], dict[str, dict[str, str]]]:
    """Return one target-only unit per SDK library row, and each unit's library info."""
    if not library:
        return [], {}
    library_stamp = (project.root / LIBRARY_UNITS).stat().st_mtime
    cache: dict[str, SdkBinary] = {}
    units: list[dict[str, Any]] = []
    names: set[str] = set()
    splits: dict[str, set[int]] = {}
    info: dict[str, dict[str, str]] = {}
    for row in library:
        target_id = str(row["id"]).rsplit("@", 1)[0]
        target = targets.get(target_id)
        if target is None:
            continue
        binary = _sdk_binary(project, target_id, target, cache, library_stamp)
        result = _sdk_unit(project, row, binary)
        if result is None:
            continue
        address, unit = result
        name = str(unit["name"])
        if name in names:
            name = f"{name}@0x{address:08X}"
            unit["name"] = name
        names.add(name)
        split = splits.setdefault(target_id, _split_offsets(project, target_id))
        info[name] = _sdk_info(row, _sdk_linkage(row, binary, split, address))
        units.append(unit)
    return units, info


def _write_json(path: Path, document: dict[str, Any]) -> None:
    """Write one generated JSON document."""
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(document, indent=2) + "\n", encoding="utf-8")


def generate(root: Path | None, build_dir: Path) -> int:
    """Write the objdiff project and print its unit counts."""
    base = root.resolve() if root is not None else ROOT
    project = Project(base, build_dir.resolve())
    targets = _target_rows(base)
    library = _library_rows(base)
    library_ids = {str(row["id"]) for row in library}
    library_symbols = {
        (str(row["id"]).rsplit("@", 1)[0], str(row["symbol"]))
        for row in library
        if row.get("symbol")
    }
    units: list[dict[str, Any]] = []
    skipped = 0
    for target in targets:
        target_units, target_skipped = _game_units(
            project, target, library_ids, library_symbols
        )
        units.extend(target_units)
        skipped += target_skipped
    targets_by_id = {str(target["id"]): target for target in targets}
    sdk_units, sdk_info = _sdk_units(project, library, targets_by_id)
    units.extend(sdk_units)
    counts = Counter(str(unit["name"]) for unit in units)
    duplicates = sorted(name for name, count in counts.items() if count > 1)
    if duplicates:
        raise SystemExit(f"duplicate objdiff unit names: {duplicates[:8]}")
    units.sort(key=lambda unit: str(unit["name"]))
    document = {
        "$schema": SCHEMA_URL,
        "build_target": False,
        "build_base": False,
        "units": units,
        "progress_categories": [dict(category) for category in CATEGORIES],
    }
    _write_json(project.build_dir / "objdiff.json", document)
    _write_json(project.build_dir / "sdk.json", sdk_info)
    counts = Counter(str(unit["metadata"]["progress_categories"][0]) for unit in units)
    sys.stdout.write(
        f"objdiff: {len(units)} units ({counts[GAME_CATEGORY]} game, "
        f"{counts[SDK_CATEGORY]} sdk, {counts[HAND_CATEGORY]} hand-asm); "
        f"{skipped} data-only sources without a target\n"
    )
    return 0


def _commit(root: Path) -> str:
    """Return the checkout's short commit id; a checkout without one is an error."""
    result = subprocess.run(
        ["git", "-C", str(root), "rev-parse", "--short", "HEAD"],
        capture_output=True,
        text=True,
        check=False,
    )
    sha = result.stdout.strip()
    if result.returncode or not sha:
        raise SystemExit(f"report: {root} has no commit to stamp")
    return sha


def _image_counts(
    image_ids: list[str], units: list[dict[str, Any]]
) -> list[dict[str, Any]]:
    """Return every image's unit count, the images with no units included."""
    names = sorted(image_ids)
    counts = dict.fromkeys(names, 0)
    for unit in units:
        name = str(unit.get("name", ""))
        image = max(
            (candidate for candidate in names if name.startswith(f"{candidate}/")),
            key=len,
            default=None,
        )
        if image is None:
            raise SystemExit(f"report: unit {name} names no image")
        counts[image] += 1
    return [{"id": image, "units": counts[image]} for image in names]


def _unproven(data: dict[str, Any]) -> dict[str, str]:
    """Return each unit marked complete that holds a function objdiff scores under 100%."""
    found: dict[str, str] = {}
    for unit in data.get("units", []):
        if not unit.get("metadata", {}).get("complete"):
            continue
        short = [
            f"{fn['name']} {fn.get('fuzzy_match_percent', 0.0):.2f}%"
            for fn in unit.get("functions", [])
            if fn.get("fuzzy_match_percent", 0.0) < 100.0
        ]
        if short:
            found[unit["name"]] = ", ".join(short)
    return found


def _demote(project_file: Path, names: dict[str, str]) -> None:
    """Mark the named units incomplete in the objdiff project file."""
    project = json.loads(project_file.read_text(encoding="utf-8"))
    for unit in project["units"]:
        if unit["name"] in names:
            unit["metadata"]["complete"] = False
    project_file.write_text(json.dumps(project, indent=2) + "\n", encoding="utf-8")


def _generate_report(tool: str, project_dir: Path, report_path: Path) -> dict[str, Any]:
    """Run objdiff over the project and return the report it wrote."""
    try:
        result = subprocess.run(
            [
                tool,
                "report",
                "generate",
                "-p",
                str(project_dir),
                "-o",
                str(report_path),
            ],
            capture_output=True,
            text=True,
            check=False,
        )
    except OSError as err:
        raise SystemExit(f"objdiff-cli failed to start: {err}") from None
    if result.returncode:
        raise SystemExit(result.stderr.strip() or result.stdout.strip())
    return json.loads(report_path.read_text(encoding="utf-8"))


def report(root: Path | None, build_dir: Path) -> int:
    """Run objdiff's report step and stamp the report with its provenance."""
    base = root.resolve() if root is not None else ROOT
    report_path = base / REPORT
    found = subprocess.run(
        [str(base / "bin/internal/find-tool"), "objdiff-cli"],
        capture_output=True,
        text=True,
        check=False,
    )
    if found.returncode:
        raise SystemExit(
            "no working objdiff-cli on PATH; install it as docs/toolchain.md#matching-tools says"
        )
    tool = found.stdout.strip()
    project_dir = build_dir.resolve()
    data = _generate_report(tool, project_dir, report_path)
    unproven = _unproven(data)
    if unproven:
        _demote(project_dir / "objdiff.json", unproven)
        data = _generate_report(tool, project_dir, report_path)
        for name, functions in unproven.items():
            sys.stderr.write(f"report: {name} is not complete: {functions}\n")
        sys.stderr.write(
            f"report: {len(unproven)} MATCH units are not counted complete; see why with "
            "`objdiff-cli diff -p build/meson -u <unit> <function>`\n"
        )
    sha = _commit(base)
    date = datetime.now(UTC).strftime("%Y-%m-%d")
    data["provenance"] = {"commit": sha, "date": date}
    # objdiff drops unknown unit metadata, so the SDK library, member and linkage are
    # stamped here from the sidecar `generate` wrote.
    sdk_info = json.loads((project_dir / "sdk.json").read_text(encoding="utf-8"))
    for unit in data.get("units", []):
        if unit["name"] in sdk_info:
            unit.setdefault("metadata", {})["sdk"] = sdk_info[unit["name"]]
    data["quality"] = quality.totals(quality.scan(quality.work_files(base)))
    data["images"] = _image_counts(
        list(load_target_manifests(base)), list(data.get("units", []))
    )
    report_path.write_text(json.dumps(data, indent=2) + "\n", encoding="utf-8")
    images = data["images"]
    sys.stdout.write(
        f"report: {len(images)} images, {sum(image['units'] for image in images)} units, "
        f"{sha} {date}\n"
    )
    return 0


def build_parser() -> argparse.ArgumentParser:
    """Return the command-line parser."""
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    generate_parser = sub.add_parser("generate", help="write the objdiff project")
    generate_parser.add_argument("--root", type=Path)
    generate_parser.add_argument("--build-dir", type=Path, required=True)
    report_parser = sub.add_parser("report", help="write and stamp the progress report")
    report_parser.add_argument("--root", type=Path)
    report_parser.add_argument("--build-dir", type=Path, required=True)
    return parser


def main(argv: list[str] | None = None) -> int:
    """Run one subcommand and return its exit status."""
    args = build_parser().parse_args(argv)
    if args.command == "generate":
        return generate(args.root, args.build_dir)
    return report(args.root, args.build_dir)


if __name__ == "__main__":
    raise SystemExit(main())
