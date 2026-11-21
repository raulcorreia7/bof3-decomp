"""The rows of ``config/attempts.jsonl``: parse, order, insert and validate. Pure; the caller does the I/O."""

from __future__ import annotations

import json
from dataclasses import asdict, dataclass

#: The keys of a row, in order.
KEYS = ("function", "tried", "first_diff", "score")


@dataclass(frozen=True)
class Attempt:
    """One recorded attempt at one function."""

    function: str
    tried: str
    first_diff: str
    score: object

    @property
    def note(self) -> str:
        """The attempt as one line of text: what was tried, the first difference and the score."""
        parts = (self.tried, self.first_diff, _percent(self.score))
        return "; ".join(part for part in parts if part) or "attempt recorded"


def _percent(score: object) -> str:
    """A percent number, or a string that states its own unit."""
    if score is None:
        return ""
    return f"{score:g}%" if isinstance(score, (int, float)) else str(score)


def parse_lines(text: str) -> list[str]:
    """The rows of ``text``, one line each."""
    return [line for line in text.splitlines() if line.strip()]


def parse(line: str) -> Attempt:
    """The attempt a row holds."""
    return Attempt(**json.loads(line))


def function_of(line: str) -> str:
    """The ``function`` of one row."""
    return json.loads(line)["function"]


def score(text: str) -> object:
    """The value of a ``--score`` text: a number, ``null``, or the text."""
    try:
        value = json.loads(text)
    except json.JSONDecodeError:
        return text
    return value if value is None or isinstance(value, (int, float)) else text


def spelling(row: Attempt, like: str | None) -> str:
    """``row`` as one line, spelled as ``like`` spells its own object."""
    if like is not None and like == json.dumps(json.loads(like), separators=(",", ":")):
        return json.dumps(asdict(row), separators=(",", ":"))
    return json.dumps(asdict(row))


def place(lines: list[str], function: str) -> int:
    """The index a row for ``function`` goes to: after its last row, else its sorted place."""
    last = None
    for index, line in enumerate(lines):
        other = function_of(line)
        if other == function:
            last = index
        elif last is None and other > function:
            return index
    return len(lines) if last is None else last + 1


def insert(lines: list[str], row: Attempt) -> int:
    """Insert ``row`` into ``lines`` at its place and return its 1-based line."""
    index = place(lines, row.function)
    like = lines[index - 1] if index else (lines[0] if lines else None)
    lines.insert(index, spelling(row, like))
    return index + 1


def sort(lines: list[str]) -> list[str]:
    """``lines`` in ``function`` order, each function's rows in the order they hold, without repeats."""
    seen: set[str] = set()
    kept: list[str] = []
    for line in sorted(lines, key=function_of):
        row = json.dumps(json.loads(line), sort_keys=True)
        if row not in seen:
            seen.add(row)
            kept.append(line)
    return kept


def validate(text: str, label: str) -> list[str]:
    """Each row outside the schema or the order, as ``label:line: problem``."""
    found: list[str] = []
    previous = ""
    ordered = True
    for number, line in enumerate(text.splitlines(), 1):
        if not line.strip():
            continue
        try:
            row = json.loads(line)
        except json.JSONDecodeError as error:
            found.append(f"{label}:{number}: not JSON: {error.msg}")
            continue
        if not isinstance(row, dict) or tuple(row) != KEYS:
            keys = tuple(row) if isinstance(row, dict) else (type(row).__name__,)
            found.append(f"{label}:{number}: keys {list(keys)} instead of {list(KEYS)}")
            continue
        if ordered and row["function"] < previous:
            found.append(
                f"{label}:{number}: {row['function']} sorts before {previous}; "
                "keep the rows in function order with tools/attempts.py sort"
            )
            ordered = False
        previous = row["function"]
    return found
