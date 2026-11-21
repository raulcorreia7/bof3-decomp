"""Read ``git diff`` text: the lines a change adds and the paths it renames. Pure."""

from __future__ import annotations

import re
from collections.abc import Iterator


def added_lines(diff: str) -> Iterator[tuple[str, int, str]]:
    """Yield (path, line, text) for each line a ``-U0`` diff adds."""
    path, line = "", 0
    for row in diff.splitlines():
        if row.startswith("+++ b/"):
            path = row[6:]
        elif row.startswith("@@"):
            m = re.search(r"\+(\d+)", row)
            line = int(m.group(1)) if m else 0
        elif row.startswith("+") and not row.startswith("+++"):
            yield path, line, row[1:]
            line += 1
        elif row.startswith(" "):
            line += 1


def renames(name_status: str) -> dict[str, str]:
    """Map each new path of a ``--name-status -M`` listing to the path it was renamed from."""
    moved: dict[str, str] = {}
    for line in name_status.splitlines():
        fields = line.split("\t")
        if fields[0].startswith("R") and len(fields) == 3:
            moved[fields[2]] = fields[1]
    return moved
