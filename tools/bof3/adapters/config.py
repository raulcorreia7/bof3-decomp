"""Read the repository's TOML configuration from disk."""

from __future__ import annotations

import tomllib
from pathlib import Path
from typing import Any

from bof3.symbols import TABLE, parse


def read_symbols(root: Path) -> dict[str, Any]:
    """Return the parsed ``config/symbols.toml``: image table -> name -> row."""
    return parse((root / TABLE).read_text(encoding="utf-8"))


def read_link(root: Path) -> dict[str, Any]:
    """Return the parsed ``config/link.toml``."""
    return tomllib.loads((root / "config/link.toml").read_text(encoding="utf-8"))
