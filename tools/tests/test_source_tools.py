from __future__ import annotations

import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import typeloss


def test_type_loss_allows_only_the_recorded_integer_correction(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    path = "src/overlays/area/area075/13/area075_13.h"
    old = {path: "void func_801F2E64(void* arg0, s32 arg1);"}
    new = {path: "void func_801F2E64(s32 arg0, s32 arg1);"}
    monkeypatch.setattr(
        typeloss, "sources", lambda rev: iter((old if rev == "old" else new).items())
    )
    assert typeloss.main(["old", "new"]) == 0
    new[path] = "void func_801F2E64(u32 arg0, s32 arg1);"
    assert typeloss.main(["old", "new"]) == 1
    new[path] = (
        "void func_801F2E64(s32 arg0, s32 arg1);\nvoid func_801F2E64(u32 arg0, s32 arg1);"
    )
    assert typeloss.main(["old", "new"]) == 1
