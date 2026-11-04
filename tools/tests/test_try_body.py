"""try_body swaps one INCLUDE_ASM for a body, adds the declarations it needs, and keeps or restores."""

from __future__ import annotations

from pathlib import Path

import pytest

import try_body
from bof3.source.index import Func

HEADER = '#ifndef H\n#define H\n\n#include "common.h"\n\nextern s16 D_1;\n\nvoid f(void);\n\n#endif\n'
STUB = '#include "img.h"\n\nINCLUDE_ASM(func_8001);\n'


@pytest.fixture
def root(tmp_path: Path) -> Path:
    (tmp_path / "src/a").mkdir(parents=True)
    (tmp_path / "src/a/img.h").write_text(HEADER, encoding="utf-8")
    (tmp_path / "src/a/b.c").write_text(STUB, encoding="utf-8")
    return tmp_path


def func(status: str = "ASM") -> Func:
    return Func("exe/a", "func_8001", 0x100, 8, (0, 0), "x", status, "src/a/b.c")


def test_split_decls_removes_the_declaration_lines() -> None:
    body, decls = try_body.split_decls(
        "@decl extern s8 D_2;\nvoid func_8001(void) {}\n"
    )
    assert body == "void func_8001(void) {}" and decls == ["extern s8 D_2;"]


def test_declared_name() -> None:
    assert try_body.declared_name("extern s16 D_2[];") == "D_2"
    assert try_body.declared_name("void g(int x);") == "g"
    assert try_body.declared_name("#define K 0x10") == "K"


def test_add_declarations_places_externs_with_externs_and_the_rest_last() -> None:
    text = try_body.add_declarations(
        HEADER, ["extern s8 D_2;", "void g(void);", "#define K 4"]
    )
    lines = text.split("\n")
    assert lines.index("extern s8 D_2;") == lines.index("extern s16 D_1;") + 1
    assert lines.index("#define K 4") == lines.index('#include "common.h"') + 1
    assert text.index("void g(void);") > text.index("void f(void);")
    assert text.rstrip().endswith("#endif")


def test_attempt_keeps_an_exact_body_and_its_new_declarations(
    root: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    monkeypatch.setattr(try_body, "match", lambda ref, r: (True, ""))
    text = "@decl extern s8 D_2;\n@decl extern s16 D_1;\nvoid func_8001(void) {}\n"
    assert try_body.attempt(root, func(), text) == ("EXACT", "src/a/b.c")
    assert "void func_8001(void) {}" in (root / "src/a/b.c").read_text()
    header = (root / "src/a/img.h").read_text()
    assert "extern s8 D_2;" in header and header.count("D_1") == 1


def test_attempt_restores_every_file_on_a_mismatch(
    root: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    monkeypatch.setattr(try_body, "match", lambda ref, r: (False, "differs"))
    out = try_body.attempt(
        root, func(), "@decl extern s8 D_2;\nvoid func_8001(void) {}"
    )
    assert out == ("FAIL", "differs")
    assert (root / "src/a/b.c").read_text() == STUB
    assert (root / "src/a/img.h").read_text() == HEADER


def test_attempt_restores_when_the_match_raises(
    root: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    def boom(ref: str, r: Path) -> tuple[bool, str]:
        raise KeyboardInterrupt

    monkeypatch.setattr(try_body, "match", boom)
    with pytest.raises(KeyboardInterrupt):
        try_body.attempt(root, func(), "@decl extern s8 D_2;\nvoid func_8001(void) {}")
    assert (root / "src/a/b.c").read_text() == STUB
    assert (root / "src/a/img.h").read_text() == HEADER


def test_attempt_skips_what_it_cannot_replace(root: Path) -> None:
    assert try_body.attempt(root, func("C"), "x")[0] == "SKIP"
    (root / "src/a/b.c").write_text("int func_8001(void) { return 0; }\n")
    assert try_body.attempt(root, func(), "x") == ("SKIP", "already has a body")


def test_a_failed_body_is_not_compiled_twice(
    root: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    calls = []

    def fake(ref: str, r: Path) -> tuple[bool, str]:
        calls.append(ref)
        return False, "differs"

    monkeypatch.setattr(try_body, "match", fake)
    text = "void func_8001(void) {}\n"
    first = try_body.trial(root, func(), text)
    again = try_body.trial(root, func(), text + "\n  \n")
    assert first[0] == "FAIL" and again[0] == "REPEAT" and len(calls) == 1
    assert try_body.trial(root, func(), text, force=True)[0] == "FAIL"
    assert len(calls) == 2
    assert try_body.trial(root, func(), "void func_8001(void) { }\n")[0] == "FAIL"


def test_the_differing_count_comes_from_the_candidate_bytes(
    root: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    def fake(ref: str, r: Path) -> tuple[bool, str]:
        (r / try_body.CAND).parent.mkdir(exist_ok=True)
        (r / try_body.CAND).write_bytes((1).to_bytes(4, "little") * 2)
        return False, "differs"

    monkeypatch.setattr(try_body, "match", fake)
    status, detail, diff = try_body.trial(root, func(), "void func_8001(void) {}\n")
    assert (status, diff) == ("FAIL", 2) and detail.startswith("2 differing; ")
