"""What ``tools/match.sh`` reports for one function, parsed. Pure; the adapter runs the script."""

from __future__ import annotations

import re
from dataclasses import dataclass

_DIFF_LINE = re.compile(r"^[! ] ?[0-9A-F]{8}:")
_DIFF_CONTINUATION = re.compile(r"^[! ]\s+\|")
_INSTRUCTION = re.compile(r"\s*([0-9A-F]{8}):\s+[0-9a-f]{8}\s+(\S+)\s*(.*)")
_COMPILER_ERROR = re.compile(r"\.[ch]:\d+: (?!warning)")

#: One instruction of a side-by-side listing: address, mnemonic, operands.
Instruction = tuple[str, str, str]


@dataclass(frozen=True)
class MatchResult:
    """One run of ``match.sh``: its exit code and everything it printed."""

    returncode: int
    output: str

    @property
    def exact(self) -> bool:
        """Whether the function's bytes equal retail."""
        return self.returncode == 0

    @property
    def lines(self) -> list[str]:
        """The output lines."""
        return self.output.splitlines()

    @property
    def differing(self) -> list[str]:
        """The lines ``--diff`` marks as differing."""
        return [line for line in self.lines if line.startswith("!")]

    @property
    def matched(self) -> bool:
        """Whether ``--diff`` printed its ``match:`` line."""
        return any(line.startswith("match: ") for line in self.lines)

    def tail(self, count: int) -> list[str]:
        """The last ``count`` non-blank-trimmed lines."""
        return self.output.strip().splitlines()[-count:]

    def errors(self) -> list[str]:
        """The compiler error lines, else every line."""
        lines = self.output.strip().splitlines()
        return [x for x in lines if _COMPILER_ERROR.search(x)] or lines


def side_by_side(result: MatchResult) -> tuple[list[Instruction], list[Instruction]]:
    """Return the (retail, candidate) instruction lists of a ``--diff`` run."""
    retail: list[Instruction] = []
    candidate: list[Instruction] = []
    for line in result.lines:
        if not (_DIFF_LINE.match(line) or _DIFF_CONTINUATION.match(line)):
            continue
        left, _, right = line[2:].partition("|")
        for text, instructions in ((left, retail), (right, candidate)):
            found = _INSTRUCTION.match(text)
            if found:
                instructions.append((found[1], found[2], found[3].strip()))
    return retail, candidate
