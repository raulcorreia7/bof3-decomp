from __future__ import annotations

import subprocess
from pathlib import Path

import pytest
from fixture import put_symbols

import check_names
from check_names import offenders, unnamed_parameters


def test_an_invented_name_with_an_address_is_an_offender() -> None:
    text = "void Menu_SwapBytes_801D933C(void);\nenum { EFFECT_BANK_80140000 };\nu8 pad_800F723D;\n"
    assert offenders(text) == {
        "Menu_SwapBytes_801D933C",
        "EFFECT_BANK_80140000",
        "pad_800F723D",
    }


def test_unnamed_parameters_are_offenders() -> None:
    assert unnamed_parameters("void f(s32 arg0, s32 arg1) { return arg0; }\n") == {
        "arg0",
        "arg1",
    }


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


def test_a_new_name_with_a_rejected_word_is_an_offender() -> None:
    name = "BattleHandlerTable"
    assert check_names.rejected_names(f"extern u8 {name};\n") == {name}


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


RENAMED_OFFSET_BODY = (
    "void func_801D9C80(void) { u8 v = FIELD(u8, base, 0x4u); Battle_DrawTile(v); }\n"
)


def _renamed_offset_repo(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, after: str
) -> None:
    def git(*args: str) -> None:
        subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)

    git("init", "-q")
    git("config", "user.email", "t@t")
    git("config", "user.name", "t")
    (tmp_path / "src").mkdir()
    (tmp_path / "src/func_801D9C80.c").write_text(RENAMED_OFFSET_BODY)
    git("add", ".")
    git("commit", "-qm", "base")
    git("mv", "src/func_801D9C80.c", "src/Battle_DrawTile.c")
    (tmp_path / "src/Battle_DrawTile.c").write_text(after)
    git("add", ".")
    git("commit", "-qm", "rename the file")
    monkeypatch.chdir(tmp_path)


