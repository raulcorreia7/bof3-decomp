"""TOML-backed target manifests."""

from __future__ import annotations

import os
import re
import stat
import tomllib
from dataclasses import dataclass, field
from pathlib import Path
from typing import Any

from bof3.core.io import is_safe_relative_path
from bof3.resolve.ids import (
    TargetId,
    normalize_target_id,
    shipped_disc_id,
)
from bof3.resolve.layout import splat_facts

_SHA256 = re.compile(r"[0-9a-f]{64}")
_LOAD_ADDRESS_MIN = 0x80000000
_LOAD_ADDRESS_MAX = 0x80200000
#: Target identity is the folder id plus the layout; a manifest may not restate it.
_DERIVED_KEYS = frozenset(
    {"schema", "id", "disc_id", "kind", "binary", "splat", "load_address"}
)


class ManifestPathError(ValueError):
    """A manifest path failed lexical relative-path validation."""


@dataclass(frozen=True)
class SectionPlacement:
    function: int
    section: str
    address: int
    size: int


@dataclass(frozen=True)
class _CompanionStaticCall:
    caller_address: int
    target_address: int


@dataclass(frozen=True)
class _CompanionAbi:
    target_address: int
    prototype: str
    evidence: str


@dataclass(frozen=True)
class _CompanionOverlay:
    target: TargetId
    disc_id: str
    payload_sha256: str
    load_address: int
    size: int
    static_calls: tuple[_CompanionStaticCall, ...]
    evidence: str
    abi: _CompanionAbi | None = None


@dataclass(frozen=True)
class CopyOverlay:
    """A disc entry whose payload is this target's payload, byte for byte.

    A copy reuses the declaring target's sources and link; it owns no source
    directory of its own. See docs/toolchain.md#copy-targets.
    """

    target: TargetId
    disc_id: str
    payload_sha256: str
    load_address: int
    size: int


@dataclass(frozen=True)
class TargetManifest:
    id: TargetId
    disc_id: str
    kind: str
    source_dir: str
    binary: str
    splat: str
    load_address: int
    section_placements: dict[int, tuple[SectionPlacement, ...]] = field(
        default_factory=dict
    )
    companions: tuple[_CompanionOverlay, ...] = ()
    copies: tuple[CopyOverlay, ...] = ()

    def __post_init__(self) -> None:
        if self.kind not in {"executable", "emi"}:
            raise ValueError(f"unsupported target kind: {self.kind}")
        if self.companions and self.kind != "emi":
            raise ValueError("only EMI targets may declare companion overlays")
        if self.copies and self.kind != "emi":
            raise ValueError("only EMI targets may declare copy payloads")


def _load_toml(path: Path) -> dict[str, Any]:
    _validate_manifest_path(path)
    flags = os.O_RDONLY | os.O_CLOEXEC | os.O_NOFOLLOW
    descriptor = os.open(path, flags)
    try:
        if not stat.S_ISREG(os.fstat(descriptor).st_mode):
            raise ValueError(f"target manifest is not a regular file: {path}")
        with os.fdopen(descriptor, "rb") as stream:
            descriptor = -1
            return tomllib.load(stream)
    finally:
        if descriptor >= 0:
            os.close(descriptor)


def _validate_path_components(path: Path, *, leaf_directory: bool) -> bool:
    """Check every existing path component without following symlinks."""
    candidate = path if path.is_absolute() else Path.cwd() / path
    current = Path(candidate.anchor)
    parts = candidate.parts[1:]
    for index, part in enumerate(parts):
        current /= part
        try:
            result = os.lstat(current)
        except FileNotFoundError:
            return False
        except OSError as exc:
            raise ManifestPathError(f"cannot inspect manifest path: {path}") from exc
        if stat.S_ISLNK(result.st_mode):
            raise ManifestPathError(f"symlink is not allowed in manifest path: {path}")
        is_leaf = index == len(parts) - 1
        if not is_leaf and not stat.S_ISDIR(result.st_mode):
            raise ManifestPathError(f"manifest parent is not a directory: {path}")
        if is_leaf:
            expected = (
                stat.S_ISDIR(result.st_mode)
                if leaf_directory
                else stat.S_ISREG(result.st_mode)
            )
            if not expected:
                kind = "directory" if leaf_directory else "regular file"
                raise ManifestPathError(f"manifest path is not a {kind}: {path}")
    return True


def _validate_manifest_path(path: Path) -> None:
    _validate_path_components(path, leaf_directory=False)


def _validate_manifest_directory(path: Path) -> bool:
    return _validate_path_components(path, leaf_directory=True)


