"""`Renamed: <old> -> <new>` commit-message lines, which `check_kept.py` and `check_tree.sh` accept as a rename.

python3 -m bof3.source.renames BASE < DIFF   (from tools/) the diff with each removed line's old names renamed
"""

from __future__ import annotations

import re
import sys

from bof3.adapters.git import git
from bof3.core.paths import ROOT

PAIR = re.compile(r"^Renamed:\s*(\w+)\s*->\s*(\w+)", re.M)


def pairs(log: str) -> dict[str, str]:
    """Old name -> new name, for each `Renamed:` line of a commit log."""
    return dict(PAIR.findall(log))


def since(base: str, head: str = "HEAD") -> dict[str, str]:
    """The renames the commits in BASE..HEAD state."""
    return pairs(git("log", "--format=%B", f"{base}..{head}", root=ROOT))


def apply(text: str, renames: dict[str, str]) -> str:
    """TEXT with every old name, as a whole word, replaced by its new name in one pass."""
    if not renames:
        return text
    word = re.compile(r"\b(" + "|".join(map(re.escape, renames)) + r")\b")
    return word.sub(lambda match: renames[match.group(1)], text)


def main(argv: list[str]) -> int:
    if len(argv) != 2 or argv[1] in ("-h", "--help"):
        print((__doc__ or "").strip(), file=sys.stderr)
        return 2
    renames = since(argv[1])
    for line in sys.stdin:
        removed = line.startswith("-") and not line.startswith("--")
        sys.stdout.write(apply(line, renames) if removed else line)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv))
