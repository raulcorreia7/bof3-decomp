from __future__ import annotations

import subprocess
from pathlib import Path

import pytest

import check_names
from check_names import offenders, unnamed_parameters


def test_an_invented_name_with_an_address_is_an_offender() -> None:
    text = "void Menu_SwapBytes_801D933C(void);\nenum { EFFECT_BANK_80140000 };\nu8 pad_800F723D;\n"
    assert offenders(text) == {
        "Menu_SwapBytes_801D933C",
        "EFFECT_BANK_80140000",
        "pad_800F723D",
    }


@pytest.mark.parametrize(
    "name",
    [
        "func_801D933C",
        "D_80146908",
        "L801D933C",
        "jtbl_801D933C",
        "jpt_801D933C_2",
        "s_gap_801D933C",
    ],
)
def test_the_default_tool_names_are_allowed(name: str) -> None:
    assert offenders(f"extern u8 {name};\n") == set()


def test_comments_strings_and_hex_literals_are_not_checked() -> None:
    text = '/* Foo_801D933C */\n// Bar_801D933C\nchar* s = "Baz_801D933C";\nu32 v = 0x801D933C;\n#include "x_801D933C.h"\n'
    assert offenders(text) == set()


def test_a_suffixed_default_name_is_still_an_offender() -> None:
    assert offenders(
        "void func_801D99AC_decl_guard(void);\nextern u8 D_801F24FC_Data;\n"
    ) == {
        "func_801D99AC_decl_guard",
        "D_801F24FC_Data",
    }


def test_words_without_a_digit_run_are_not_addresses() -> None:
    assert offenders("int FACEDBEE_flag;\nint step_12;\n") == set()


def test_unnamed_parameters_are_offenders() -> None:
    assert unnamed_parameters("void f(s32 arg0, s32 arg1) { return arg0; }\n") == {
        "arg0",
        "arg1",
    }


def test_argn_in_a_comment_or_string_is_ignored() -> None:
    assert unnamed_parameters('/* arg0 */ char *s = "arg1"; void f(s32 x);\n') == set()


def test_a_diff_with_an_unnamed_parameter_fails(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    def git(*args: str) -> None:
        subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)

    git("init", "-q")
    git("config", "user.email", "t@t")
    git("config", "user.name", "t")
    (tmp_path / "src").mkdir()
    (tmp_path / "src/a.c").write_text("void f(void);\n")
    git("add", ".")
    git("commit", "-qm", "base")
    (tmp_path / "src/a.c").write_text("void f(s32 arg0);\n")
    git("commit", "-qam", "add arg0")
    monkeypatch.chdir(tmp_path)
    assert check_names.main(["--diff", "HEAD~1"]) == 1
    assert "arg0: an unnamed parameter" in capsys.readouterr().err


@pytest.fixture
def tree(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> Path:
    monkeypatch.chdir(tmp_path)
    monkeypatch.setattr(check_names, "tree_entries", lambda: {"src/a.c\tFoo_801D933C"})
    return tmp_path


def test_the_ratchet_passes_on_the_baseline_and_fails_on_a_new_or_a_stale_name(
    tree: Path,
) -> None:
    baseline = tree / "config/address_names.txt"
    baseline.parent.mkdir()

    baseline.write_text("src/a.c\tFoo_801D933C\n")
    assert check_names.main([]) == 0

    baseline.write_text("")
    assert check_names.main([]) == 1  # new name

    baseline.write_text("src/a.c\tFoo_801D933C\nsrc/a.c\tGone_801D933C\n")
    assert check_names.main([]) == 1  # the baseline may only shrink
