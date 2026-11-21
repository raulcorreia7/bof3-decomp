"""The checkout and per-run caches the symbol verbs share."""

from __future__ import annotations

from collections.abc import Callable
from dataclasses import dataclass, field
from pathlib import Path
from typing import TYPE_CHECKING

from bof3.adapters.git import git
from bof3.core.paths import ROOT
from bof3.errors import SymbolError
from bof3.resolve.ids import source_folder

if TYPE_CHECKING:
    from bof3.symbols.assembly import Assembly
    from bof3.symbols.probe import Layout


@dataclass
class Context:
    """The checkout and the per-run caches the verbs share."""

    root: Path = ROOT
    layouts: dict[str, Layout | None] = field(default_factory=dict)
    layout_index: dict[str, dict] | None = None
    spans: dict[str, dict[int, int]] = field(default_factory=dict)
    ranges: dict[str, tuple[int, int] | None] = field(default_factory=dict)
    value_shared: dict = field(default_factory=dict)
    value_index: dict[str, dict] = field(default_factory=dict)
    value_views: list[tuple[str, str, str]] = field(default_factory=list)
    asm_functions: dict[str, list] = field(default_factory=dict)
    assembly: Assembly | None = None
    extent_rows: list[dict] | None = None

    def git(
        self, *args: str, check: bool = True, env: dict[str, str] | None = None
    ) -> str:
        return git(*args, root=self.root, check=check, env=env)

    @property
    def layout_cache(self) -> Path:
        return self.root / "build/symbol-layouts.json"

    @property
    def xref_cache(self) -> Path:
        return self.root / "build/symbol-xrefs"

    @property
    def asm_root(self) -> Path:
        return self.root / "build/asm"


@dataclass(frozen=True)
class Table:
    """Rows a verb found: ``keys`` (space-separated) name the JSON fields, ``heads`` and ``cells`` the text view."""

    keys: str
    rows: list[dict]
    notes: tuple[str, ...] = ()
    heads: str | None = None
    cells: Callable[[dict], list[str]] | None = None


RESIDENT = ("exe/slus_004_22", "emi/etc/game/00")


DEFAULT_SCOPE = ("src", "include", "config", "docs", "asm")


HISTORY = (
    "config/attempts.jsonl"  # failed-attempt rows keep the names they were written with
)


def grep_files(ctx: Context, word: str, scope: list[str]) -> list[str]:
    """Return the tracked files under ``scope`` that hold ``word`` as a whole word."""
    names = ctx.git(
        "grep",
        "-l",
        "-z",
        "-w",
        "-e",
        word,
        "--",
        *scope,
        f":(exclude){HISTORY}",
        check=False,
    )
    return [name for name in names.split("\0") if name]


def tables_with(text: str, name: str) -> list[str]:
    """Return the images whose table has a row ``name``."""
    images, image = [], ""
    for line in text.split("\n"):
        if line.startswith('["'):
            image = line[2:-2]
        elif line.startswith(name + " = "):
            images.append(image)
    return images


def local_scope(ctx: Context, images: list[str]) -> list[str]:
    """Return the folders that belong to the images."""
    folders = [
        f
        for image in images
        for f in (f"src/{source_folder(image)}", f"config/{image}")
    ]
    missing = [f for f in folders if not (ctx.root / f).is_dir()]
    if missing:
        raise SymbolError(f"symbol: no such folder {', '.join(missing)}")
    return folders
