"""The disc manifest, ``config/disc.toml``: the version, the tracks and every file of the disc.

The manifest holds paths, sizes and hashes, never game data. Setup and ``tools/disc.py`` read
it to refuse a wrong dump and to name each extracted file that differs. The retail SHA-1 of
every code image lives in the build config (``config/<target>/splat.yaml``), the file the
build's ``check`` reads, and is not repeated here.
"""

from __future__ import annotations

import hashlib
import re
import tomllib
import zlib
from dataclasses import dataclass
from pathlib import Path

from bof3.errors import MissingInputError

MANIFEST = "config/disc.toml"
MEDIA = "inputs/external"
EXTRACTED = "build/disc"


@dataclass(frozen=True, slots=True)
class Digest:
    """Size and the three hashes the disc databases list."""

    size: int
    crc32: str
    md5: str
    sha1: str


def digest_file(path: Path) -> Digest:
    """Read ``path`` once and return its size, CRC32, MD5 and SHA-1."""
    md5, sha1, crc, size = hashlib.md5(usedforsecurity=False), hashlib.sha1(), 0, 0
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1 << 20), b""):
            md5.update(chunk)
            sha1.update(chunk)
            crc = zlib.crc32(chunk, crc)
            size += len(chunk)
    return Digest(size, f"{crc:08x}", md5.hexdigest(), sha1.hexdigest())


def sha1_file(path: Path) -> str:
    """Return the SHA-1 of ``path``."""
    sha1 = hashlib.sha1()
    with path.open("rb") as stream:
        for chunk in iter(lambda: stream.read(1 << 20), b""):
            sha1.update(chunk)
    return sha1.hexdigest()


def load_manifest(root: Path) -> dict:
    """Read ``config/disc.toml``."""
    path = root / MANIFEST
    if not path.is_file():
        raise MissingInputError(f"disc: {MANIFEST} is missing; restore it with git")
    with path.open("rb") as stream:
        return tomllib.load(stream)


def disc_set(media: Path) -> tuple[Path, list[Path]] | None:
    """Return the cue sheet and bins of the shallowest complete disc set under ``media``."""
    found = []
    for cue in sorted(media.rglob("*.cue")):
        text = cue.read_text(encoding="utf-8", errors="ignore")
        bins = [
            (cue.parent / name).resolve()
            for name in re.findall(r'^\s*FILE\s+"([^"]+)"', text, re.I | re.M)
        ]
        if bins and all(path.is_file() for path in bins):
            found.append((len(cue.relative_to(media).parts), cue, bins))
    return min(found, key=lambda item: item[:2])[1:] if found else None


def verify_tracks(manifest: dict, bins: list[Path]) -> list[str]:
    """Return one message per track that differs from the manifest."""
    tracks = manifest["disc"]["tracks"]
    if len(bins) != len(tracks):
        return [
            f"the cue sheet names {len(bins)} track file(s); the disc has {len(tracks)}"
        ]
    problems = []
    for want, path in zip(tracks, bins, strict=True):
        if path.stat().st_size != want["size"]:
            problems.append(
                f"{path.name}: size {path.stat().st_size}, expected {want['size']}"
            )
            continue
        got = sha1_file(path)
        if got != want["sha1"]:
            problems.append(f"{path.name}: SHA-1 {got}, expected {want['sha1']}")
    return problems


def verify_files(manifest: dict, folder: Path) -> list[str]:
    """Return one message per disc file under ``folder`` that is missing or differs."""
    problems = []
    for entry in manifest["iso"]["files"]:
        path = folder / entry["path"]
        if not path.is_file():
            problems.append(f"{entry['path']}: missing")
        elif path.stat().st_size != entry["size"]:
            problems.append(
                f"{entry['path']}: size {path.stat().st_size}, expected {entry['size']}"
            )
        elif sha1_file(path) != entry["sha1"]:
            problems.append(f"{entry['path']}: SHA-1 differs")
    return problems


def verify_images(root: Path) -> list[str]:
    """Return one message per extracted code image that differs from its ``splat.yaml`` SHA-1."""
    from bof3.resolve import load_target_manifests

    problems = []
    for _target, manifest in sorted(load_target_manifests(root).items()):
        wanted = re.search(r"^sha1:\s*(\w+)", (root / manifest.splat).read_text(), re.M)
        path = root / manifest.binary
        if wanted is None:
            problems.append(f"{manifest.splat}: no sha1")
        elif not path.is_file():
            problems.append(f"{manifest.binary}: missing")
        elif sha1_file(path) != wanted[1]:
            problems.append(f"{manifest.binary}: SHA-1 differs from {manifest.splat}")
    return problems


def _string(value: str) -> str:
    return '"' + value.replace("\\", "\\\\").replace('"', '\\"') + '"'


def _digest_keys(d: Digest) -> str:
    return f'size = {d.size}\ncrc32 = "{d.crc32}"\nmd5 = "{d.md5}"\nsha1 = "{d.sha1}"'


def render(
    *,
    title: str,
    region: str,
    serial: str,
    redump: str,
    cue: tuple[str, Digest],
    tracks: list[tuple[int, str, str, Digest]],
    files: list[tuple[str, int, int, str]],
) -> str:
    """Return ``config/disc.toml``: files are ``(path, lba, size, sha1)``."""
    out = [
        "# The retail disc this project builds against: version, tracks and every file.",
        "# Hashes, sizes and paths only. Generated by `tools/disc.py manifest`; do not edit.",
        "# A file's size and SHA-1 are those of the file `bof3 disc extract` writes; an XA stream",
        "# keeps its raw 2336-byte sectors. The retail SHA-1 of each code image is the `sha1` of its",
        "# config/<target>/splat.yaml.",
        "",
        "[disc]",
        f"title = {_string(title)}",
        f"region = {_string(region)}",
        f"serial = {_string(serial)}",
        f"redump = {_string(redump)}",
        "",
        "[disc.cue]",
        f"name = {_string(cue[0])}",
        _digest_keys(cue[1]),
        "",
    ]
    for number, name, kind, d in tracks:
        out += [
            "[[disc.tracks]]",
            f"number = {number}",
            f"name = {_string(name)}",
            f"type = {_string(kind)}",
            _digest_keys(d),
            "",
        ]
    out += ["[iso]", "files = ["]
    for path, lba, size, sha1 in files:
        out.append(
            f'  {{ path = {_string(path)}, lba = {lba}, size = {size}, sha1 = "{sha1}" }},'
        )
    out.append("]")
    return "\n".join(out) + "\n"
