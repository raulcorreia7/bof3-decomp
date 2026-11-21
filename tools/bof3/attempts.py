"""The rows of ``config/attempts.jsonl``: parse, spell and validate. Pure."""

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
    return [line for line in text.splitlines() if line.strip()]


def parse(line: str) -> Attempt:
    return Attempt(**json.loads(line))


def function_of(line: str) -> str:
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


def validate(text: str, label: str) -> list[str]:
    """Each row outside the schema, as ``label:line: problem``."""
    found: list[str] = []
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
    return found
