"""Run ``tools/match.sh``."""

from __future__ import annotations

import os
import subprocess
from pathlib import Path

from bof3.match import MatchResult


def run_match(
    root: Path, *args: str, cand_out: Path | None = None, merged: bool = False
) -> MatchResult:
    """Run ``match.sh`` with ``args``; ``cand_out`` also receives the candidate's bytes."""
    env = {**os.environ, "MATCH_CAND_OUT": str(cand_out)} if cand_out else None
    result = subprocess.run(
        ["sh", "tools/match.sh", *args],
        cwd=root,
        env=env,
        stdout=subprocess.PIPE,
        stderr=subprocess.STDOUT if merged else subprocess.PIPE,
        text=True,
        check=False,
    )
    return MatchResult(result.returncode, result.stdout + (result.stderr or ""))
