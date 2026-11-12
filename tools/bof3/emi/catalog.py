"""Verify each reviewed EMI target against the extracted disc and copy its payload."""

from __future__ import annotations

import os
import re
import tempfile
from pathlib import Path
from typing import TYPE_CHECKING, Any

from bof3.core.binio import u32
from bof3.core.hashing import file_sha256
from bof3.core.io import read_json
from bof3.core.paths import BUILD
from bof3.resolve import load_target_manifests, normalize_target_id

if TYPE_CHECKING:
    from bof3.resolve.manifests import _CompanionOverlay

TARGET_RE = re.compile(r"^(?P<archive>.+?)(?:\.EMI)?#(?P<slot>\d+)$", re.IGNORECASE)
AUDIO_TYPES = {6, 7, 8, 10}


def _split_id(identifier: str) -> tuple[str, int]:
    """Return ``(archive_id, slot)`` for a disc id or an EMI target id."""
    try:
        normalized = normalize_target_id(identifier)
    except ValueError:
        normalized = None
    if normalized is not None and normalized.value.startswith("emi/"):
        _, family, archive, slot = normalized.value.split("/", 3)
        return f"{family}/{archive}".upper(), int(slot)
    match = TARGET_RE.fullmatch(identifier.replace("\\", "/"))
    if match is None:
        raise ValueError("entry must look like BIN/BATTLE/BATTLE.EMI#3")
    archive = match.group("archive").removesuffix(".EMI")
    archive = archive[4:] if archive.upper().startswith("BIN/") else archive
    return archive.upper(), int(match.group("slot"))


def _payload_kind(entry_type: int, load_address: int, size: int) -> str:
    if entry_type == 3:
        return "image"
    if entry_type in AUDIO_TYPES:
        return "audio"
    if (
        entry_type == 0
        and 0x80033000 <= load_address <= 0x8003AFFF
        and size in {0x40, 0x200, 0x400, 0x1000}
    ):
        return "image"
    return "ram" if entry_type == 0 else "unresolved"


def entry_for(root: Path, identifier: str) -> dict[str, Any]:
    """Return the extracted disc entry an identifier names."""
    archive_id, slot = _split_id(identifier)
    folder = root / BUILD / "disc" / "BIN" / archive_id
    manifest = folder / "emi.json"
    if not manifest.is_file():
        raise ValueError(f"missing extracted EMI archive: {manifest}")
    entries = read_json(manifest).get("entries", [])
    matches = [
        raw
        for raw in entries
        if isinstance(raw, dict) and int(raw.get("index") or 0) == slot
    ]
    if len(matches) != 1:
        raise ValueError(
            f"expected one extracted EMI entry for {identifier}; found {len(matches)}"
        )
    raw = matches[0]
    payload = folder / str(raw.get("name") or f"{slot}.bin")
    if not payload.is_file():
        raise ValueError(f"missing extracted EMI payload for {identifier}: {payload}")
    entry_type = int(raw.get("type") or 0)
    load_address = int(raw.get("ram_ptr") or 0)
    size = payload.stat().st_size
    return {
        "payload_path": payload,
        "load_address": load_address,
        "size": size,
        "payload_kind": _payload_kind(entry_type, load_address, size),
    }


def _jal_target(word: int, caller_address: int) -> int | None:
    if word >> 26 != 3:
        return None
    return ((caller_address + 4) & 0xF0000000) | ((word & 0x03FFFFFF) << 2)


def _relation_entry(
    *, caller: str, companion: _CompanionOverlay, calls: list[dict[str, int]]
) -> dict[str, Any]:
    return {
        "caller": caller,
        "companion": companion.target.value,
        "disc_id": companion.disc_id,
        "payload_sha256": companion.payload_sha256,
        "load_address": companion.load_address,
        "size": companion.size,
        "static_calls": calls,
        "evidence": companion.evidence,
    }


