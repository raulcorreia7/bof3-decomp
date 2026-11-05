from __future__ import annotations

from pathlib import Path

import pytest

from bof3.link import symbols
from bof3.link.symbols import LinkError, Scan


def table(tmp_path: Path, body: str) -> Path:
    (tmp_path / "config/exe/a").mkdir(parents=True)
    (tmp_path / "config/exe/a/splat.yaml").write_text("name: a\n")
    (tmp_path / "config/symbols.toml").write_text(body)
    return tmp_path


def test_address_names_spell_their_address() -> None:
    assert symbols.address_of("D_80140000") == 0x80140000
    assert symbols.address_of("SCENA16_D_80010004") == 0x80010004
    assert symbols.address_of("g_Zenny") is None


def test_rows_load_sorted_with_attributes(tmp_path: Path) -> None:
    root = table(
        tmp_path,
        '["exe/a"]\nB = { addr = 0x20, type = "func", size = 0x8 }\nA = { addr = 0x10 }\n',
    )
    rows = symbols.target_rows(root, "exe/a")
    assert [(r.name, r.address) for r in rows] == [("A", 0x10), ("B", 0x20)]
    assert rows[1].comment == "type:func size:0x8"


@pytest.mark.parametrize(
    "body, fix",
    [
        ('["exe/a"]\nA = { addr = 0x10, adr = 1 }\n', "unknown key 'adr'"),
        ('["exe/a"]\nA = { addr = "0x10" }\n', "`addr` is missing"),
        (
            '["exe/a"]\nA = { addr = 0x10, size = 0x10 }\nB = { addr = 0x14 }\n',
            "overlaps A",
        ),
        ('["exe/b"]\nA = { addr = 0x10 }\n', "names no target"),
    ],
)
def test_a_bad_row_names_the_row_and_the_fix(
    tmp_path: Path, body: str, fix: str
) -> None:
    with pytest.raises(LinkError, match=fix):
        symbols.load(table(tmp_path, body))


def test_an_overlap_with_a_recorded_reason_loads(tmp_path: Path) -> None:
    body = '["exe/a"]\nA = { addr = 0x10, size = 0x10 }\nB = { addr = 0x14, alias = true }\n'
    assert len(symbols.load(table(tmp_path, body))["exe/a"]) == 2


def maps(tmp_path: Path, **files: str) -> list[str]:
    (tmp_path / "build/symbols").mkdir(parents=True)
    for name, text in files.items():
        (tmp_path / f"build/symbols/{name}.link").write_text(text)
    return [f"build/symbols/{name}.link" for name in files]


def scan(*needed: str) -> Scan:
    return Scan(frozenset(), {name: "x.o" for name in needed})


def test_resolve_takes_address_names_from_the_name_and_readable_names_from_rows(
    tmp_path: Path,
) -> None:
    found = symbols.resolve(
        tmp_path,
        "exe/a",
        maps(tmp_path, **{"exe+a": "g_One 0x80000010\n"}),
        scan("D_80000020", "g_One"),
        frozenset(),
        {},
    )
    assert found == {"D_80000020": 0x80000020, "g_One": 0x80000010}


def test_resolve_fails_for_an_unknown_name_and_for_two_addresses(
    tmp_path: Path,
) -> None:
    listed = maps(tmp_path, **{"exe+a": "g_Two 0x10\n", "exe+b": "g_Two 0x20\n"})
    with pytest.raises(LinkError, match=r"g_Two .* 2 addresses"):
        symbols.resolve(tmp_path, "exe/a", listed, scan("g_Two"), frozenset(), {})
    with pytest.raises(LinkError, match="g_Nope .* no address"):
        symbols.resolve(tmp_path, "exe/a", listed, scan("g_Nope"), frozenset(), {})


def test_reduced_layout_derives_options_and_owners(tmp_path: Path) -> None:
    from bof3.resolve.layout import read_splat

    folder = tmp_path / "config/emi/battle/battle/03"
    folder.mkdir(parents=True)
    path = folder / "splat.yaml"
    path.write_text("sha1: ab\noptions:\n  subalign: 8\nsegments: []\n")
    _, document = read_splat(path)
    options = document["options"]
    assert document["name"] == "battle_battle_03"
    assert options["src_path"] == "src/overlays/battle/battle/03"
    assert options["target_path"] == "build/bin/emi/battle/battle/03.bin"
    assert options["subalign"] == 8
    assert document["symbol_owners"] == ["exe/slus_004_22", "emi/battle/battle/03"]


def test_logo_never_links_against_the_executable() -> None:
    root = Path(__file__).resolve().parents[2]
    assert symbols.link_owners(root, "exe/logo") == ["exe/logo"]
    assert "exe/slus_004_22" in symbols.link_owners(root, "emi/battle/battle/03")


def test_own_rows_are_proven_against_the_linked_address(tmp_path: Path) -> None:
    (tmp_path / "build/symbols").mkdir(parents=True)
    (tmp_path / "build/symbols/exe+a.link").write_text(
        "g_One 0x80100000\ng_Two 0x80100004\n"
    )
    maps = ["build/symbols/exe+a.link"]
    lines = symbols.own_checks(tmp_path, "exe/a", maps, frozenset({"g_One", "g_Other"}))
    assert len(lines) == 1
    assert lines[0].startswith("ASSERT(g_One == 0x80100000,")
    linked = tmp_path / "a.map"
    linked.write_text(
        "                0x0000000080100000                g_One\n"
        "                0x0000000080100008                g_Two\n"
    )
    [message] = symbols.explain(tmp_path, "exe/a", linked)
    assert "g_Two" in message
    assert "0x80100004" in message
    assert "0x80100008" in message


def test_imported_map_keeps_the_targets_own_address(
    tmp_path: Path, monkeypatch: pytest.MonkeyPatch
) -> None:
    root = table(
        tmp_path,
        '["exe/a"]\nPick = { addr = 0x10 }\nOwn = { addr = 0x20 }\n'
        '["exe/b"]\nPick = { addr = 0x90 }\nOther = { addr = 0x94 }\n',
    )
    (root / "config/exe/b").mkdir()
    (root / "config/exe/b/splat.yaml").write_text("name: b\n")
    monkeypatch.setattr(symbols, "splat_owners", lambda _root, _t: ["exe/a", "exe/b"])
    assert symbols.imported_map(root, "exe/a") == "Other = 0x00000094;\n"
    assert symbols.imported_map(root, "exe/b") == "Own = 0x00000020;\n"
