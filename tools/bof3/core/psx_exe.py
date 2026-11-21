"""The PS-X EXE header: one reader for every tool that maps a retail image."""

from __future__ import annotations

import struct
from dataclasses import dataclass
from pathlib import Path

#: The header's signature, and the length the loader skips before the text.
MAGIC = b"PS-X EXE"
HEADER_SIZE = 0x800
#: The initial-PC offset; gp, the text load address and the text size follow it.
PC0_OFFSET = 0x10


@dataclass(frozen=True, slots=True)
class Header:
    """The header fields a tool needs, named after the format's own fields."""

    pc0: int
    load_address: int
    text_size: int


def parse(header: bytes) -> Header | None:
    """The header of the first ``HEADER_SIZE`` bytes of an image, or None."""
    if len(header) < HEADER_SIZE or header[: len(MAGIC)] != MAGIC:
        return None
    pc0, _gp, load_address, text_size = struct.unpack_from("<IIII", header, PC0_OFFSET)
    return Header(pc0, load_address, text_size)


def read(path: Path) -> Header | None:
    """The header of one image file, or None when it is missing or not a PS-X EXE."""
    try:
        with path.open("rb") as stream:
            return parse(stream.read(HEADER_SIZE))
    except OSError:
        return None


def text(path: Path) -> tuple[bytes, int] | None:
    """The text bytes and the load address of one image, or None when it is not one."""
    try:
        data = path.read_bytes()
    except OSError:
        return None
    header = parse(data[:HEADER_SIZE])
    if header is None:
        return None
    return data[HEADER_SIZE : HEADER_SIZE + header.text_size], header.load_address