def verify_companion_relations(root: Path) -> list[dict[str, Any]]:
    """Return declared companion calls whose disc identity and call bytes agree.

    It establishes that the bytes match, not the ABI or ownership.
    """
    relations: list[dict[str, Any]] = []
    for manifest in load_target_manifests(root).values():
        for companion in manifest.companions:
            caller = entry_for(root, manifest.disc_id)
            target = entry_for(root, companion.disc_id)
            if (
                file_sha256(Path(target["payload_path"])) != companion.payload_sha256
                or int(target["load_address"]) != companion.load_address
                or int(target["size"]) != companion.size
            ):
                raise ValueError(
                    f"companion disc identity mismatch: {manifest.id.value} -> "
                    f"{companion.target.value}"
                )
            caller_start = int(caller["load_address"])
            caller_size = int(caller["size"])
            if manifest.load_address != caller_start:
                raise ValueError(
                    f"caller disc load address mismatch: {manifest.id.value}"
                )
            if target["payload_kind"] != "ram":
                raise ValueError(
                    f"companion is not a RAM payload: {companion.target.value}"
                )
            payload = Path(caller["payload_path"]).read_bytes()
            calls: list[dict[str, int]] = []
            for call in companion.static_calls:
                offset = call.caller_address - caller_start
                if offset < 0 or offset + 4 > caller_size:
                    raise ValueError(
                        f"companion call outside caller payload: {manifest.id.value}"
                    )
                word = u32(payload, offset)
                if _jal_target(word, call.caller_address) != call.target_address:
                    raise ValueError(
                        f"companion call bytes differ: {manifest.id.value} at "
                        f"0x{call.caller_address:08X}"
                    )
                calls.append(
                    {
                        "caller_address": call.caller_address,
                        "target_address": call.target_address,
                    }
                )
            relations.append(
                _relation_entry(
                    caller=manifest.id.value, companion=companion, calls=calls
                )
            )
    return sorted(relations, key=lambda item: (item["caller"], item["companion"]))


def verify_copy_relations(root: Path) -> list[dict[str, Any]]:
    """Return declared copies whose disc payload agrees with their source.

    The disc entry a copy names must carry the source's payload bytes at the
    pinned base and size; a matching identity alone never makes a program a
    copy. Copy targets and their config are specified in docs/toolchain.md#copy-targets.
    """
    relations: list[dict[str, Any]] = []
    for manifest in load_target_manifests(root).values():
        if not manifest.copies:
            continue
        source = entry_for(root, manifest.disc_id)
        source_hash = file_sha256(Path(source["payload_path"]))
        for copy in manifest.copies:
            entry = entry_for(root, copy.disc_id)
            digest = file_sha256(Path(entry["payload_path"]))
            if digest != copy.payload_sha256 or digest != source_hash:
                raise ValueError(
                    f"copy payload differs from its source: {copy.disc_id}"
                )
            if (
                int(entry["load_address"]) != copy.load_address
                or copy.load_address != manifest.load_address
            ):
                raise ValueError(
                    f"copy load address differs from its source: {copy.disc_id}"
                )
            if int(entry["size"]) != copy.size:
                raise ValueError(
                    f"copy size differs from its pinned size: {copy.disc_id}"
                )
            relations.append(
                {
                    "source": manifest.id.value,
                    "copy": copy.target.value,
                    "disc_id": copy.disc_id,
                    "payload_sha256": digest,
                    "load_address": copy.load_address,
                    "size": copy.size,
                }
            )
    return sorted(relations, key=lambda item: (item["source"], item["copy"]))


def _write_new(path: Path, content: bytes) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.exists():
        raise ValueError(f"refusing to overwrite: {path}")
    descriptor, temporary_name = tempfile.mkstemp(
        dir=path.parent, prefix=f".{path.name}."
    )
    temporary = Path(temporary_name)
    try:
        with os.fdopen(descriptor, "wb") as stream:
            stream.write(content)
            stream.flush()
            os.fsync(stream.fileno())
        os.link(temporary, path)
    finally:
        temporary.unlink(missing_ok=True)


def materialize_reviewed_targets(*, root: Path) -> list[Path]:
    """Copy each reviewed EMI target's payload from the extracted disc."""
    verify_companion_relations(root)
    verify_copy_relations(root)
    images: list[Path] = []
    for manifest in sorted(
        load_target_manifests(root).values(), key=lambda item: item.id.value
    ):
        if manifest.kind != "emi":
            continue
        entry = entry_for(root, manifest.disc_id)
        if manifest.load_address != int(entry["load_address"]):
            raise ValueError(
                f"load address differs from {manifest.disc_id}: "
                f"manifest=0x{manifest.load_address:08X}, "
                f"payload=0x{int(entry['load_address']):08X}"
            )
        image = root / manifest.binary
        if not image.is_file():
            _write_new(image, Path(entry["payload_path"]).read_bytes())
        images.append(image)
    return images