def test_a_renamed_file_that_gains_an_offset_access_fails(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    _renamed_offset_repo(
        tmp_path,
        monkeypatch,
        RENAMED_OFFSET_BODY.replace(
            "Battle_DrawTile(v); }",
            "Battle_DrawTile(v); u8 w = FIELD(u8, base, 0x8u); }",
        ),
    )
    assert check_names.main(["--diff", "HEAD~1"]) == 1
    assert "FIELD(): 1 new offset access" in capsys.readouterr().err


LAYOUT = """sha1: 0
segments:
  - name: main
    type: code
    start: 0x0
    vram: 0x80000000
    align: 4
    subsegments:
      - [0x0, %s, %s]
"""


def write_image(
    root: Path, kind: str, row: str, table: str, unit: str, unit_name: str
) -> None:
    """Write one image layout, its symbol table and its one source file."""
    (root / "config/exe/a").mkdir(parents=True, exist_ok=True)
    (root / "config/exe/a/splat.yaml").write_text(LAYOUT % (kind, row))
    put_symbols(root, '["exe/a"]\n' + table + "\n")
    (root / "src/a").mkdir(parents=True, exist_ok=True)
    (root / "src/a" / f"{unit_name}.c").write_text(unit)


NAMED_UNIT = "MATCH void Named(void) {}\n"
NAMED_ROW = 'Named = { addr = 0x80000000, type = "func", source = "x" }'


@pytest.fixture
def no_ratchet(monkeypatch: pytest.MonkeyPatch) -> None:
    """The address-name ratchet reads git; these fixtures check the layout rule alone."""
    monkeypatch.setattr(check_names, "tree_entries", lambda: set())


def test_a_unit_row_that_keeps_its_address_name_is_stale(
    tmp_path: Path,
    monkeypatch: pytest.MonkeyPatch,
    no_ratchet: None,
    capsys: pytest.CaptureFixture[str],
) -> None:
    monkeypatch.chdir(tmp_path)
    write_image(tmp_path, "c", "func_80000000", NAMED_ROW, NAMED_UNIT, "func_80000000")
    assert check_names.main([]) == 1
    assert "keeps the address name" in capsys.readouterr().err


def rename_repo(root: Path) -> None:
    """Commit one offender under ``src/a`` and stage a rename of it or another file."""
    subprocess.run(["git", "init", "-q"], cwd=root, check=True)
    for key, value in (("user.email", "t@t"), ("user.name", "t")):
        subprocess.run(["git", "config", key, value], cwd=root, check=True)
    (root / "src/a").mkdir(parents=True)
    (root / "src/a/A.c").write_text("extern u8 Foo_801D933C;\n")
    (root / "config").mkdir()
    (root / "config/address_names.txt").write_text("src/a/A.c\tFoo_801D933C\n")
    subprocess.run(["git", "add", "."], cwd=root, check=True)
    subprocess.run(["git", "commit", "-qm", "base"], cwd=root, check=True)


def test_an_unstaged_rename_reads_the_file_that_holds_the_name(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    rename_repo(tmp_path)
    (tmp_path / "src/a/A.c").rename(tmp_path / "src/a/B.c")
    monkeypatch.chdir(tmp_path)
    assert check_names.main([]) == 0


def test_offset_macro_moved_to_a_sibling_file_is_not_new(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    def git(*args: str) -> None:
        subprocess.run(["git", *args], cwd=tmp_path, check=True, capture_output=True)

    git("init", "-q")
    git("config", "user.email", "t@t")
    git("config", "user.name", "t")
    (tmp_path / "src").mkdir()
    use = "void f(void) { SP_REF(u8, 0x0u) = 1; }\n"
    (tmp_path / "src/a.c").write_text("void g(void);\n" + use)
    git("add", ".")
    git("commit", "-qm", "base")
    (tmp_path / "src/a.c").write_text("void g(void);\n")
    (tmp_path / "src/b.c").write_text(use)
    git("add", ".")
    git("commit", "-qm", "move")
    monkeypatch.chdir(tmp_path)
    assert check_names.main(["--diff", "HEAD~1"]) == 0, capsys.readouterr().err


NAMING = """\
Engine modules (`src/engine/<module>`):

| Module | Tag | Folders |
| --- | --- | --- |
| camera | `Camera_` | `field/camera` |
| archives | `EMI_` | `emi/loader` |

Game parts (`src/overlays`, `src/logo`):

| Part | Tag | Folder |
| --- | --- | --- |
| area | `Area_` | `overlays/area` |
| fairy village | `Fairy_` | `overlays/commu`, `area175` to `area176` |
"""


def test_a_folder_allows_the_tags_of_its_table_row() -> None:
    folders = check_names.folder_tags(NAMING)
    assert folders["src/engine/field/camera"] == {"Camera"}
    assert folders["src/overlays/commu"] == {"Fairy"}
    assert folders["src/overlays/area/area176"] == {"Fairy", "Area"}


def test_a_function_with_another_modules_tag_is_a_mismatch() -> None:
    folders = check_names.folder_tags(NAMING)
    text = "void Party_Load(s32 id)\n{\n}\n\ns32 Camera_Get(void)\n{\n}\n"
    path = "src/engine/emi/loader/EMI_Load.c"
    assert check_names.tag_mismatches(text, path, folders) == {
        "Party_Load",
        "Camera_Get",
    }


def test_a_comment_or_a_call_is_not_a_definition() -> None:
    folders = check_names.folder_tags(NAMING)
    text = (
        "/* void Party_Load(s32 id) */\nvoid EMI_Load(void)\n{\n    Party_Load(1);\n}\n"
    )
    assert (
        check_names.tag_mismatches(text, "src/engine/emi/loader/a.c", folders) == set()
    )


def test_a_folder_outside_the_tables_is_not_checked() -> None:
    folders = check_names.folder_tags(NAMING)
    assert (
        check_names.tag_mismatches(
            "void X_Y(void)\n{\n}\n", "src/engine/slus/a.c", folders
        )
        == set()
    )


def test_a_new_mismatch_fails_and_a_listed_one_passes(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    (tmp_path / "docs").mkdir()
    (tmp_path / "docs/naming.md").write_text(NAMING)
    folder = tmp_path / "src/engine/emi/loader"
    folder.mkdir(parents=True)
    (folder / "a.c").write_text("void Party_Load(void)\n{\n}\n")
    subprocess.run(["git", "init", "-q"], cwd=tmp_path, check=True)
    subprocess.run(["git", "add", "."], cwd=tmp_path, check=True)
    monkeypatch.chdir(tmp_path)
    assert check_names.check_tags() is True
    assert (
        "Party_Load: the prefix is not a tag of this folder" in capsys.readouterr().err
    )
    (tmp_path / "config").mkdir()
    (tmp_path / "config/tag_mismatches.txt").write_text(
        "src/engine/emi/loader/a.c\tParty_Load\n"
    )
    assert check_names.check_tags() is False
    (folder / "a.c").write_text("void EMI_Load(void)\n{\n}\n")
    assert check_names.check_tags() is True
    assert "no longer a mismatch" in capsys.readouterr().err
