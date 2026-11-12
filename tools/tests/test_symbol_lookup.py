from __future__ import annotations

import shutil
import subprocess
from pathlib import Path

import pytest

import symbol
from symbol import Layout, Member

CLANG = shutil.which(symbol.CLANG) is not None

LAYOUT = """
*** Dumping AST Record Layout
         0 | struct __probe
         0 |   struct State x
         0 |     Inner[2] rows
         8 |     u8 flags
         9 |     u8[7] pad_09
           | [sizeof=16, align=2]
"""

CHOICE = """
*** Dumping AST Record Layout
         0 | struct __probe
         0 |   union Choice x
         0 |     u8 byte
         0 |     u16 half
           | [sizeof=2, align=2]
"""


@pytest.fixture
def repo(tmp_path: Path, monkeypatch: pytest.MonkeyPatch) -> Path:
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    files = {
        "config/symbols.toml": (
            '["exe/a"]\n'
            'Game = { addr = 0x80000000, type = "State", size = 0x10, source = "test" }\n'
            'Data = { addr = 0x80000020, type = "u8", size = 0x2, source = "test" }\n'
            'Open = { addr = 0x80000030, type = "func", source = "test" }\n'
            'Old = { addr = 0x80000000, alias = true, source = "test" }\n'
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
        path = tmp_path / name
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
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
    monkeypatch.setattr(symbol, "ROOT", tmp_path)
    monkeypatch.setattr(symbol, "SYMBOLS", tmp_path / "config/symbols.toml")
    monkeypatch.setattr(symbol, "LAYOUT_CACHE", tmp_path / "build/symbol-layouts.json")
    monkeypatch.setattr(symbol, "XREF_CACHE", tmp_path / "build/symbol-xrefs")
    monkeypatch.setattr(symbol, "_LAYOUTS", {})
    monkeypatch.setattr(symbol, "_LAYOUT_INDEX", None)
    monkeypatch.setattr(symbol, "_SPLAT_SPANS", {})
    monkeypatch.setattr(symbol, "_RANGES", {})
    return tmp_path


def test_probe_keeps_nested_members_and_array_sizes() -> None:
    layout = symbol.parse_probe(LAYOUT)
    assert layout is not None
    assert layout.size == 16
    assert [(m.offset, m.path, m.ctype, m.size) for m in layout.members] == [
        (0, "rows", "Inner[2]", 8),
        (8, "flags", "u8", 1),
        (9, "pad_09", "u8[7]", 7),
    ]


def test_a_union_alias_keeps_the_whole_cell() -> None:
    layout = symbol.parse_probe(CHOICE)
    assert layout is not None
    assert [(m.path, m.size) for m in layout.members] == [("byte", 1), ("half", 2)]


def test_locate_descends_into_record_arrays(monkeypatch: pytest.MonkeyPatch) -> None:
    inner = Layout(4, (Member(0, "a", "u8", 1), Member(2, "b", "u16", 2)), True)
    state = Layout(16, (Member(0, "rows", "Inner[2]", 8),), True)
    monkeypatch.setattr(
        symbol, "type_layout", lambda name: inner if name == "Inner" else state
    )
    assert symbol.locate(state, 6) == [("rows[1].b", 6, "u16")]
    assert symbol.locate(inner, 1) == []
    assert symbol.locate(state, 1) == [("rows[0]", 0, "Inner")]


def test_member_prints_every_union_name(
    repo: Path, monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    inner = Layout(4, (Member(0, "a", "u8", 1), Member(2, "b", "u16", 2)), True)
    choice = Layout(4, (Member(0, "byte", "u8", 4), Member(0, "half", "u16", 4)), True)
    monkeypatch.setattr(
        symbol, "type_layout", lambda name: choice if name == "Choice" else inner
    )
    assert symbol.main(["member", "Choice", "0x0"]) == 0
    assert capsys.readouterr().out.splitlines() == ["byte\tu8", "half\tu16"]


@pytest.mark.skipif(not CLANG, reason="needs clang for the record layout")
def test_member_reads_the_compiler_layout(
    repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    assert symbol.main(["member", "State", "0x6"]) == 0
    assert capsys.readouterr().out.splitlines() == ["rows[1].b\tu16"]


@pytest.mark.skipif(not CLANG, reason="needs clang for the record layout")
def test_member_reuses_the_cached_layout(
    repo: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    assert symbol.main(["member", "State", "0x6"]) == 0
    assert symbol.LAYOUT_CACHE.is_file()
    monkeypatch.setattr(symbol, "_LAYOUTS", {})
    monkeypatch.setattr(symbol, "_LAYOUT_INDEX", None)

    def fail(name: str) -> None:
        raise AssertionError("clang must not run for a warm cache")

    monkeypatch.setattr(symbol, "_probe", fail)
    assert symbol.main(["member", "State", "0x6"]) == 0


def test_member_rejects_an_outside_offset(repo: Path) -> None:
    with pytest.raises(SystemExit, match="outside"):
        symbol.main(["member", "State", "0x10"])


def test_member_rejects_an_unknown_type(repo: Path) -> None:
    with pytest.raises(SystemExit, match="no named members"):
        symbol.main(["member", "NoSuchRecord", "0x0"])


def test_at_prints_the_member_path(
    repo: Path, monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    inner = Layout(4, (Member(0, "a", "u8", 1), Member(2, "b", "u16", 2)), True)
    state = Layout(16, (Member(0, "rows", "Inner[2]", 8),), True)
    monkeypatch.setattr(
        symbol, "type_layout", lambda name: inner if name == "Inner" else state
    )
    assert symbol.main(["at", "exe/a", "0x80000006", "0x80000000"]) == 0
    assert capsys.readouterr().out.splitlines() == [
        "0x80000006  Game.rows[1].b+0x0  (State, 0x10)  [exe/a]",
        "0x80000000  Game+0x0  (State, 0x10)  [exe/a]",
    ]


def test_at_reads_a_resident_table_and_skips_aliases(
    repo: Path, monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    inner = Layout(4, (Member(0, "a", "u8", 1), Member(2, "b", "u16", 2)), True)
    state = Layout(16, (Member(0, "rows", "Inner[2]", 8),), True)
    monkeypatch.setattr(
        symbol, "type_layout", lambda name: inner if name == "Inner" else state
    )
    assert symbol.main(["at", "emi/etc/game/00", "0x80010006"]) == 0
    assert capsys.readouterr().out.splitlines() == [
        "0x80010006  g_Game.rows[1].b+0x0  (State, 0x10)  [emi/etc/game/00]"
    ]


def test_at_says_no_owner(repo: Path, capsys: pytest.CaptureFixture[str]) -> None:
    assert symbol.main(["at", "exe/a", "0x80000200"]) == 0
    assert capsys.readouterr().out.splitlines() == ["0x80000200  no named owner"]


def test_at_diff_reads_the_added_d_addresses(
    repo: Path, monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    inner = Layout(4, (Member(0, "a", "u8", 1), Member(2, "b", "u16", 2)), True)
    state = Layout(16, (Member(0, "rows", "Inner[2]", 8),), True)
    monkeypatch.setattr(
        symbol, "type_layout", lambda name: inner if name == "Inner" else state
    )
    (repo / "src/a/use.c").write_text(
        (repo / "src/a/use.c").read_text() + "extern u8 D_80000004;\n"
    )
    subprocess.run(["git", "-C", str(repo), "add", "."], check=True)
    subprocess.run(
        ["git", "-C", str(repo), "commit", "-qm", "add D_"],
        check=True,
        env={
            "GIT_AUTHOR_NAME": "t",
            "GIT_AUTHOR_EMAIL": "t@t",
            "GIT_COMMITTER_NAME": "t",
            "GIT_COMMITTER_EMAIL": "t@t",
            "PATH": "/usr/bin:/bin",
        },
    )
    assert symbol.main(["at", "--diff", "HEAD~1"]) == 0
    assert capsys.readouterr().out.splitlines()[0] == (
        "0x80000004  Game.rows[1].a+0x0  (State, 0x10)  [exe/a]"
    )


def test_uses_lists_c_and_asm_references(
    repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    assert symbol.main(["uses", "Game"]) == 0
    out = capsys.readouterr()
    assert "c\tsrc/a/use.c:3" in out.out
    assert "c\tsrc/a/use.c:1" not in out.out
    assert "c\tsrc/a/use.c:2" not in out.out
    assert symbol.main(["uses", "Data"]) == 0
    lines = capsys.readouterr().out.splitlines()
    assert lines == [
        "asm\tasm/exe/a/func_80000020.s:4\tfunc_80000020\tlui $s0, %hi(Data)",
        "asm\tasm/exe/a/func_80000020.s:5\tfunc_80000020\tsw $s0, %lo(Data)($s0)",
    ]


def test_uses_address_resolves_the_owner_first(
    repo: Path, monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    inner = Layout(4, (Member(0, "a", "u8", 1), Member(2, "b", "u16", 2)), True)
    state = Layout(16, (Member(0, "rows", "Inner[2]", 8),), True)
    monkeypatch.setattr(
        symbol, "type_layout", lambda name: inner if name == "Inner" else state
    )
    assert symbol.main(["uses", "exe/a@0x80000006"]) == 0
    out = capsys.readouterr().out.splitlines()
    assert out[0] == "exe/a@0x80000006  Game.rows[1].b+0x0  (State, 0x10)  [exe/a]"
    assert "c\tsrc/a/use.c:3" in out


def test_uses_rizin_xrefs_and_caches_the_map(
    repo: Path, capsys: pytest.CaptureFixture[str]
) -> None:
    project = repo / "build/meson/rz+exe+a.rzdb"
    project.parent.mkdir(parents=True)
    project.write_text("project")
    marker = repo / "called"
    script = repo / "bin/rz"
    script.parent.mkdir()
    script.write_text(
        "#!/bin/sh\n"
        f'echo x >> "{marker}"\n'
        'echo \'[{"from":2147483656,"to":2147483654,"type":"DATA"}]\'\n'
    )
    script.chmod(0o755)
    assert symbol.main(["uses", "exe/a@0x80000006"]) == 0
    out = capsys.readouterr().out
    assert "rizin\texe/a\t0x80000008\tDATA" in out
    assert marker.read_text().count("x") == 1
    assert symbol.main(["uses", "exe/a@0x80000006"]) == 0
    capsys.readouterr()
    assert marker.read_text().count("x") == 1


def test_foreign_table_outside_its_payload_is_ignored(repo: Path) -> None:
    assert symbol.foreign_visible("exe/a", "emi/etc/game/00", 0x80000010)
    assert not symbol.foreign_visible("exe/a", "emi/etc/game/00", 0x80000100)
