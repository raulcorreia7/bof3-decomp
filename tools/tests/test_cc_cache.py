"""The compile cache keys on the preprocessed source, the arguments and the tools."""

from __future__ import annotations

import os
from pathlib import Path

import pytest

import cc

pytestmark = pytest.mark.skipif(
    not os.path.isfile(cc.GCC), reason="the GCC 2.7.2 PSX toolchain is not installed"
)


def key(tmp_path: Path, *flags: str) -> str | None:
    plan = cc.parse([*flags, "-c", str(tmp_path / "a.c"), "-o", str(tmp_path / "a.o")])
    env = dict(os.environ, GCC_EXEC_PREFIX=cc.GCC_DIR + "/", COMPILER_PATH=cc.GCC_DIR)
    return cc.cache_key(plan, cc.gcc_arguments(plan), env)


def test_a_changed_flag_or_header_changes_the_key(tmp_path: Path) -> None:
    (tmp_path / "a.c").write_text('#include "a.h"\nint f(void) { return N; }\n')
    (tmp_path / "a.h").write_text("#define N 1\n")
    first = key(tmp_path, "-O2")
    assert first and key(tmp_path, "-O2") == first
    assert key(tmp_path, "-O1") != first
    assert key(tmp_path, "-O2", "-DX") != first
    (tmp_path / "a.h").write_text("#define N 2\n")
    assert key(tmp_path, "-O2") != first


def test_a_hit_copies_the_object_and_rewrites_the_depfile(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    monkeypatch.setattr(cc, "CACHE_DIR", str(tmp_path / "cache"))
    monkeypatch.delenv("BOF3_CC_CACHE", raising=False)
    (tmp_path / "a.c").write_text("int f(void) { return 1; }\n")
    args = ["-O2", "-MMD", "-MP", "-MF", "a.d", "-c", str(tmp_path / "a.c")]
    out = []
    for name in ("cold", "warm"):
        monkeypatch.chdir(tmp_path)
        assert cc.main(["--build-dir", str(tmp_path / name), *args, "-o", "a.o"]) == 0
        out.append(tmp_path / name)
    assert (out[0] / "a.o").read_bytes() == (out[1] / "a.o").read_bytes()
    assert len(list((tmp_path / "cache").glob("*.o"))) == 1
    assert (out[1] / "a.d").read_text().startswith("a.o:")
