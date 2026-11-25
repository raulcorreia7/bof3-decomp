from __future__ import annotations

import shutil
import subprocess
from pathlib import Path

import pytest
from fixture import main, patch, put_symbols

from bof3.symbols import probe
from bof3.symbols.context import Context
from bof3.symbols.lookup import at
from bof3.symbols.probe import Layout, Member

CLANG = shutil.which(probe.CLANG) is not None


def _put_file(path: Path, text: str) -> None:
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text)


@pytest.fixture
def repo(tmp_path: Path) -> Path:
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    files = {
        "config/symbols/exe+a.toml": (
            '["exe/a"]\n'
            'Game = { addr = 0x80000000, type = "State", size = 0x10, source = "test" }\n'
            'Data = { addr = 0x80000020, type = "u8", size = 0x2, source = "test" }\n'
            'Open = { addr = 0x80000030, type = "func", source = "test" }\n'
            '["emi/etc/game/00"]\n'
            'g_Game = { addr = 0x80010000, type = "State", size = 0x10, source = "test" }\n'
        ),
        "config/exe/a/splat.yaml": (
            "segments:\n"
            "  - name: text\n"
            "    type: code\n"
            "    start: 0x0\n"
            "    vram: 0x80000000\n"
            "    subsegments:\n"
            "      - [0x0, c, Game]\n"
            "  - [0x100]\n"
        ),
        "include/common.h": "typedef unsigned char u8;\ntypedef unsigned short u16;\n",
        "include/game/values.h": (
            "typedef enum Ability {\n"
            "    ABILITY_SANCTUARY = 0x3A,\n"
            "    ABILITY_OTHER = 0x3B,\n"
            "} Ability;\n"
            "\n"
            "typedef enum Counts {\n"
            "    COUNT_ZERO,\n"
            "    COUNT_ONE = 0x3A,\n"
            "    COUNT_TWO,\n"
            "} Counts;\n"
            "\n"
            "#define STRING_COLON 0x3A\n"
            "#define FLAG_SHIFT (1 << 3)\n"
        ),
        "include/other.h": "#define OTHER_VALUE 0x3A\n",
        "include/psyq/sdk.h": "#define SDK_VALUE 0x3A\n",
        "src/a/a.h": (
            "#define IMAGE_VALUE 0x3A\n"
            "#define ALIAS_VALUE IMAGE_VALUE\n"
            '#include "group.h"\n'
            '#include "game/values.h"\n'
            "#include <psyq/sdk.h>\n"
        ),
        "src/group.h": "#define GROUP_VALUE 0x3A\n",
        "include/fixture.h": (
            "typedef struct Inner { u8 a; u16 b; } Inner;\n"
            "typedef struct State { Inner rows[2]; u8 flags; u8 pad_09[7]; } State;\n"
            "typedef union Choice { u8 byte; u16 half; } Choice;\n"
            "extern State Game;\n"
            "extern State g_Game;\n"
        ),
        "src/a/use.c": (
            "/* Game is a comment. */\n"
            'static const char *kName = "Game";\n'
            "void f(void) { Game.flags = 1; }\n"
            '#include "a.h"\n'
        ),
        "asm/exe/a/func_80000020.s": (
            '.include "macro.inc"\n'
            "nonmatching func_80000020, 0x20\n"
            "glabel func_80000020\n"
            "    /* 0 80000020 00000000 */  lui  $s0, %hi(Data)\n"
            "    /* 4 80000024 00000000 */  sw   $s0, %lo(Data)($s0)\n"
            "    /* 8 80000028 00000000 */  jr   $ra\n"
            "endlabel func_80000020\n"
        ),
    }
    for name, text in files.items():
        _put_file(tmp_path / name, text)
    subprocess.run(["git", "-C", str(tmp_path), "add", "."], check=True)
    subprocess.run(
        ["git", "-C", str(tmp_path), "commit", "-qm", "init"],
        check=True,
        env={
            "GIT_AUTHOR_NAME": "t",
            "GIT_AUTHOR_EMAIL": "t@t",
            "GIT_COMMITTER_NAME": "t",
            "GIT_COMMITTER_EMAIL": "t@t",
            "PATH": "/usr/bin:/bin",
        },
    )
    return tmp_path


@pytest.fixture
def lookup_repo(tmp_path: Path) -> Path:
    _put_file(
        tmp_path / "config/link.toml",
        '[[resident]]\ntarget = "exe/slus_004_22"\nvisible_to = ["emi"]\n',
    )
    return tmp_path


