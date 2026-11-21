"""The rows of ``config/symbols.toml``: parse the document, validate each row, reject overlaps.

Pure: the caller reads the file. A bad document or row is a :class:`LinkError`.
"""

from __future__ import annotations

import re
import tomllib
from typing import Any, NamedTuple

from bof3.core.paths import CONFIG

TABLE = f"{CONFIG}/symbols.toml"

_NAME = re.compile(r"^[A-Za-z_]\w*$")
_TYPE = re.compile(r"^[A-Za-z_][\w*]*$")
_KEYS = ("addr", "type", "size", "source", "alias")


class LinkError(Exception):
    """A symbol cannot be handled for certain; the message states the fix."""


class Entry(NamedTuple):
    """One table row."""

    name: str
    addr: int
    type: str = ""
    size: int = 0
    source: str = ""
    alias: bool = False

    @property
    def attributes(self) -> str:
        """The Splat attribute text of the row (no evidence, no link-only marks)."""
        parts = []
        if self.type:
            parts.append(f"type:{self.type}")
        if self.size:
            parts.append(f"size:0x{self.size:X}")
        return " ".join(parts)

    @property
    def address(self) -> int:
        """The row's address."""
        return self.addr

    @property
    def comment(self) -> str:
        """The row comment: attributes, alias and source."""
        parts = [self.attributes]
        if self.alias:
            parts.append("alias:true")
        if self.source:
            parts.append(f'source="{self.source}"')
        return " ".join(p for p in parts if p)


def _row_error(target: str, name: str, problem: str, fix: str) -> LinkError:
    return LinkError(f"{TABLE} [{target}] {name}: {problem}. {fix}")


def _entry(target: str, name: str, value: object) -> Entry:
    if not _NAME.match(name):
        raise _row_error(
            target, name, "the name is not a C identifier", "Rename the row."
        )
    if not isinstance(value, dict):
        raise _row_error(
            target,
            name,
            "the row is not an inline table",
            f"Write `{name} = {{ addr = 0x... }}`.",
        )
    unknown = sorted(set(value) - set(_KEYS))
    if unknown:
        raise _row_error(
            target, name, f"unknown key {unknown[0]!r}", f"Use only {', '.join(_KEYS)}."
        )
    addr = value.get("addr")
    if (
        not isinstance(addr, int)
        or isinstance(addr, bool)
        or not 0 <= addr <= 0xFFFFFFFF
    ):
        raise _row_error(
            target,
            name,
            "`addr` is missing or not a 32-bit integer",
            "Write `addr = 0x8015DF18`.",
        )
    size = value.get("size", 0)
    if not isinstance(size, int) or isinstance(size, bool) or size < 0:
        raise _row_error(
            target, name, "`size` is not a byte count", "Write `size = 0x10`."
        )
    type_ = value.get("type", "")
    if not isinstance(type_, str) or (type_ and not _TYPE.match(type_)):
        raise _row_error(
            target,
            name,
            "`type` is not one word",
            'Write `type = "func"` or a C type name.',
        )
    source = value.get("source", "")
    if not isinstance(source, str) or '"' in source or "\n" in source:
        raise _row_error(
            target,
            name,
            "`source` is not a one-line string without quotes",
            "Reword the evidence.",
        )
    alias = value.get("alias", False)
    if not isinstance(alias, bool):
        raise _row_error(
            target, name, "`alias` is not true or false", "Write `alias = true`."
        )
    return Entry(name, addr, type_, size, source, alias)


def overlaps(target: str, entries: list[Entry]) -> list[str]:
    """Return a message per row whose range overlaps an earlier row without a recorded reason."""
    problems = []
    ordered = sorted(entries, key=lambda e: e.addr)
    reach = 0
    holder = None
    for entry in ordered:
        if holder is not None and entry.addr < reach:
            if not (entry.alias or holder.alias):
                problems.append(
                    f"{TABLE} [{target}] {entry.name} (0x{entry.addr:08X}) overlaps {holder.name} "
                    f"(0x{holder.addr:08X}+0x{max(holder.size, 1):X}). Fix an address or size, or "
                    "mark the second name `alias = true` (a link-only name)."
                )
        end = entry.addr + max(entry.size, 1)
        if holder is None or end >= reach:
            reach, holder = end, entry
    return problems


def parse(text: str) -> dict[str, Any]:
    """Parse a ``symbols.toml`` document; a bad one is a :class:`LinkError`."""
    try:
        return tomllib.loads(text)
    except tomllib.TOMLDecodeError as error:
        raise LinkError(f"{TABLE}: {error}. Fix the line named above.") from None


def table_entries(target: str, rows: dict[str, Any]) -> list[Entry]:
    """Return one table's validated rows; a bad row is a :class:`LinkError`."""
    return [_entry(target, name, value) for name, value in rows.items()]
