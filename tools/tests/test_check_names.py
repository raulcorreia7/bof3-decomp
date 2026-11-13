from __future__ import annotations

import subprocess
from pathlib import Path

import pytest

import check_names
from check_names import offenders, offset_macros, unnamed_parameters


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


def test_offset_macros_are_refused_in_a_diff(
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
    (tmp_path / "src/a.c").write_text(
        "void f(void) { u8 v = FIELD(u8, base, 0x4u); SP_REF(u8, 0x0u) = v; }\n"
    )
    git("commit", "-qam", "add offset reads")
    monkeypatch.chdir(tmp_path)
    assert check_names.main(["--diff", "HEAD~1"]) == 1
    err = capsys.readouterr().err
    assert "FIELD(): 1 new offset access" in err
    assert "SP_REF(): 1 new offset access" in err


def test_a_diff_that_removes_an_offset_access_passes(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    def git(*args: str) -> None:
        subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)

    git("init", "-q")
    git("config", "user.email", "t@t")
    git("config", "user.name", "t")
    (tmp_path / "src").mkdir()
    (tmp_path / "src/a.c").write_text(
        "void f(void) { u8 v = FIELD(u8, base, 0x4u); }\n"
    )
    git("add", ".")
    git("commit", "-qm", "base")
    (tmp_path / "src/a.c").write_text("void f(void) { u8 v = base->unk_04; }\n")
    git("commit", "-qam", "read the member")
    monkeypatch.chdir(tmp_path)
    assert check_names.main(["--diff", "HEAD~1"]) == 0


def test_an_offset_access_in_a_comment_or_string_or_definition_is_not_refused() -> None:
    assert (
        offset_macros('/* FIELD(u8, base, 0x4u) */ char* s = "SP_REF(u8, 0x0u)";\n')
        == set()
    )
    assert (
        offset_macros("#define FIELD(type, base, off) (*FIELD_PTR(type, base, off))\n")
        == set()
    )
    assert (
        offset_macros("value = FIELD_PTR(u8, base, 0x4u); SP_PTR(u8, 0x0u);\n") == set()
    )


def test_the_offset_macros_are_named() -> None:
    assert offset_macros("x = FIELD(u8, base, 0x4u); SP(0x18u);\n") == {"FIELD", "SP"}


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


def test_camel_and_underscore_names_split_into_words() -> None:
    assert check_names.split_words("SND_PlayCue") == ["snd", "play", "cue"]
    assert check_names.split_words("g_PartyCount") == ["g", "party", "count"]
    assert check_names.split_words("ColorRGB8") == ["color", "rgb", "8"]
    assert check_names.split_words("UPoint2D") == ["u", "point", "2", "d"]


@pytest.mark.parametrize(
    "name",
    [
        "BattleHandlerTable",
        "EffectData",
        "g_BattleWork",
        "effect_kind",
        "saveBuf",
        "ItemIdx",
        "tile_cnt",
        "old_temp",
        "cur_row",
        "cell_ptr",
        "work_obj",
        "SceneFx",
        "BattleAmount",
        "WaitCheck",
        "BattleFinish",
        "MapStore",
    ],
)
def test_a_new_name_with_a_rejected_word_is_an_offender(name: str) -> None:
    assert check_names.rejected_names(f"extern u8 {name};\n") == {name}


@pytest.mark.parametrize(
    "name",
    [
        "Battle_ApplyDamage",
        "PartyMember",
        "g_PartyCount",
        "Callback",
        "Thread",
        "ColorRGB8",
        "Point2l",
        "BattleCommandFunc",
        "Message_WindowOpen",
        "Item_Add",
    ],
)
def test_a_new_name_in_the_decided_vocabulary_is_allowed(name: str) -> None:
    assert check_names.rejected_names(f"extern u8 {name};\n") == set()


@pytest.mark.parametrize(
    "name",
    [
        "World_UpdateClouds",
        "Plchar_Foo",
        "PAD_GetRepeatedButtons",
        "Mem_CopyBytes",
        "Matrix_SetIdentity",
        "Fish_Swim",
    ],
)
def test_a_new_name_with_an_old_system_tag_is_an_offender(name: str) -> None:
    assert check_names.rejected_names(f"void {name}(void);\n") == {name}


def test_rejected_words_in_comments_and_strings_are_ignored() -> None:
    text = '/* BattleHandlerTable */\nchar* s = "EffectData";\n'
    assert check_names.rejected_names(text) == set()


def test_a_diff_with_a_new_rejected_name_fails(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    def git(*args: str) -> None:
        subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)

    git("init", "-q")
    git("config", "user.email", "t@t")
    git("config", "user.name", "t")
    (tmp_path / "src").mkdir()
    (tmp_path / "src/a.c").write_text("void Battle_ApplyDamage(void);\n")
    git("add", ".")
    git("commit", "-qm", "base")
    (tmp_path / "src/a.c").write_text(
        "void Battle_ApplyDamage(void);\nvoid BattleHandlerTable(void);\n"
    )
    git("commit", "-qam", "add a rejected name")
    monkeypatch.chdir(tmp_path)
    assert check_names.main(["--diff", "HEAD~1"]) == 1
    assert "BattleHandlerTable" in capsys.readouterr().err


def test_a_diff_that_only_uses_an_existing_name_passes(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    def git(*args: str) -> None:
        subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)

    git("init", "-q")
    git("config", "user.email", "t@t")
    git("config", "user.name", "t")
    (tmp_path / "src").mkdir()
    (tmp_path / "src/a.c").write_text("extern unsigned char SaveData;\n")
    git("add", ".")
    git("commit", "-qm", "base")
    (tmp_path / "src/a.c").write_text(
        "extern unsigned char SaveData;\nvoid f(void) { SaveData = 1; }\n"
    )
    git("commit", "-qam", "use the existing name")
    monkeypatch.chdir(tmp_path)
    assert check_names.main(["--diff", "HEAD~1"]) == 0


def test_a_diff_that_deletes_a_file_does_not_crash(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    def git(*args: str) -> None:
        subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)

    git("init", "-q")
    git("config", "user.email", "t@t")
    git("config", "user.name", "t")
    (tmp_path / "src").mkdir()
    (tmp_path / "src/a.c").write_text("void f(void);\n")
    (tmp_path / "src/gone.c").write_text("void g(void);\n")
    git("add", ".")
    git("commit", "-qm", "base")
    git("rm", "-q", "src/gone.c")
    git("commit", "-qm", "delete a file")
    monkeypatch.chdir(tmp_path)
    assert check_names.main(["--diff", "HEAD~1"]) == 0
    assert "no new rejected names" in capsys.readouterr().out
