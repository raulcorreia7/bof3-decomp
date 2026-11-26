"""The compile cache leaves no lock behind and stays within its bounds."""

from __future__ import annotations

import os
from pathlib import Path

import pytest

import cc


@pytest.fixture(autouse=True)
def cache(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> Path:
    monkeypatch.setattr(cc, "CACHE_DIR", str(tmp_path / "cache"))
    monkeypatch.delenv("BOF3_CC_CACHE", raising=False)
    return tmp_path / "cache"


@pytest.mark.parametrize("status", [0, 1])
def test_a_finished_compile_leaves_no_lock(
    tmp_path: Path, cache: Path, monkeypatch: pytest.MonkeyPatch, status: int
) -> None:
    output = tmp_path / "a.o"

    def compile_one(plan, gcc_args, env, tmp):
        output.write_bytes(b"object")
        return status, []

    monkeypatch.setattr(cc, "cache_key", lambda *_: "ab" + "0" * 38)
    monkeypatch.setattr(cc, "compile_one", compile_one)
    monkeypatch.setattr(cc, "PRUNE_ONE_IN", 10**9)
    plan = {"output": str(output), "depfile": None}
    assert cc.cached_compile(plan, [], {}, str(tmp_path), None) == status
    assert not list(cache.glob("*/*.lock"))
    assert len(list(cache.glob("*/*.obj"))) == (status == 0)


def test_the_prune_keeps_the_newest_entries_within_the_bound(
    cache: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    monkeypatch.setattr(cc, "MAX_ENTRIES", 10)
    (cache / "ab").mkdir(parents=True)
    for age in range(30):
        entry = cache / "ab" / f"{age:040x}.obj"
        entry.write_bytes(b"0\nobject")
        os.utime(entry, (1000 + age, 1000 + age))
    (cache / "ab" / f"{99:040x}.o").write_bytes(b"old layout")
    cc.prune()
    kept = sorted(path.name for path in cache.glob("ab/*"))
    assert kept == [f"{age:040x}.obj" for age in range(21, 30)]