def _stat_stamp(result: os.stat_result) -> tuple[int, int, int, int]:
    return (
        result.st_ino,
        stat.S_IFMT(result.st_mode),
        result.st_mtime_ns,
        result.st_size,
    )


def _splat_paths(directory: Path) -> tuple[Path, ...]:
    """Return every ``config/**/splat.yaml``, sorted, refusing symlinks."""
    pending = [directory]
    manifests: list[Path] = []
    while pending:
        current = pending.pop()
        before = os.lstat(current)
        if stat.S_ISLNK(before.st_mode) or not stat.S_ISDIR(before.st_mode):
            raise ManifestPathError(f"layout parent is not a directory: {current}")
        try:
            with os.scandir(current) as iterator:
                entries = sorted(iterator, key=lambda entry: entry.name.encode("utf-8"))
                for entry in entries:
                    path = Path(entry.path)
                    result = os.lstat(path)
                    if stat.S_ISLNK(result.st_mode):
                        raise ManifestPathError(
                            f"symlink is not allowed in config tree: {path}"
                        )
                    if stat.S_ISDIR(result.st_mode):
                        pending.append(path)
                    elif entry.name == "splat.yaml":
                        if not stat.S_ISREG(result.st_mode):
                            raise ManifestPathError(
                                f"layout is not a regular file: {path}"
                            )
                        manifests.append(path)
        except ManifestPathError:
            raise
        except OSError as exc:
            raise ManifestPathError(f"cannot enumerate config tree: {current}") from exc
        try:
            after = os.lstat(current)
        except OSError as exc:
            raise ManifestPathError(
                f"cannot revalidate config tree: {current}"
            ) from exc
        if _stat_stamp(before) != _stat_stamp(after):
            raise ManifestPathError(
                f"config directory changed while reading: {current}"
            )
    return tuple(sorted(manifests, key=lambda path: path.as_posix().encode("utf-8")))


def _load_optional_toml(path: Path) -> dict[str, Any]:
    """Return one optional ``target.toml``, or an empty document when it is absent."""
    if path.is_file():
        return _load_toml(path)
    _validate_manifest_directory(path.parent)
    return {}


def _manifest_path(value: object, label: str, path: Path) -> str:
    if not is_safe_relative_path(value):
        raise ManifestPathError(f"invalid {label} path in {path}")
    return value


def _load_address(value: object, path: Path) -> int:
    if type(value) is not int:
        raise ValueError(f"load_address must be a TOML integer in {path}")
    if not _LOAD_ADDRESS_MIN <= value < _LOAD_ADDRESS_MAX or value % 4:
        raise ValueError(
            f"load_address is outside the aligned PSX load range in {path}"
        )
    return value


def _toml_integer(value: object, label: str) -> int:
    if type(value) is not int:
        raise ValueError(f"{label} must be a TOML integer")
    return value


