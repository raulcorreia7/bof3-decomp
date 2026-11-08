from __future__ import annotations

from pathlib import Path

import pytest

import check_names
from check_names import offenders


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
