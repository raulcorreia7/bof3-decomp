from __future__ import annotations

from pathlib import Path

import pytest
from fixture import put_symbols

from bof3.link import symbols
from bof3.link.symbols import LinkError, Scan


def table(tmp_path: Path, body: str) -> Path:
    (tmp_path / "config/exe/a").mkdir(parents=True)
    (tmp_path / "config/exe/a/splat.yaml").write_text("name: a\n")
    put_symbols(tmp_path, body)
    return tmp_path


@pytest.mark.parametrize(
    "body, fix",
    [
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


def maps(tmp_path: Path, **files: str) -> list[str]:
    (tmp_path / "build/symbols").mkdir(parents=True)
    for name, text in files.items():
        (tmp_path / f"build/symbols/{name}.link").write_text(text)
    return [f"build/symbols/{name}.link" for name in files]


def scan(*needed: str) -> Scan:
    return Scan(frozenset(), {name: "x.o" for name in needed})


def test_resolve_fails_for_an_unknown_name_and_for_two_addresses(
    tmp_path: Path,
) -> None:
    listed = maps(tmp_path, **{"exe+a": "g_Two 0x10\n", "exe+b": "g_Two 0x20\n"})
    with pytest.raises(LinkError, match=r"g_Two .* 2 addresses"):
        symbols.resolve(tmp_path, "exe/a", listed, scan("g_Two"), frozenset(), {})
    with pytest.raises(LinkError, match="g_Nope .* no address"):
        symbols.resolve(tmp_path, "exe/a", listed, scan("g_Nope"), frozenset(), {})


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
        " .text          0x80100000        0x10 src+a.c.o\n"
        "                0x80100000                g_One\n"
        "                0x80100008                g_Two\n"
    )
    [message] = symbols.explain(tmp_path, "exe/a", linked)
    assert "g_Two" in message
    assert "0x80100004" in message
    assert "0x80100008" in message


def test_merge_driver_unions_rows_in_address_order(tmp_path) -> None:
    import merge_symbols

    def write(name: str, *rows: str) -> str:
        path = tmp_path / name
        path.write_text('["a/00"]\n' + "".join(f"{row}\n" for row in rows))
        return str(path)

    one, two, three = (
        f"{n} = {{ addr = 0x{a} }}"
        for n, a in (("One", "10"), ("Two", "20"), ("Three", "30"))
    )
    base = write("base", one)
    ours = write("ours", one, three)
    assert merge_symbols.main(base, ours, write("theirs", one, two)) == 0
    assert (tmp_path / "ours").read_text() == f'["a/00"]\n{one}\n{two}\n{three}\n'