def _parse_companions(
    raw: dict[str, Any], caller: TargetId
) -> tuple[_CompanionOverlay, ...]:
    values = raw.get("companion_overlays", [])
    if not isinstance(values, list):
        raise ValueError("companion_overlays must be an array of tables")
    companions: list[_CompanionOverlay] = []
    seen: set[str] = set()
    for value in values:
        if not isinstance(value, dict):
            raise ValueError("companion overlay must be a table")
        target = normalize_target_id(str(value["target"]))
        disc_id = str(value["disc_id"])
        if target.kind != "emi" or normalize_target_id(disc_id).value != target.value:
            raise ValueError(f"invalid companion overlay identity: {disc_id}")
        if target.value == caller.value:
            raise ValueError(
                f"companion overlay cannot reference itself: {target.value}"
            )
        if target.value in seen:
            raise ValueError(f"duplicate companion overlay: {target.value}")
        seen.add(target.value)
        digest = str(value["payload_sha256"])
        if _SHA256.fullmatch(digest) is None:
            raise ValueError(f"invalid companion payload SHA-256: {target.value}")
        load_address = _toml_integer(value["load_address"], "companion load_address")
        size = _toml_integer(value["size"], "companion size")
        if load_address % 4 or not 0x80000000 <= load_address < 0x80200000:
            raise ValueError(f"invalid companion load address: {target.value}")
        if size <= 0 or load_address + size > 0x80200000:
            raise ValueError(f"invalid companion payload size: {target.value}")
        calls = value.get("static_calls", [])
        if not isinstance(calls, list) or not calls:
            raise ValueError(f"missing companion static calls: {target.value}")
        static_calls: list[_CompanionStaticCall] = []
        seen_calls: set[tuple[int, int]] = set()
        for call in calls:
            if not isinstance(call, dict):
                raise ValueError(f"invalid companion static call: {target.value}")
            caller_address = _toml_integer(
                call["caller_address"], "companion caller_address"
            )
            target_address = _toml_integer(
                call["target_address"], "companion target_address"
            )
            key = (caller_address, target_address)
            if caller_address % 4 or target_address % 4:
                raise ValueError(f"unaligned companion static call: {target.value}")
            if not load_address <= target_address < load_address + size:
                raise ValueError(f"companion call outside payload: {target.value}")
            if key in seen_calls:
                raise ValueError(f"duplicate companion static call: {target.value}")
            seen_calls.add(key)
            static_calls.append(_CompanionStaticCall(*key))
        evidence = str(value["evidence"]).strip()
        if not evidence:
            raise ValueError(f"missing companion evidence: {target.value}")
        abi_raw = value.get("abi")
        abi = None
        if abi_raw is not None:
            if not isinstance(abi_raw, dict):
                raise ValueError(f"invalid companion ABI: {target.value}")
            target_address = _toml_integer(
                abi_raw.get("target_address", 0), "companion ABI target_address"
            )
            prototype = str(abi_raw.get("prototype", "")).strip()
            abi_evidence = str(abi_raw.get("evidence", "")).strip()
            call_targets = {call.target_address for call in static_calls}
            if target_address not in call_targets or not prototype or not abi_evidence:
                raise ValueError(f"missing companion ABI evidence: {target.value}")
            abi = _CompanionAbi(target_address, prototype, abi_evidence)
        companions.append(
            _CompanionOverlay(
                target=target,
                disc_id=disc_id,
                payload_sha256=digest,
                load_address=load_address,
                size=size,
                static_calls=tuple(static_calls),
                evidence=evidence,
                abi=abi,
            )
        )
    return tuple(companions)


def _validate_companions(manifests: dict[str, TargetManifest]) -> None:
    for manifest in manifests.values():
        for companion in manifest.companions:
            target = manifests.get(companion.target.value)
            if target is None:
                raise ValueError(f"unknown companion overlay: {companion.target.value}")
            if (
                target.kind != "emi"
                or target.disc_id != companion.disc_id
                or target.load_address != companion.load_address
            ):
                raise ValueError(
                    f"companion overlay identity mismatch: {companion.target.value}"
                )


def _parse_copies(
    raw: dict[str, Any], caller: TargetId, source_load_address: int
) -> tuple[CopyOverlay, ...]:
    """Parse the byte-identical disc entries that reuse this target's sources."""
    values = raw.get("copies", [])
    if not isinstance(values, list):
        raise ValueError("copies must be an array of tables")
    copies: list[CopyOverlay] = []
    seen: set[str] = set()
    for value in values:
        if not isinstance(value, dict):
            raise ValueError("copy must be a table")
        disc_id = str(value["disc_id"])
        target = normalize_target_id(disc_id)
        if target.kind != "emi":
            raise ValueError(f"invalid copy target: {disc_id}")
        if target.value == caller.value:
            raise ValueError(f"copy cannot reference its own entry: {target.value}")
        if target.value in seen:
            raise ValueError(f"duplicate copy target: {target.value}")
        seen.add(target.value)
        digest = str(value["payload_sha256"])
        if _SHA256.fullmatch(digest) is None:
            raise ValueError(f"invalid copy payload SHA-256: {target.value}")
        load_address = _toml_integer(value["load_address"], "copy load_address")
        if (
            load_address % 4
            or not _LOAD_ADDRESS_MIN <= load_address < _LOAD_ADDRESS_MAX
        ):
            raise ValueError(f"invalid copy load address: {target.value}")
        if load_address != source_load_address:
            raise ValueError(
                f"copy load address differs from its source: {target.value}"
            )
        size = _toml_integer(value["size"], "copy size")
        if size <= 0 or load_address + size > _LOAD_ADDRESS_MAX:
            raise ValueError(f"invalid copy payload size: {target.value}")
        copies.append(
            CopyOverlay(
                target=target,
                disc_id=disc_id,
                payload_sha256=digest,
                load_address=load_address,
                size=size,
            )
        )
    return tuple(copies)


