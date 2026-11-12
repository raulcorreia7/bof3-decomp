"""Target and function identity; :class:`TargetId` keeps the disc spelling for output."""

from __future__ import annotations

import glob
import os
import re
import unicodedata
from dataclasses import dataclass
from pathlib import Path

_EXE_NAMES = {
    "slus_004.22": "exe/slus_004_22",
    "slus_004_22": "exe/slus_004_22",
    "logo/logo.exe": "exe/logo",
    "logo.exe": "exe/logo",
}
_EXE_ID_RE = re.compile(r"^exe/(?P<name>[a-z0-9]+(?:[_-][a-z0-9]+)*)$", re.ASCII)
_EMI_ID_RE = re.compile(
    r"^emi/(?P<family>[a-z0-9]+(?:[_-][a-z0-9]+)*)/"
    r"(?P<archive>[a-z0-9]+(?:[_-][a-z0-9]+)*)/(?P<slot>[0-9]{2})$",
    re.ASCII,
)
_SHIPPED_EMI_RE = re.compile(
    r"^(?:bin/)?(?P<family>[a-z0-9]+(?:[_-][a-z0-9]+)*)/"
    r"(?P<archive>[a-z0-9]+(?:[_-][a-z0-9]+)*)\.emi#(?P<slot>[0-9]{1,2})$",
    re.IGNORECASE | re.ASCII,
)


def _reject_unsafe_text(value: str) -> None:
    """Reject text that must never be treated as a filesystem identity."""
    if not isinstance(value, str):
        raise ValueError("target identifier must be a string")
    for character in value:
        category = unicodedata.category(character)
        if category in {"Cc", "Zl", "Zp"} or 0xD800 <= ord(character) <= 0xDFFF:
            raise ValueError("target identifier contains a control or surrogate")
        if character == "\x00":
            raise ValueError("target identifier contains NUL")


def _emi_id(family: str, archive: str, slot: str, shipped: str) -> TargetId:
    """The one spelling of an EMI identity: ``emi/<family>/<archive>/<slot>``."""
    return TargetId(f"emi/{family.lower()}/{archive.lower()}/{int(slot):02d}", shipped)


def _canonical_emi(value: str, shipped: str) -> TargetId:
    match = _EMI_ID_RE.fullmatch(value)
    if match is None:
        raise ValueError(
            "canonical EMI target must be emi/<family>/<archive>/<two-digit slot>"
        )
    return _emi_id(
        match.group("family"), match.group("archive"), match.group("slot"), shipped
    )


def _canonical_exe(value: str, shipped: str) -> TargetId:
    normalized = value.replace(".", "_")
    if _EXE_ID_RE.fullmatch(normalized) is None:
        raise ValueError("canonical executable target must be exe/<safe-name>")
    return TargetId(normalized, shipped)


@dataclass(frozen=True)
class TargetId:
    """A normalized target plus the shipped identifier used to resolve it."""

    value: str
    shipped: str

    @property
    def kind(self) -> str:
        return "executable" if self.value.startswith("exe/") else "emi"

    def __str__(self) -> str:
        """Return the canonical target spelling."""
        return self.value


_SERIAL_RE = re.compile(r"^(?P<name>[a-z]+)_\d{3}_\d{2}$")


def shipped_disc_id(target: TargetId) -> str:
    """Return the disc spelling of a canonical target id.

    The executable name follows its serial, and an executable without one lives
    in its own folder: ``exe/slus_004_22`` -> ``SLUS_004.22``,
    ``exe/logo`` -> ``LOGO/LOGO.EXE``. An EMI entry is the archive path:
    ``emi/etc/game/00`` -> ``BIN/ETC/GAME.EMI#0``.
    """
    if target.kind == "executable":
        name = target.value.split("/", 1)[1]
        serial = _SERIAL_RE.fullmatch(name)
        if serial is not None:
            family, number, region = name.split("_")
            return f"{family.upper()}_{number}.{region}"
        return f"{name.upper()}/{name.upper()}.EXE"
    _, family, archive, slot = target.value.split("/")
    return f"BIN/{family.upper()}/{archive.upper()}.EMI#{int(slot)}"


