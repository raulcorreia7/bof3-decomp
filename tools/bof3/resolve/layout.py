"""Structural parser for reviewed Splat layouts."""

from __future__ import annotations

import hashlib
import os
import re
from dataclasses import dataclass
from pathlib import Path
from typing import Any

import yaml

from bof3.core import psx_exe
from bof3.core.cache import file_memo
from bof3.resolve.ids import source_folder

_RAW_FUNCTION = re.compile(r"func_[0-9A-F]{8}\Z")
_MIXED_CASE_RAW_FUNCTION = re.compile(r"func_[0-9A-Fa-f]{8}\Z")
#: The row that holds a PS-X EXE's file header; the text starts ``psx_exe.HEADER_SIZE`` bytes after it.
PSX_EXE_HEADER_NAME = "psx_exe_header"


@dataclass(frozen=True)
class LayoutBoundary:
    file_start: int
    file_end: int | None
    virtual_start: int
    virtual_end: int | None
    kind: str
    #: The row's name without its folder.
    name: str | None
    #: The folder a row names its file in, relative to the image folder: ``../sound/``.
    folder: str = ""

    @property
    def is_function(self) -> bool:
        return self.kind in {"c", "asm"}


#: libyaml's C loader when PyYAML has it: several times faster than SafeLoader.
YAML_LOADER = getattr(yaml, "CSafeLoader", yaml.SafeLoader)


def read_splat(splat_path: Path) -> tuple[str, Any]:
    """Return one Splat layout's text and parsed document."""
    return file_memo(
        "splat-read", [splat_path], None, lambda: _parse_splat_text(splat_path)
    )


def _parse_splat_text(splat_path: Path) -> tuple[str, Any]:
    text = splat_path.read_text(encoding="utf-8")
    document = yaml.load(text, Loader=YAML_LOADER)
    target = target_of(splat_path)
    if target and isinstance(document, dict):
        complete(document, target)
    return text, document


def target_of(splat_path: Path) -> str | None:
    """Return the target id of a ``config/<target>/splat.yaml`` path, else None."""
    parts = splat_path.parent.parts
    if "config" not in parts:
        return None
    return "/".join(parts[len(parts) - parts[::-1].index("config") :])


def derived_options(target: str) -> dict[str, Any]:
    """Return the Splat options every target shares, filled in from its id."""
    parts = target.split("/")
    rest = parts[-1:] if parts[0] == "exe" else parts[1:]
    return {
        "generated_asm_macros_directory": "include/match",
        "generate_asm_macros_files": False,
        "platform": "psx",
        "compiler": "psyq",
        "basename": "_".join(rest),
        "base_path": "../" * (len(parts) + 1),
        "target_path": f"build/bin/{target}.bin",
        "asm_path": f"build/asm/{target}",
        "nonmatchings_path": ".",
        "data_path": "data",
        "src_path": "src/" + source_folder(target),
        "ld_script_path": f"build/asm/{target}/linker.ld",
        "asset_path": f"build/assets/{target}",
        "undefined_funcs_auto_path": f"build/asm/{target}/undefined_funcs_auto.txt",
        "undefined_syms_auto_path": f"build/asm/{target}/undefined_syms_auto.txt",
        "subalign": 4,
        "section_order": [".text", ".rodata", ".data", ".bss"],
        "create_c_files": True,
    }


#: The image that every ``emi`` target reads symbols from, before its own.
EXECUTABLE = "exe/slus_004_22"


def complete(document: dict[str, Any], target: str) -> None:
    """Fill a reduced ``splat.yaml`` document with what its id derives."""
    options = derived_options(target)
    options.update(document.get("options") or {})
    document["options"] = options
    document.setdefault("name", options["basename"])
    document.setdefault(
        "symbol_owners",
        [target] if target.startswith("exe/") else [EXECUTABLE, target],
    )


@dataclass(frozen=True, slots=True)
class SplatFacts:
    """The target identity a reviewed ``splat.yaml`` holds."""

    load_address: int
    binary: str
    source_dir: str
    #: Sources outside ``source_dir`` that ``c`` rows name, relative to the repository.
    outside: tuple[str, ...] = ()


def splat_facts(splat_path: Path) -> SplatFacts:
    """Return the load address and the payload and source paths of one layout."""
    _text, document = read_splat(splat_path)
    if not isinstance(document, dict):
        raise ValueError(f"invalid Splat document in {splat_path}")
    segments = document.get("segments")
    if not isinstance(segments, list):
        raise ValueError(f"invalid Splat segments in {splat_path}")
    load_address = next(
        (
            _integer(segment["vram"], field="vram")
            for segment in segments
            if isinstance(segment, dict) and "vram" in segment
        ),
        None,
    )
    if load_address is None:
        raise ValueError(f"no Splat segment carries a vram in {splat_path}")
    options = document.get("options")
    if not isinstance(options, dict):
        raise ValueError(f"invalid Splat options in {splat_path}")
    binary = options.get("target_path")
    source_dir = options.get("src_path")
    if not isinstance(binary, str) or not isinstance(source_dir, str):
        raise ValueError(
            f"Splat options name no target_path and src_path in {splat_path}"
        )
    return SplatFacts(load_address, binary, source_dir, outside_sources(document))