def _validate_copies(manifests: dict[str, TargetManifest]) -> None:
    """A copy keeps its own identity: one declaring owner per copy, never a target."""
    owners: dict[str, str] = {}
    for manifest in manifests.values():
        for copy in manifest.copies:
            if copy.target.value in manifests:
                raise ValueError(
                    f"copy target is a configured target: {copy.target.value}"
                )
            owner = owners.get(copy.target.value)
            if owner is not None:
                raise ValueError(
                    f"duplicate copy target {copy.target.value}: "
                    f"{owner} and {manifest.id.value}"
                )
            owners[copy.target.value] = manifest.id.value


def _parse_target_manifest(path: Path, target_id: TargetId) -> TargetManifest:
    """Parse one target's optional ``target.toml`` and derive its identity."""
    raw = _load_optional_toml(path)
    stale = raw.keys() & _DERIVED_KEYS
    if stale:
        raise ValueError(
            f"target manifest restates derived fields {sorted(stale)}: {path}"
        )
    try:
        facts = splat_facts(path.parent / "splat.yaml")
    except (OSError, ValueError) as exc:
        raise ValueError(f"cannot read the target layout {path.parent}: {exc}") from exc

    sdk = raw.get("sdk", {})
    if not isinstance(sdk, dict):
        raise ValueError(f"sdk must be a table in {path}")
    if "surface" in sdk:
        raise ValueError(f"sdk.surface is derived from the link; remove it from {path}")

    matching = raw.get("matching", {})
    if not isinstance(matching, dict):
        raise ValueError(f"matching must be a table in {path}")
    raw_placements = matching.get("section_placements", [])
    if not isinstance(raw_placements, list):
        raise ValueError(f"matching.section_placements must be an array in {path}")
    placements: dict[int, list[SectionPlacement]] = {}
    seen_placements: set[tuple[int, str]] = set()
    for value in raw_placements:
        if not isinstance(value, dict):
            raise ValueError(f"matching section placement must be a table in {path}")
        try:
            placement = SectionPlacement(
                function=int(value["function"]),
                section=str(value["section"]),
                address=int(value["address"]),
                size=int(value["size"]),
            )
        except (KeyError, TypeError, ValueError) as exc:
            raise ValueError(f"invalid matching section placement in {path}") from exc
        key = (placement.function, placement.section)
        if not re.fullmatch(r"\.[A-Za-z0-9_.]+", placement.section):
            raise ValueError(f"invalid matching section name: {placement.section}")
        if placement.function % 4 or placement.address % 4:
            raise ValueError("matching function and section addresses must be aligned")
        if placement.size <= 0:
            raise ValueError("matching section placement size must be positive")
        if key in seen_placements:
            raise ValueError(
                f"duplicate matching section placement: {placement.function:#x} "
                f"{placement.section}"
            )
        seen_placements.add(key)
        placements.setdefault(placement.function, []).append(placement)

    load_address = _load_address(facts.load_address, path)
    try:
        manifest = TargetManifest(
            id=target_id,
            disc_id=shipped_disc_id(target_id),
            kind=target_id.kind,
            source_dir=_manifest_path(facts.source_dir, "source_dir", path),
            binary=_manifest_path(facts.binary, "binary", path),
            splat=f"config/{target_id.value}/splat.yaml",
            load_address=load_address,
            section_placements={
                function: tuple(values) for function, values in placements.items()
            },
            companions=_parse_companions(raw, target_id),
            copies=_parse_copies(raw, target_id, load_address),
        )
    except ManifestPathError:
        raise
    except (KeyError, TypeError, ValueError) as exc:
        raise ValueError(f"invalid target manifest in {path}: {exc}") from exc
    return manifest


def _validate_section_placements(root: Path, manifest: TargetManifest) -> None:
    binary_path = root / manifest.binary
    if not binary_path.is_file():
        return
    target_end = manifest.load_address + binary_path.stat().st_size
    for values in manifest.section_placements.values():
        for placement in values:
            if not (
                manifest.load_address <= placement.function < target_end
                and manifest.load_address <= placement.address
                and placement.address + placement.size <= target_end
            ):
                raise ValueError(
                    f"matching section placement outside target {manifest.id.value}: "
                    f"{placement.section} at {placement.address:#x}"
                )


def load_target_manifest(path: Path, *, root: Path, target: str) -> TargetManifest:
    """Parse one target's optional ``target.toml`` and validate it against the tree.

    The target id comes from the caller (its ``config/<target>/`` folder); the
    layout and the derived fields come from that folder's ``splat.yaml``. An
    absent manifest means the defaults: no placements, copies, companions or
    PsyQ evidence.
    """
    target_id = normalize_target_id(target)
    manifest = _parse_target_manifest(Path(path), target_id)
    _validate_section_placements(Path(root), manifest)
    return manifest
