"""SHA-256 helpers."""

from __future__ import annotations

import hashlib
from pathlib import Path


def sha256(data: bytes) -> str:
    return hashlib.sha256(data).hexdigest()


def file_digest(path: Path, algorithm: str) -> str:
    """The hex digest of the file at ``path``."""
    with path.open("rb") as stream:
        return hashlib.file_digest(stream, algorithm).hexdigest()
