"""Instruction counts and C declaration lookups for the try tools."""

from __future__ import annotations

import difflib
import re

from bof3.source.ctext import mask

JUMP_OPS = (2, 3)


def _norm(words: tuple[int, ...]) -> list[int]:
    return [-(w >> 26) if w >> 26 in JUMP_OPS else w for w in words]


def diff_count(template: tuple[int, ...], target: tuple[int, ...]) -> int:
    """Return how many instructions differ, ignoring jump targets."""
    a, b = _norm(template), _norm(target)
    matched = sum(
        m.size
        for m in difflib.SequenceMatcher(
            None, a, b, autojunk=False
        ).get_matching_blocks()
    )
    return max(len(a), len(b)) - matched


def statements(text: str) -> list[str]:
    """Return the top-level declaration statements of C text, one string each."""
    masked = mask(text)
    masked = re.sub(
        r"^[ \t]*#.*(?:\\\n.*)*$",
        lambda m: re.sub(r"[^\n]", " ", m.group(0)),
        masked,
        flags=re.M,
    )
    out, start, depth, body = [], 0, 0, False
    for i, ch in enumerate(masked):
        if ch == "{":
            if depth == 0:
                body = masked[start:i].rstrip().endswith(")")
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0 and body:
                start, body = i + 1, False
        elif ch == ";" and depth == 0:
            out.append(" ".join(masked[start : i + 1].split()))
            start = i + 1
    return out


def declaration(text: str, name: str) -> str | None:
    """Return the one-line ``extern`` or prototype that declares ``name``, or None."""
    for stmt in statements(text):
        if "," in stmt.split("(")[0] or not re.search(
            r"\b" + re.escape(name) + r"\b", stmt
        ):
            continue
        if stmt.startswith("extern ") or re.search(
            r"\b" + re.escape(name) + r"\s*\(", stmt
        ):
            if not stmt.startswith(("typedef", "static")) and "=" not in stmt:
                return stmt
    return None