@pytest.mark.skipif(not CLANG, reason="needs clang for the record layout")
def test_member_reads_the_compiler_layout(
    repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    assert main(repo, ["member", "State", "0x6"]) == 0
    assert capsys.readouterr().out.splitlines() == ["rows[1].b\tu16"]


def test_at_prints_the_member_path(
    repo: Path, monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    inner = Layout(4, (Member(0, "a", "u8", 1), Member(2, "b", "u16", 2)), True)
    state = Layout(16, (Member(0, "rows", "Inner[2]", 8),), True)
    patch(
        monkeypatch,
        "type_layout",
        lambda _ctx, name: inner if name == "Inner" else state,
    )
    (repo / "config/link.toml").write_text("")
    assert main(repo, ["at", "exe/a", "0x80000006", "0x80000000"]) == 0
    assert capsys.readouterr().out.splitlines() == [
        "0x80000006  Game.rows[1].b+0x0  (State, 0x10)  [exe/a]",
        "0x80000000  Game+0x0  (State, 0x10)  [exe/a]",
    ]


def test_at_does_not_use_slus_symbols_for_logo(
    lookup_repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    _put_file(lookup_repo / "config/exe/logo/splat.yaml", "segments: []\n")
    _put_file(lookup_repo / "config/exe/slus_004_22/splat.yaml", "segments: []\n")
    put_symbols(
        lookup_repo,
        '["exe/slus_004_22"]\n'
        'GFX_AddPrim = { addr = 0x8014E5A0, type = "func", size = 0x10 }\n',
    )
    assert main(lookup_repo, ["at", "exe/logo", "0x8014E5A0"]) == 0
    assert capsys.readouterr().out.splitlines() == ["0x8014e5a0  no named owner"]


def test_at_resolves_explicit_imports_after_the_local_table(
    lookup_repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    image = "emi/boss/boss001/13"
    owner = "emi/battle/battle/03"
    _put_file(
        lookup_repo / f"config/{image}/splat.yaml",
        f"symbol_owners: [{owner}]\nsegments: []\n",
    )
    _put_file(lookup_repo / f"config/{owner}/splat.yaml", "segments: []\n")
    put_symbols(
        lookup_repo,
        f'["{owner}"]\n'
        'Effect_Reset = { addr = 0x801E5988, type = "func", size = 0x10 }\n'
        'Effect_Tick = { addr = 0x801E5998, type = "func", size = 0x10 }\n'
        f'["{image}"]\n'
        'Boss_Tick = { addr = 0x801E5998, type = "func", size = 0x10 }\n',
    )
    assert main(lookup_repo, ["at", image, "0x801E5988", "0x801E5998"]) == 0
    assert capsys.readouterr().out.splitlines() == [
        "0x801e5988  Effect_Reset+0x0  (func, 0x10)  [emi/battle/battle/03]",
        "0x801e5998  Boss_Tick+0x0  (func, 0x10)  [emi/boss/boss001/13]",
        "0x801e5998  Effect_Tick+0x0  (func, 0x10)  [emi/battle/battle/03]",
    ]
    assert main(lookup_repo, ["uses", f"{image}@0x801E5988"]) == 0
    assert capsys.readouterr().out.splitlines() == [
        f"{image}@0x801E5988  Effect_Reset+0x0  (func, 0x10)  [emi/battle/battle/03]"
    ]


@pytest.fixture
def alias_repo(lookup_repo: Path) -> Path:
    _put_file(lookup_repo / "config/exe/a/splat.yaml", "segments: []\n")
    put_symbols(
        lookup_repo,
        '["exe/a"]\n'
        'Word = { addr = 0x80000000, type = "u32", size = 0x4 }\n'
        'WordBytes = { addr = 0x80000000, type = "u8", size = 0x4, alias = true }\n'
        "Old = { addr = 0x80000000, alias = true }\n"
        'AliasOnly = { addr = 0x80000200, type = "u8", alias = true }\n',
    )
    return lookup_repo


def test_at_lists_same_address_aliases_after_the_owner(alias_repo: Path) -> None:
    result = at(Context(alias_repo), "exe/a", ["0x80000000"], None)
    assert [(owner.path, owner.size) for owner in result.rows[0].owners] == [
        ("Word", "(u32, 0x4)"),
        ("WordBytes", "(alias, u8, 0x4)"),
        ("Old", "(alias, untyped)"),
    ]


def test_uses_displays_an_alias_without_searching_it_as_the_owner(
    alias_repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    _put_file(alias_repo / "src/a/use.c", "extern unsigned char AliasOnly;\n")
    subprocess.run(["git", "init", "-q", str(alias_repo)], check=True)
    subprocess.run(["git", "-C", str(alias_repo), "add", "src/a/use.c"], check=True)

    assert main(alias_repo, ["uses", "exe/a@0x80000200"]) == 0
    assert capsys.readouterr().out.splitlines() == [
        "exe/a@0x80000200  AliasOnly+0x0  (alias, u8)  [exe/a]"
    ]


def test_uses_lists_c_and_asm_references(
    repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    assert main(repo, ["uses", "Game"]) == 0
    out = capsys.readouterr()
    assert "c\tsrc/a/use.c:3" in out.out
    assert "c\tsrc/a/use.c:1" not in out.out
    assert "c\tsrc/a/use.c:2" not in out.out
    assert main(repo, ["uses", "Data"]) == 0
    lines = capsys.readouterr().out.splitlines()
    assert lines == [
        "asm\tasm/exe/a/func_80000020.s:4\tfunc_80000020\tlui $s0, %hi(Data)",
        "asm\tasm/exe/a/func_80000020.s:5\tfunc_80000020\tsw $s0, %lo(Data)($s0)",
    ]


def test_value_lists_scopes_nearest_first(
    repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    assert main(repo, ["value", "0x3A", "--image", "exe/a"]) == 0
    assert capsys.readouterr().out.splitlines() == [
        "IMAGE_VALUE\tsrc/a/a.h:1\tIMAGE_",
        "ALIAS_VALUE\tsrc/a/a.h:2\tALIAS_",
        "GROUP_VALUE\tsrc/group.h:1\tGROUP_",
        "ABILITY_SANCTUARY\tinclude/game/values.h:2\tenum Ability",
        "COUNT_ONE\tinclude/game/values.h:8\tenum Counts",
        "STRING_COLON\tinclude/game/values.h:12\tSTRING_",
        "SDK_VALUE\tinclude/psyq/sdk.h:1\tSDK_",
    ]
