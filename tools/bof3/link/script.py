"""Parse Splat linker inputs and prepare each target's link inputs."""

from __future__ import annotations

import re
from dataclasses import dataclass
from pathlib import Path

from bof3.core.paths import ASM, BUILD, CONFIG
from bof3.link.inputs import Input, parse, write_if_changed
from bof3.resolve import normalize_target_id
from bof3.resolve.layout import parse_splat_layout
from bof3.resolve.manifests import SectionPlacement, load_target_manifest
from bof3.state.canonical import suffix_address
from bof3.status import map as target_map
from bof3.status import model as status_model

__all__ = [
    "Input",
    "Prepared",
    "kept",
    "parse",
    "prepare_link",
    "prune_linker_script",
    "rewrite",
    "write_if_changed",
    "shadowed",
]


_UNIT_OBJECT = re.compile(r"^(?P<stem>.*)\.(?:c|s)\.o$")
_OUTPUT_SECTION = re.compile(r"^\s*\.\S+\s+(0x[0-9a-fA-F]+)\s*:")


def unit_of(path: str) -> str | None:
    """Return the named C or assembly unit in an input object path."""
    match = _UNIT_OBJECT.match(path)
    return Path(match["stem"]).name if match is not None else None


def _input_starts(text: str) -> dict[int, int]:
    """Return each input line's enclosing output-section address."""
    starts: dict[int, int] = {}
    start = 0
    for number, line in enumerate(text.splitlines(), 1):
        if (header := _OUTPUT_SECTION.match(line)) is not None:
            start = int(header[1], 16)
        starts[number] = start
    return starts


def kept(
    text: str, placements: dict[tuple[str, str], int]
) -> dict[tuple[str, str], Input]:
    """Return each placement's input selector at its reviewed address."""
    starts = _input_starts(text)
    entries = parse(text)
    named: dict[tuple[str, str], list[Input]] = {}
    for entry in entries:
        key = (unit_of(entry.path) or "", entry.section)
        if key in placements:
            named.setdefault(key, []).append(entry)

    keep: dict[tuple[str, str], Input] = {}
    for key, entries_for_key in named.items():
        reachable = [
            entry for entry in entries_for_key if starts[entry.line] <= placements[key]
        ]
        keep[key] = max(
            reachable or entries_for_key, key=lambda entry: starts[entry.line]
        )

    # A placed table may sit in a jtbl object; its output section still names it by address.
    for key, address in placements.items():
        if key not in keep or starts[keep[key].line] > address:
            located = [
                entry
                for entry in entries
                if entry.section == key[1]
                and starts[entry.line] == address
                and suffix_address(unit_of(entry.path) or "") == address
            ]
            if len(located) == 1:
                keep[key] = located[0]
    return keep


def shadowed(text: str, placements: dict[tuple[str, str], int]) -> frozenset[int]:
    """Find selectors that would take a placed section away from its reviewed address."""
    entries = parse(text)
    starts = _input_starts(text)
    selected = kept(text, placements)
    keep = {entry.line for entry in selected.values()}
    dropped = {
        entry.line
        for entry in entries
        if (unit_of(entry.path) or "", entry.section) in placements
        and entry.line not in keep
    }
    for key, entry in selected.items():
        if unit_of(entry.path) == key[0]:
            continue
        address = placements[key]
        dropped.update(
            candidate.line
            for candidate in entries
            if candidate.section == key[1]
            and candidate.line != entry.line
            and (candidate.path == entry.path or starts[candidate.line] == address)
        )
    return frozenset(dropped)


def _object_paths(text: str) -> tuple[str, ...]:
    return tuple(dict.fromkeys(entry.path for entry in parse(text)))


def _rewrite_placements(
    text: str,
    placements: tuple[SectionPlacement, ...],
    exact_units: frozenset[str],
    unit_names: dict[int, str],
    binary: str,
    image_base: int,
    placement_directory: Path,
) -> tuple[str, dict[Path, str]]:
    """Replace non-exact placed input sections with retail-byte wrappers."""
    addresses = {
        (
            unit_names.get(placement.function, f"func_{placement.function:08X}"),
            placement.section,
        ): placement.address
        for placement in placements
    }
    selected = kept(text, addresses)
    updated, _ = prune_linker_script(text, addresses)
    existing = {(entry.path, entry.section) for entry in parse(text)}
    replacements: dict[int, str] = {}
    wrappers: dict[Path, str] = {}

    for placement in placements:
        unit = unit_names.get(placement.function, f"func_{placement.function:08X}")
        if unit in exact_units:
            continue
        key = (unit, placement.section)
        source = placement_directory / f"{unit}{placement.section}.s"
        obj = source.with_suffix(".s.o").as_posix()
        entry = selected.get(key)
        if entry is None:
            if (obj, placement.section) not in existing:
                # Aggregate TUs own their rodata as a whole; there is no
                # standalone function section to replace.
                continue
        else:
            replacements[entry.line] = f"{obj}({placement.section})"
        offset = placement.address - image_base
        wrappers[source] = (
            f".section {placement.section}\n"
            f'.incbin "{Path(binary).as_posix()}", {offset}, {placement.size}\n'
        )

    return rewrite(updated, replacements), wrappers


@dataclass(frozen=True, slots=True)
class Prepared:
    """One target's pruned linker script and what the pruning depended on."""

    text: str
    objects: tuple[str, ...]
    #: C files whose match markers decided which placed sections stay retail wrappers.
    sources: tuple[Path, ...]


def prepare_link(root: Path, target: str) -> Prepared:
    """Prune and place one target's inputs from Splat's linker script, which it only reads."""
    root = Path(root).resolve()
    target = normalize_target_id(target).value
    manifest_path = root / CONFIG / target / "target.toml"
    if not (root / CONFIG / target / "splat.yaml").is_file():
        raise ValueError(f"unknown target: {target}")
    manifest = load_target_manifest(manifest_path, root=root, target=target)
    tmap = target_map.load_target(root, manifest)
    exact_units = frozenset(
        unit.name
        for unit in tmap.reviewed_code
        if status_model.unit_state(unit) == "exact"
    )
    placements = tuple(
        placement for rows in manifest.section_placements.values() for placement in rows
    )
    placed = {placement.function for placement in placements}
    sources = tuple(
        unit.source
        for unit in tmap.reviewed_code
        if unit.vaddr in placed and unit.source is not None
    )

    linker_script = root / BUILD / ASM / target / "linker.ld"
    original = linker_script.read_text(encoding="utf-8")
    updated, wrappers = _rewrite_placements(
        original,
        placements,
        exact_units,
        {unit.vaddr: unit.name for unit in tmap.reviewed_code},
        manifest.binary,
        parse_splat_layout(root / manifest.splat, manifest.load_address).image_base,
        Path(BUILD) / "p2" / target / "placements",
    )
    for source, text in wrappers.items():
        write_if_changed(root / source, text)
    return Prepared(updated, _object_paths(updated), sources)


def rewrite(
    text: str, replacements: dict[int, str], drop: frozenset[int] = frozenset()
) -> str:
    """Apply input-line replacements and remove the selected line numbers."""
    lines = text.splitlines(keepends=True)
    for number, replacement in replacements.items():
        lines[number - 1] = f"        {replacement};\n"
    for number in drop:
        lines[number - 1] = "\n"
    return "".join(lines)


def prune_linker_script(
    text: str, placements: dict[tuple[str, str], int]
) -> tuple[str, int]:
    """Remove duplicate input selectors for reviewed section placements."""
    dropped = shadowed(text, placements)
    return rewrite(text, {}, dropped), len(dropped)
