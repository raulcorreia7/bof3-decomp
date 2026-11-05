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
import csv
import json
import os
import re
import struct
import subprocess
import sys
import tomllib
from collections import Counter
from dataclasses import dataclass
from datetime import UTC, datetime
from pathlib import Path
from typing import Any

import quality
from bof3.link import symbols
from bof3.link.graph import source_object
from bof3.resolve import load_target_manifests
from bof3.status.claims import source_text

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
    """One checkout and the objdiff settings read from ``config/project.toml``."""

    root: Path
    cfg: dict[str, Any]
    match: re.Pattern[str]
    draft: re.Pattern[str]
    func_address: re.Pattern[str]
    data_address: re.Pattern[str]

    def path(self, key: str) -> Path:
        """Return one configured path under the checkout root."""
        return (self.root / self.cfg[key]).resolve()

    def tool(self, key: str) -> str:
        """Return one configured tool path, keeping the symlink's verb name."""
        return str(self.root / self.cfg[key])

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
        """Assemble one unit's split asm, reusing an object that is already current.

        ``readable`` maps the readable data names the image links against to their
        addresses; a reference to one resolves as the compiled base's constant does.
        """
        output.parent.mkdir(parents=True, exist_ok=True)
        inputs = [*sources, self.root / symbols.TABLE]
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
        argv = [
            self.tool("assembler"),
            *[str(flag) for flag in self.cfg["assembler_flags"]],
        ]
        argv.extend(f"-I{self.root / include}" for include in self.cfg["asm_include"])
        argv.extend(definitions)
        argv.extend(["-o", str(output), str(source)])
        self.command(argv)

    def _resolve_data(
        self, source: Path, output: Path, readable: dict[str, int]
    ) -> None:
        """Resolve data relocations to their addresses so a base constant can match."""
        definitions = []
        for line in self.command([self.tool("nm"), "-u", str(output)]).splitlines():
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
                [self.tool("nm"), "-g", "--defined-only", str(output)]
            ).splitlines()
            if (fields := line.split())
            and fields[-1].endswith(str(self.cfg["nonmatching_suffix"]))
        ]
        if names:
            argv = [
                self.tool("objcopy"),
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
        label = re.compile(
            rf"^\s*{re.escape(str(self.cfg['data_label']))}\s+(\S+)", re.M
        )
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
        hand = self.root / self.cfg["asm"] / target / self.cfg["hand_dir"] / f"{stem}.s"
        if hand.is_file():
            return [hand], str(self.cfg["hand_category"])
        directory = self.root / self.cfg["asm"] / target
        found = [directory / f"{stem}.s"] if (directory / f"{stem}.s").is_file() else []
        data = directory / self.cfg["data_dir"]
        if data.is_dir():
            found.extend(sorted(data.glob(f"{stem}.*.s")))
        found.extend(sorted(directory.glob(f"{stem}.*.s")))
        return _unique(found), str(self.cfg["game_category"])

    def report_base(self, base: Path) -> tuple[Path, bool]:
        """Return the object the report compares and whether it holds ``INCLUDE_ASM`` bodies.

        The compiled object assembles the same split assembly as the target for an
        ``INCLUDE_ASM`` function, so those bytes would score 100%. The report copy
        overwrites each such body; an object without one is used as built.
        """
        output = self.path("report_objects") / base.name
        if output.is_file() and base.stat().st_mtime <= output.stat().st_mtime:
            return output, True
        suffix = str(self.cfg["nonmatching_suffix"])
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
        """Return True when the source, or a header it includes, carries a ``MATCH`` marker."""
        return bool(self.match.search(source_text(source)))

    def hand_complete(self, source: Path) -> bool:
        """Return True for a hand-written unit with the profiled origin proof."""
        text = source.read_text(encoding="utf-8", errors="replace")
        return str(self.cfg["hand_marker"]) in text


def _unlifted_ranges(data: bytes, suffix: str, path: Path) -> list[tuple[int, int]]:
    """Return the file offset and size of every body the object marks with ``suffix``.

    The object is ELF32 little-endian MIPS. A marker is a defined symbol named
    ``<function><suffix>`` whose value and size span the function in its section.
    """
    if data[:5] != b"\x7fELF\x01" or data[5] != 1:
        raise SystemExit(f"{path} is not an ELF32 little-endian object")
    fields = ELF_HEADER.unpack_from(data)
    section_offset, section_size, section_count = fields[5], fields[10], fields[11]
    sections = [
        ELF_SECTION.unpack_from(data, section_offset + index * section_size)
        for index in range(section_count)
    ]
    ranges: list[tuple[int, int]] = []
    for _, kind, _, _, offset, size, link, _, _, _ in sections:
        if kind != SHT_SYMTAB:
            continue
        strings = sections[link][4]
        for position in range(offset, offset + size, ELF_SYMBOL.size):
            name, value, length, _, _, index = ELF_SYMBOL.unpack_from(data, position)
            if not 0 < index < section_count:
                continue
            end = data.index(b"\0", strings + name)
            if not data[strings + name : end].endswith(suffix.encode("ascii")):
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
    """Return one object path relative to the project directory."""
    return Path(os.path.relpath(path, start)).as_posix()


def _load_config(path: Path, build_dir: Path) -> dict[str, Any]:
    """Return the ``[objdiff]`` table of one project config.

    The Meson build directory holds the compiled objects, named flat, and the project
    beside them; the report stays where the config puts it.
    """
    with path.open("rb") as handle:
        document = tomllib.load(handle)
    cfg = document["objdiff"]
    cfg["base_objects"] = cfg["project_dir"] = str(build_dir.resolve())
    cfg["target_objects"] = str(build_dir.resolve() / "objdiff/target")
    cfg["report_objects"] = str(build_dir.resolve() / "objdiff/base")
    cfg["sdk_objects"] = str(build_dir.resolve() / "objdiff/sdk")
    cfg["project"] = str(build_dir.resolve() / "objdiff.json")
    return cfg


def _target_rows(root: Path) -> list[dict[str, Any]]:
    """Return every target with the identity its layout gives it."""
    return [
        {
            "id": manifest.id.value,
            "kind": manifest.kind,
            "binary": manifest.binary,
            "source_dir": manifest.source_dir,
            "load_address": manifest.load_address,
        }
        for manifest in load_target_manifests(root).values()
    ]


def _library_rows(root: Path, cfg: dict[str, Any]) -> list[dict[str, Any]]:
    """Return the SDK library rows, or an empty list when the file is absent."""
    path = root / cfg["library_units"]
    if not path.is_file():
        return []
    with path.open(newline="", encoding="utf-8") as handle:
        return list(csv.DictReader(handle))


def _unit(
    project: Project,
    name: str,
    target: Path,
    base: Path | None,
    metadata: dict[str, Any],
) -> dict[str, Any]:
    """Return one objdiff unit with paths relative to the project directory."""
    project_dir = project.path("project_dir")
    unit: dict[str, Any] = {
        "name": name,
        "target_path": _relative(target, project_dir),
        "metadata": metadata,
    }
    if base is not None:
        unit["base_path"] = _relative(base, project_dir)
    return unit


def _base_object(project: Project, source: Path, relative: Path) -> Path:
    """Return the object objdiff compares against: the draft build's for a draft source."""
    draft = project.draft.search(source.read_text(encoding="utf-8", errors="replace"))
    return project.path("base_objects") / source_object(relative, draft=bool(draft))


def _game_units(
    project: Project,
    target: dict[str, Any],
    library_ids: set[str],
    library_symbols: set[tuple[str, str]],
) -> tuple[list[dict[str, Any]], int]:
    """Return one target's game units and its C sources with no split asm target."""
    target_id = str(target["id"])
    source_dir = project.root / str(target["source_dir"])
    sources = sorted(source_dir.glob("*.c"))
    readable = _readable_data(project.root, target_id)
    asm_dir = project.root / project.cfg["asm"] / target_id
    if not asm_dir.is_dir() and any(
        project.func_address.match(source.stem) for source in sources
    ):
        raise SystemExit(f"missing {asm_dir}; run `meson setup build/meson`")
    units: list[dict[str, Any]] = []
    skipped = 0
    for source in sources:
        match = project.func_address.match(source.stem)
        if match and f"{target_id}@0x{int(match.group(1), 16):08X}" in library_ids:
            continue
        if (target_id, source.stem) in library_symbols:
            continue
        asm, category = project.source_asm(target_id, source)
        if not asm:
            skipped += 1
            continue
        relative = source.relative_to(project.path("src"))
        base = _base_object(project, source, relative)
        if not base.is_file():
            raise SystemExit(
                f"missing {base}; build the images first, and if {source} gained "
                "its NON_MATCHING marker since the last configure, run `meson setup "
                "--reconfigure` so Meson builds its draft object"
            )
        broken = base.stat().st_size == 0
        unlifted = False
        if not broken and category != str(project.cfg["hand_category"]):
            base, unlifted = project.report_base(base)
        target_object = project.path("target_objects") / relative.with_suffix(".o")
        project.assemble(asm, target_object, readable)
        complete = (
            project.hand_complete(source)
            if category == str(project.cfg["hand_category"])
            else project.marked(source)
        )
        metadata = {
            "complete": complete and not broken and not unlifted,
            "source_path": str(relative),
            "progress_categories": [category],
        }
        units.append(
            _unit(
                project,
                f"{target_id}/{source.stem}",
                target_object,
                None
                if broken or category == str(project.cfg["hand_category"])
                else base,
                metadata,
            )
        )
    claimed = {
        f"func_{match}"
        for source in sources
        for match in re.findall(
            r"\bfunc_([0-9A-Fa-f]{8})\b",
            source.read_text(encoding="utf-8", errors="replace"),
        )
    }
    units.extend(
        _unlifted_units(
            project,
            target,
            {source.stem for source in sources} | claimed,
            library_ids,
        )
    )
    return units, skipped


def _unlifted_units(
    project: Project,
    target: dict[str, Any],
    c_stems: set[str],
    library_ids: set[str],
) -> list[dict[str, Any]]:
    """Return reviewed code with no C source: target-only and never complete."""
    target_id = str(target["id"])
    directory = project.root / project.cfg["asm"] / target_id
    units: list[dict[str, Any]] = []
    if not directory.is_dir():
        return units
    for source in sorted(directory.glob("*.s")):
        match = project.func_address.match(source.stem)
        if match is None or source.stem in c_stems:
            continue
        if f"{target_id}@0x{int(match.group(1), 16):08X}" in library_ids:
            continue
        output = project.path("target_objects") / target_id / f"{source.stem}.o"
        project.assemble([source], output)
        units.append(
            _unit(
                project,
                f"{target_id}/{source.stem}",
                output,
                None,
                {
                    "complete": False,
                    "progress_categories": [str(project.cfg["game_category"])],
                },
            )
        )
    return units


def _readable_data(root: Path, target: str) -> dict[str, int]:
    """Return ``name -> address`` for the readable data rows an image links against.

    A name with a row of a function type is left to the link: a call against an absolute
    address would not encode as one. A name whose owners give two addresses is left out.
    """
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
    if str(binary.target.get("kind")) == "executable":
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
    if str(binary.target.get("kind")) == "executable":
        offset += 0x800
    if size <= 0 or offset < 0 or offset + size > len(binary.data):
        return None
    output = project.path("sdk_objects") / binary.target_id / f"{address:08X}.o"
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
            "progress_categories": [str(project.cfg["sdk_category"])],
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
    library_stamp = (project.root / project.cfg["library_units"]).stat().st_mtime
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


def generate(config_path: Path, root: Path | None, build_dir: Path) -> int:
    """Write the objdiff project and print its unit counts."""
    cfg = _load_config(config_path, build_dir)
    base = root.resolve() if root is not None else config_path.resolve().parent.parent
    project = Project(
        base,
        cfg,
        re.compile(str(cfg["match_marker"]), re.MULTILINE),
        re.compile(r"^NON_MATCHING\s", re.MULTILINE),
        re.compile(str(cfg["func_address"])),
        re.compile(str(cfg["data_address"])),
    )
    targets = _target_rows(base)
    library = _library_rows(base, cfg)
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
        "progress_categories": [
            {"id": str(category["id"]), "name": str(category["name"])}
            for category in cfg["category"]
        ],
    }
    _write_json(project.path("project"), document)
    _write_json(project.path("project_dir") / "sdk.json", sdk_info)
    counts = Counter(str(unit["metadata"]["progress_categories"][0]) for unit in units)
    sys.stdout.write(
        f"objdiff: {len(units)} units ({counts['game']} game, {counts['sdk']} sdk, "
        f"{counts['hand-asm']} hand-asm); {skipped} data-only sources without a target\n"
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
    """Return every image's unit count, the images with no units included.

    A unit is named ``<image>/<source stem>``, so the image is the longest id
    the name starts with.
    """
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
    """Return each unit marked complete that holds a function objdiff scores under 100%.

    A ``MATCH`` marker is a claim; the report counts a unit complete only when every
    function in it is 100% as well. The value lists the unit's functions under 100%.
    """
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


def report(config_path: Path, root: Path | None, build_dir: Path) -> int:
    """Run objdiff's report step and stamp the report with its provenance.

    ``objdiff-cli report generate`` writes ``build/report.json``: its version,
    the progress categories and one unit per source file. The status site
    reads that file as its only input, so three top-level fields are added and
    the objdiff ones are left as written. ``provenance`` names the commit and
    UTC date that produced the report; ``images`` lists every image the layout
    names with its unit count, so the image with no units is counted instead
    of absent. ``quality`` holds the debt totals of ``tools/quality.py``.
    """
    cfg = _load_config(config_path, build_dir)
    base = root.resolve() if root is not None else config_path.resolve().parent.parent
    report_path = base / cfg["report"]
    found = subprocess.run(
        [str(base / "bin/internal/find-tool"), "objdiff-cli"],
        capture_output=True,
        text=True,
        check=False,
    )
    if found.returncode:
        raise SystemExit(
            "no working objdiff-cli on PATH; install it as docs/toolchain.md#matching-aids says"
        )
    project_dir = base / cfg["project_dir"]

    def generate() -> dict[str, Any]:
        """Run objdiff over the project and return the report it wrote."""
        try:
            result = subprocess.run(
                [
                    found.stdout.strip(),
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

    data = generate()
    unproven = _unproven(data)
    if unproven:
        _demote(project_dir / "objdiff.json", unproven)
        data = generate()
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
    sdk_path = base / cfg["project_dir"] / "sdk.json"
    sdk_info = json.loads(sdk_path.read_text(encoding="utf-8"))
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
    generate_parser.add_argument(
        "--config", type=Path, default=Path("config/project.toml")
    )
    generate_parser.add_argument("--root", type=Path)
    generate_parser.add_argument("--build-dir", type=Path, required=True)
    report_parser = sub.add_parser("report", help="write and stamp the progress report")
    report_parser.add_argument(
        "--config", type=Path, default=Path("config/project.toml")
    )
    report_parser.add_argument("--root", type=Path)
    report_parser.add_argument("--build-dir", type=Path, required=True)
    return parser


def main(argv: list[str] | None = None) -> int:
    """Run one subcommand and return its exit status."""
    args = build_parser().parse_args(argv)
    if args.command == "generate":
        return generate(args.config, args.root, args.build_dir)
    return report(args.config, args.root, args.build_dir)


if __name__ == "__main__":
    raise SystemExit(main())