#: Where an image's sources live under ``src/``, by disc family, archive or image. The most
#: specific key wins: ``family/archive/slot``, then ``family/archive``, then ``family``. An
#: image with no key lives in ``overlays/<family>``.
_SOURCE_ROOTS = {
    **{f"world0{n}": "overlays/area" for n in range(5)},
    "etc/game/00": "engine",
    "etc/game/01": "overlays/title",
    **{
        f"etc/{a}": "overlays/menu"
        for a in ("start", "shop", "sisyou", "shisu", "bate")
    },
    **{f"etc/commu0{n}": "overlays/commu" for n in range(6)},
}


def source_folder(target: str) -> str:
    """Return the folder under ``src/`` that holds a target's sources.

    The folder is a root plus the id's tail: ``emi/world02/area078/13`` ->
    ``overlays/area/area078/13``; ``emi/etc/game/00`` -> ``engine/game/00``;
    ``exe/slus_004_22`` -> ``engine/slus`` (the serial is dropped); ``exe/logo`` -> ``logo``.
    """
    parts = target.split("/")
    if parts[0] == "exe":
        serial = _SERIAL_RE.fullmatch(parts[1])
        name = serial["name"] if serial else parts[1]
        return f"engine/{name}" if name == "slus" else name
    _, family, archive, slot = parts
    for key in (f"{family}/{archive}/{slot}", f"{family}/{archive}", family):
        if key in _SOURCE_ROOTS:
            return f"{_SOURCE_ROOTS[key]}/{archive}/{slot}"
    return f"overlays/{family}/{archive}/{slot}"


def asm_dir(source: str | Path, root: str | Path) -> str | None:
    """Return the `ASM_DIR` of a source under `src/`: its image folder, or its hand folder.

    The image follows from the source folder: `src/engine/slus`, `src/logo`, and
    `.../<archive>/<slot>/<file>` for the one `emi/<family>/<archive>/<slot>` under `config/`.
    """
    parts = os.path.relpath(os.path.abspath(source), root).split(os.sep)
    if parts[0] != "src":
        return None
    if parts[1:3] == ["engine", "slus"]:
        target = "exe/slus_004_22"
    elif parts[1] == "logo":
        target = "exe/logo"
    elif len(parts) >= 5:
        found = glob.glob(f"{root}/config/emi/*/{parts[-3]}/{parts[-2]}/splat.yaml")
        if len(found) != 1:
            return None
        target = os.path.relpath(os.path.dirname(found[0]), f"{root}/config")
    else:
        return None
    stem = os.path.splitext(parts[-1])[0]
    hand = f"asm/{target}/hand"
    return hand if os.path.isfile(f"{root}/{hand}/{stem}.s") else f"asm/{target}"


def image_header(target: str) -> str:
    """Return the target's own header file name: ``battle_03.h``, ``slus.h``.

    The name is the archive and slot of the id: ``emi/battle/battle/03`` -> ``battle_03.h``;
    ``emi/etc/shop/00`` -> ``shop_00.h``; ``exe/slus_004_22`` -> ``slus.h``; ``exe/logo`` -> ``logo.h``.
    """
    parts = target.split("/")
    if parts[0] == "exe":
        serial = _SERIAL_RE.fullmatch(parts[1])
        return f"{serial['name'] if serial else parts[1]}.h"
    return f"{parts[-2]}_{parts[-1]}.h"


def _normalize_emi(raw: str) -> TargetId:
    match = _SHIPPED_EMI_RE.fullmatch(raw.replace("\\", "/"))
    if match is None:
        raise ValueError("EMI target must be family/archive.emi#N")
    return _emi_id(
        match.group("family"), match.group("archive"), match.group("slot"), raw
    )


def normalize_target_id(value: str) -> TargetId:
    """Normalize a shipped executable or EMI identifier."""
    _reject_unsafe_text(value)
    raw = value
    if not raw:
        raise ValueError("target identifier must not be empty")
    key = raw.lower()
    if key in _EXE_NAMES:
        return TargetId(_EXE_NAMES[key], raw)
    if "\\" not in raw and key.startswith("exe/") and raw == key:
        return _canonical_exe(key, raw)
    if "\\" not in raw and key.startswith("emi/") and raw == key:
        return _canonical_emi(key, raw)
    return _normalize_emi(raw)
