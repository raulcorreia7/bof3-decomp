"""Binary-map facts for one target: its reviewed units, spans and sources."""

from __future__ import annotations

import re
from collections.abc import Iterator, Mapping
from dataclasses import dataclass, field
from pathlib import Path

from bof3.core.cache import file_memo
from bof3.link.symbols import splat_map, splat_owners
from bof3.resolve.layout import ReviewedLayout, parse_splat_layout
from bof3.resolve.manifests import TargetManifest
from bof3.status import claims

CODE_KINDS = ("c", "asm")
_DATA_PREFIXES = ("T_", "D_")
_DATA_SUFFIXES = ("_pad", "_gap")


@dataclass(frozen=True, slots=True)
class Unit:
    """One mapped subsegment: a code function or a data blob."""

    name: str
    kind: str
    offset: int
    vaddr: int
    size: int
    source: Path | None
    #: The image's symbol rows, name -> address: how a marker naming a renamed function resolves.
    names: Mapping[str, int] = field(default=claims.NO_NAMES, compare=False, repr=False)

    @property
    def is_code(self) -> bool:
        return self.kind in CODE_KINDS

    @property
    def is_game_function(self) -> bool:
        return self.is_code and not is_data_name(self.name)


@dataclass(frozen=True, slots=True)
class TargetMap:
    """One target's map facts; `defect` explains an unreadable map."""

    id: str
    source_dir: Path
    binary: Path
    splat: Path
    payload_bytes: int
    load_address: int
    units: tuple[Unit, ...]
    defect: str | None = None

    @property
    def reviewed_code(self) -> tuple[Unit, ...]:
        return tuple(unit for unit in self.units if unit.is_game_function)


def bare_kind(kind: str) -> str:
    return kind.removeprefix(".")


def is_data_name(name: str) -> bool:
    return name.startswith(_DATA_PREFIXES) or name.endswith(_DATA_SUFFIXES)


def payload_bytes(root: Path, binary: str, target: str) -> int:
    """Length of the shipped payload; a missing or empty one names its image and fails."""
    path = root / binary
    if not path.is_file() or path.stat().st_size == 0:
        state = "missing" if not path.is_file() else "empty"
        raise FileNotFoundError(
            f"payload {binary} of {target} is {state}; run tools/setup.sh"
        )
    return path.stat().st_size


def manifest_error(error: Exception) -> str:
    return f"manifest: {type(error).__name__}: {error}"


def load_target(root: Path, manifest: TargetManifest) -> TargetMap:
    """Join one target manifest with its reviewed layout, sources and payload."""
    target = manifest.id.value
    source_dir = root / manifest.source_dir
    splat_path = root / manifest.splat
    binary_path = root / manifest.binary
    load_address = manifest.load_address
    try:
        owners = splat_owners(root, target)
    except OSError as error:
        return _defect(
            target,
            source_dir,
            binary_path,
            splat_path,
            0,
            0,
            manifest_error(error),
        )
    payload_length = payload_bytes(root, manifest.binary, target)
    names = function_names(root, owners)
    sources = source_index(source_dir, names)
    try:
        layout = parse_splat_layout(splat_path, load_address)
    except (OSError, ValueError) as error:
        return _defect(
            target,
            source_dir,
            binary_path,
            splat_path,
            payload_length,
            load_address,
            f"{type(error).__name__}: {error}",
        )
    return TargetMap(
        id=target,
        source_dir=source_dir,
        binary=binary_path,
        splat=splat_path,
        payload_bytes=payload_length,
        load_address=load_address,
        units=units_from_layout(layout, payload_length, sources, names),
    )


def _defect(
    target: str,
    source_dir: Path,
    binary: Path,
    splat: Path,
    payload_length: int,
    load_address: int,
    defect: str,
) -> TargetMap:
    return TargetMap(
        id=target,
        source_dir=source_dir,
        binary=binary,
        splat=splat,
        payload_bytes=payload_length,
        load_address=load_address,
        units=(),
        defect=defect,
    )


def units_from_layout(
    layout: ReviewedLayout,
    payload_length: int,
    sources: dict[str, Path],
    names: Mapping[str, int] = claims.NO_NAMES,
) -> tuple[Unit, ...]:
    """One `Unit` per boundary; the final span ends at the payload or the EOF."""
    units = []
    for boundary in layout.boundaries:
        end = boundary.file_end if boundary.file_end is not None else payload_length
        name = boundary.name or (
            f"{boundary.file_start:X}" if bare_kind(boundary.kind) == "c" else ""
        )
        unit = Unit(
            name=name,
            kind=boundary.kind,
            offset=boundary.file_start,
            vaddr=boundary.virtual_start,
            size=max(end - boundary.file_start, 0),
            source=sources.get(name),
            names=names,
        )
        units.extend(merged_functions(unit))
    return tuple(units)


def merged_functions(unit: Unit) -> tuple[Unit, ...]:
    """Split a merged translation-unit file into one `Unit` per function it holds."""
    if bare_kind(unit.kind) != "c" or unit.source is None:
        return (unit,)
    text = unit.source.read_text(encoding="utf-8", errors="replace")
    end = unit.vaddr + unit.size
    addresses = sorted(
        address
        for address in claims.function_addresses(text, unit.names)
        if unit.vaddr <= address < end
    )
    if len(addresses) < 2:
        return (unit,)
    stops = addresses[1:] + [end]
    return tuple(
        Unit(
            name=f"func_{address:08X}",
            kind=unit.kind,
            offset=unit.offset + address - unit.vaddr,
            vaddr=address,
            size=stop - address,
            source=unit.source,
            names=unit.names,
        )
        for address, stop in zip(addresses, stops, strict=True)
    )


def source_index(
    source_dir: Path, names: Mapping[str, int] = claims.NO_NAMES
) -> dict[str, Path]:
    """Map C file stems and marked or assembly-backed function names to sources."""
    if not source_dir.is_dir():
        return {}
    paths = [path for path in sorted(source_dir.glob("*.c")) if path.stem != "symbols"]
    sources = {path.stem: path for path in paths}
    for path in paths:
        text = path.read_text(encoding="utf-8", errors="replace")
        for address in claims.function_claims(text, names):
            sources.setdefault(f"func_{address:08X}", path)
    return sources


def function_names(root: Path, owners: list[str]) -> dict[str, int]:
    """Return ``name -> address`` over every symbol map Splat reads for the target."""
    paths = [root / splat_map(owner) for owner in owners]
    paths = [path for path in paths if path.is_file()]

    def read() -> dict[str, int]:
        names: dict[str, int] = {}
        for path in paths:
            names.update(_symbol_rows(path.read_text(encoding="utf-8")))
        return names

    return file_memo("function-names", paths, (), read)


#: Symbol map rows read ``name = 0xADDR;`` and usually carry a trailing comment.
_ROW_COMMENT = re.compile(r"//[^\n]*")


def _symbol_rows(text: str) -> Iterator[tuple[str, int]]:
    """``(name, address)`` of every row, comments stripped."""
    for line in _ROW_COMMENT.sub("", text).splitlines():
        name, separator, value = line.partition("=")
        value = value.strip().rstrip(";").strip()
        if not separator or not name.strip() or not value.lower().startswith("0x"):
            continue
        try:
            yield (name.strip(), int(value, 16))
        except ValueError:
            continue
