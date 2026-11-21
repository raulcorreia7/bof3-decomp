"""Process-local memoization of parsed repository files."""

from __future__ import annotations

from collections.abc import Callable, Hashable, Iterable
from pathlib import Path
from typing import Any

_FILE_MEMO: dict[tuple, Any] = {}


def file_stamp(path: Path) -> tuple[int, int] | None:
    """``(mtime_ns, size)`` of ``path``, or None when it is missing."""
    try:
        stat = path.stat()
    except OSError:
        return None
    return (stat.st_mtime_ns, stat.st_size)


def file_memo[T](
    kind: str, paths: Iterable[Path], extra: Hashable, compute: Callable[[], T]
) -> T:
    """Process-local memo of ``compute()`` keyed on ``kind``, ``extra`` and the stamp of ``paths``."""
    paths = tuple(paths)
    key = (kind, extra, tuple((str(p), file_stamp(p)) for p in paths))
    try:
        return _FILE_MEMO[key]
    except KeyError:
        value = _FILE_MEMO[key] = compute()
        return value