def outside_sources(document: dict[str, Any]) -> tuple[str, ...]:
    """Return the files ``c`` rows name outside the image folder, such as ``../sound/SND_Init``."""
    source_dir = document["options"]["src_path"]
    found: list[str] = []
    for segment in document.get("segments", []):
        rows = (
            segment.get("subsegments") or [] if isinstance(segment, dict) else [segment]
        )
        for row in rows:
            parsed = _row(row)
            if parsed and parsed[1] == "c" and parsed[2] and "/" in parsed[2]:
                found.append(os.path.normpath(f"{source_dir}/{parsed[2]}.c"))
    return tuple(found)


@dataclass(frozen=True)
class ReviewedLayout:
    boundaries: tuple[LayoutBoundary, ...]
    load_address: int
    sha256: str
    #: Address of file byte 0: every row sits at ``image_base`` plus its file offset.
    image_base: int


def _integer(value: object, *, field: str) -> int:
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        try:
            return int(value, 0)
        except ValueError as exc:
            raise ValueError(f"invalid Splat {field}: {value!r}") from exc
    raise ValueError(f"invalid Splat {field}: {value!r}")


def _row_as_list(value: object) -> object:
    """Return a keyed row (``{start, type, name, ...}``) as the list row it stands for."""
    if isinstance(value, dict) and "start" in value and "type" in value:
        return [value["start"], value["type"], value.get("name", "")]
    return value


def _row(value: object) -> tuple[int, str, str | None] | None:
    value = _row_as_list(value)
    if not isinstance(value, list) or len(value) < 2 or not isinstance(value[1], str):
        return None
    name = str(value[2]) if len(value) >= 3 else None
    if (
        name
        and _MIXED_CASE_RAW_FUNCTION.fullmatch(name)
        and not _RAW_FUNCTION.fullmatch(name)
    ):
        raise ValueError(f"non-canonical Splat function name: {name}")
    return (
        _integer(value[0], field="offset"),
        value[1],
        name,
    )


def _header_size(rows: list[tuple[int, str, str | None]]) -> int:
    """Bytes between file byte 0 and the load address: a PS-X header row has them."""
    has_header = any(
        offset == 0 and name == PSX_EXE_HEADER_NAME for offset, _kind, name in rows
    )
    return psx_exe.HEADER_SIZE if has_header else 0


def parse_splat_layout(splat_path: Path, load_address: int) -> ReviewedLayout:
    return file_memo(
        "splat-layout",
        [splat_path],
        load_address,
        lambda: _parse_splat_layout(splat_path, load_address),
    )


def _parse_splat_layout(splat_path: Path, load_address: int) -> ReviewedLayout:
    text, document = read_splat(splat_path)
    if not isinstance(document, dict) or not isinstance(document.get("segments"), list):
        raise ValueError(f"invalid Splat segments in {splat_path}")

    rows: list[tuple[int, str, str | None]] = []
    eof: int | None = None
    for segment in document["segments"]:
        if isinstance(segment, list):
            if len(segment) == 1:
                eof = _integer(segment[0], field="EOF")
                continue
            parsed = _row(segment)
            if parsed is not None:
                rows.append(parsed)
            continue
        if not isinstance(segment, dict):
            raise ValueError(f"unsupported Splat segment in {splat_path}: {segment!r}")
        subsegments = segment.get("subsegments")
        if subsegments is None:
            segment_start = _integer(segment.get("start", 0), field="segment start")
            subsegments = [
                [segment_start, segment.get("type"), segment.get("name", "")]
            ]
        if not isinstance(subsegments, list):
            raise ValueError(f"invalid Splat subsegments in {splat_path}")
        for subsegment in subsegments:
            parsed = _row(subsegment)
            if parsed is None:
                raise ValueError(
                    f"unsupported Splat subsegment in {splat_path}: {subsegment!r}"
                )
            rows.append(parsed)

    base = load_address - _header_size(rows)
    starts = [(offset, base + offset, kind, name) for offset, kind, name in rows]
    starts.sort(key=lambda item: item[0])
    boundaries: list[LayoutBoundary] = []
    for index, (file_start, virtual_start, kind, name) in enumerate(starts):
        file_end = starts[index + 1][0] if index + 1 < len(starts) else eof
        virtual_end = (
            virtual_start + file_end - file_start if file_end is not None else None
        )
        folder, _, stem = (name or "").rpartition("/")
        boundaries.append(
            LayoutBoundary(
                file_start,
                file_end,
                virtual_start,
                virtual_end,
                kind,
                stem if name is not None else None,
                f"{folder}/" if folder else "",
            )
        )
    return ReviewedLayout(
        tuple(boundaries), load_address, hashlib.sha256(text.encode()).hexdigest(), base
    )
