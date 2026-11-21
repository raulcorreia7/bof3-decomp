"""Shared test helpers."""

from pathlib import Path

from bof3.adapters.config import split_tables, table_file


def put_symbols(root: Path, text: str) -> None:
    """Write `text` as the symbol tables of the tree at `root`, one file per image."""
    for image, table in split_tables(text).items():
        path = root / table_file(image)
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(table)
