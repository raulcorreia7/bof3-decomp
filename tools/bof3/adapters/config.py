"""Read and write the repository's TOML configuration."""

from __future__ import annotations

import re
import tomllib
from pathlib import Path
from typing import Any

from bof3.adapters.git import git
from bof3.core.paths import CONFIG
from bof3.symbols import SPLIT, parse

_TITLE = re.compile(r'^\["([^"]+)"\]', re.MULTILINE)


def table_file(image: str) -> str:
    return f"{SPLIT}/{image.replace('/', '+')}.toml"


def symbol_files(root: Path) -> list[Path]:
    return sorted((root / SPLIT).glob("*.toml"))


def symbols_text(root: Path, rev: str | None = None) -> str:
    """The symbol tables as one TOML text: the files of `config/symbols/`, at `rev` if given."""
    if rev is None:
        return "".join(p.read_text(encoding="utf-8") for p in symbol_files(root))
    names = git("ls-tree", "--name-only", rev, f"{SPLIT}/", root=root).split()
    return "".join(git("show", f"{rev}:{name}", root=root) for name in names)


def split_tables(text: str) -> dict[str, str]:
    """Each image's table text, without the header comment of the whole document."""
    titles = list(_TITLE.finditer(text))
    ends = [m.start() for m in titles[1:]] + [len(text)]
    return {
        m[1]: text[m.start() : end].rstrip() + "\n"
        for m, end in zip(titles, ends, strict=True)
    }


def symbol_edits(root: Path, text: str) -> dict[Path, str]:
    """The files whose content differs from the symbol tables `text`."""
    edits = {}
    for image, table in split_tables(text).items():
        path = root / table_file(image)
        if not path.is_file() or path.read_text(encoding="utf-8") != table:
            edits[path] = table
    return edits


def write_symbols(root: Path, text: str) -> None:
    """Write the symbol tables `text` back to where they live."""
    for path, contents in symbol_edits(root, text).items():
        path.parent.mkdir(exist_ok=True)
        path.write_text(contents, encoding="utf-8")


def read_symbols(root: Path) -> dict[str, Any]:
    return parse(symbols_text(root))


def read_link(root: Path) -> dict[str, Any]:
    return tomllib.loads((root / "config/link.toml").read_text(encoding="utf-8"))


def read_lines(path: Path, errors: str = "strict") -> list[str]:
    return path.read_text(encoding="utf-8", errors=errors).splitlines()


def has_splat(root: Path, target: str) -> bool:
    return (root / CONFIG / target / "splat.yaml").is_file()


def image_layout(root: Path, image: str):
    """The reviewed layout of an image's ``splat.yaml``, or None when it cannot be read."""
    from bof3.resolve.layout import parse_splat_layout, splat_facts

    path = root / CONFIG / image / "splat.yaml"
    if not path.is_file():
        return None
    try:
        return parse_splat_layout(path, splat_facts(path).load_address)
    except (OSError, ValueError, ImportError):
        return None


def manifest_layout(root: Path, manifest):
    """The reviewed layout of an image manifest."""
    from bof3.resolve.layout import parse_splat_layout

    return parse_splat_layout(root / manifest.splat, manifest.load_address)


def splat_owners(root: Path, target: str) -> list[str]:
    """The targets whose rows Splat reads for ``target``, in order."""
    from bof3.resolve.layout import read_splat

    _, document = read_splat(root / CONFIG / target / "splat.yaml")
    return list(document["symbol_owners"])


def splat_targets(root: Path) -> list[str]:
    """The targets that have a ``splat.yaml``, sorted by path."""
    folder = root / CONFIG
    return [
        p.parent.relative_to(folder).as_posix()
        for p in sorted(folder.rglob("splat.yaml"))
    ]
