"""Addresses carried by Splat's default symbol names."""

from __future__ import annotations

import re

_NAME_SUFFIX = re.compile(r"(?:func|D|jtbl)_([0-9A-Fa-f]{8})$")


# Splat names a jump table inside a function `jtbl_<TABLE>_<FUNCTION NAME>`.
_JUMP_TABLE_OF_FUNCTION = re.compile(r"(?:^|_)jtbl_([0-9A-Fa-f]{8})_[A-Za-z_]\w*$")


def suffix_address(name: str) -> int | None:
    """Address of a canonical name, also when an overlay prefixes it (``AREA_D_80149333``)."""
    match = _JUMP_TABLE_OF_FUNCTION.search(name) or _NAME_SUFFIX.search(name)
    return int(match[1], 16) if match else None
