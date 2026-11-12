"""The compile cache keys on the preprocessed source, the arguments and the tools."""

from __future__ import annotations

import os
import threading
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


def test_the_split_assembly_of_include_asm_changes_the_key(tmp_path: Path) -> None:
    asm = tmp_path / "asm" / "t"
    asm.mkdir(parents=True)
    (asm / "f.s").write_text(".section .text\nnop\n")
    (tmp_path / "a.c").write_text(
        '#define ASM_DIR "asm/t"\n'
        '#define INCLUDE_ASM(name) __asm__(".section .text\\n.include \\"" ASM_DIR "/" #name ".s\\"\\n")\n'
        "INCLUDE_ASM(f);\n"
    )
    flags = ("-O2", f"-Wa,-I{tmp_path}")
    first = key(tmp_path, *flags)
    assert first and key(tmp_path, *flags) == first
    (asm / "f.s").write_text(".section .text\nnop\nnop\n")
    assert key(tmp_path, *flags) != first


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


def test_two_builds_of_one_cold_key_compile_it_once(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    monkeypatch.setattr(cc, "CACHE_DIR", str(tmp_path / "cache"))
    monkeypatch.delenv("BOF3_CC_CACHE", raising=False)
    (tmp_path / "a.c").write_text("int f(void) { return 1; }\n")
    plan = cc.parse(
        ["-O2", "-MMD", "-MP", "-MF", "a.d", "-c", str(tmp_path / "a.c"), "-o", "a.o"]
    )
    env = dict(os.environ, GCC_EXEC_PREFIX=cc.GCC_DIR + "/", COMPILER_PATH=cc.GCC_DIR)
    started, release = threading.Event(), threading.Event()
    compiled = []
    real = cc.compile_one

    def slow(*args):
        compiled.append(1)
        started.set()
        release.wait(5)
        return real(*args)

    monkeypatch.setattr(cc, "compile_one", slow)

    def build(name: str) -> None:
        work = tmp_path / name
        (work / "tmp").mkdir(parents=True)
        own = dict(plan, output=str(work / "a.o"), depfile=str(work / "a.d"))
        assert (
            cc.cached_compile(own, cc.gcc_arguments(own), env, str(work / "tmp"), None)
            == 0
        )

    first = threading.Thread(target=build, args=("first",))
    first.start()
    assert started.wait(5)
    second = threading.Thread(target=build, args=("second",))
    second.start()
    second.join(0.5)
    release.set()
    first.join()
    second.join()
    assert len(compiled) == 1
    assert (tmp_path / "first" / "a.o").read_bytes() == (
        tmp_path / "second" / "a.o"
    ).read_bytes()
