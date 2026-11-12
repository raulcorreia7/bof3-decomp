"""Edit ``config/symbols.toml`` as text, keeping its layout: one table per image, rows by address."""

from __future__ import annotations

import re

_ADDR = re.compile(r"\baddr = 0x([0-9A-Fa-f]+)")


class SymtabError(ValueError):
    """The table cannot take the edit; the message says why."""


def header(image: str) -> str:
    """Return the table header line of ``image``."""
    return f'["{image}"]'


def format_row(
    name: str,
    addr: int,
    *,
    type: str | None = None,
    size: int | None = None,
    source: str | None = None,
    alias: bool = False,
) -> str:
    """Return one row in the table's key order: addr, type, size, source, alias."""
    keys = [f"addr = 0x{addr:08X}"]
    if type:
        keys.append(f'type = "{type}"')
    if size is not None:
        keys.append(f"size = 0x{size:X}")
    if source:
        keys.append(
            'source = "' + source.replace("\\", "\\\\").replace('"', '\\"') + '"'
        )
    if alias:
        keys.append("alias = true")
    return f"{name} = {{ {', '.join(keys)} }}"


def _section(lines: list[str], image: str) -> tuple[int, int] | None:
    """Return the ``[first row, end)`` line range of an image's table."""
    try:
        start = lines.index(header(image)) + 1
    except ValueError:
        return None
    end = start
    while end < len(lines) and not lines[end].startswith("["):
        end += 1
    return start, end


def has_row(text: str, image: str, name: str) -> bool:
    """Return True when the image's table has a row named ``name``."""
    lines = text.split("\n")
    span = _section(lines, image)
    return bool(span) and any(
        line.startswith(name + " = ") for line in lines[span[0] : span[1]]
    )


def add_row(text: str, image: str, name: str, row: str, addr: int) -> str:
    """Insert ``row`` into the image's table in address order; start the table if needed."""
    lines = text.split("\n")
    if has_row(text, image, name):
        raise SymtabError(f"[{image}] already has a row named {name}")
    if _section(lines, image) is None:
        heads = [k for k, line in enumerate(lines) if line.startswith('["')]
        at = next((k for k in heads if lines[k] > header(image)), len(lines))
        lines[at:at] = (
            [header(image), "", ""] if at < len(lines) else ["", header(image), ""]
        )
    start, end = _section(lines, image)  # type: ignore[misc]
    at = end
    for k in range(start, end):
        found = _ADDR.search(lines[k])
        if found and int(found[1], 16) > addr and lines[k].strip():
            at = k
            break
    else:
        while at > start and not lines[at - 1].strip():
            at -= 1
    lines.insert(at, row)
    return "\n".join(lines)


def remove_row(text: str, image: str, name: str) -> str | None:
    """Remove the row ``name`` of the image's table; None when it has no such row."""
    lines = text.split("\n")
    span = _section(lines, image)
    if span is None:
        return None
    for k in range(*span):
        if lines[k].startswith(name + " = "):
            del lines[k]
            return "\n".join(lines)
    return None


def rename_row(text: str, image: str, old: str, new: str) -> str | None:
    """Rename the row ``old`` of the image's table; None when it has no such row."""
    lines = text.split("\n")
    span = _section(lines, image)
    if span is None:
        return None
    if has_row(text, image, new):
        raise SymtabError(f"[{image}] already has a row named {new}")
    for k in range(*span):
        if lines[k].startswith(old + " = "):
            lines[k] = new + lines[k][len(old) :]
            return "\n".join(lines)
    return None
