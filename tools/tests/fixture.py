"""Shared test helpers."""

import sys
from pathlib import Path

from bof3.adapters.config import split_tables, table_file


def put_symbols(root: Path, text: str) -> None:
    """Write `text` as the symbol tables of the tree at `root`, one file per image."""
    for image, table in split_tables(text).items():
        path = root / table_file(image)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(table)


def main(root: Path, argv: list[str]) -> int:
    """Run `tools/symbol.py` on the tree at `root`."""
    import symbol

    return symbol.main(argv, symbol.Context(root))


def patch(monkeypatch, name: str, replacement: object) -> None:
    """Replace `name` in every symbol module that holds it, as each imports it by name."""
    for module in list(sys.modules.values()):
        if module.__name__.startswith("bof3.symbols.") and hasattr(module, name):
            monkeypatch.setattr(module, name, replacement)
