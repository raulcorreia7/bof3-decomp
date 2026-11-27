from pathlib import Path

from bof3.link import symbols
from bof3.source import hints
from bof3.source.index import Func

FUNC = Func(
    image="exe/a",
    name="func_80140000",
    addr=0x80140000,
    size=0x20,
    words=(),
    sha1="",
    status="ASM",
    src="src/a/func_80140000.c",
)


def context(table=None, splat=""):
    return hints.Context(Path("."), FUNC, table or {}, splat)


def run(detector, text, **kwargs):
    return detector(hints.parse(text), context(**kwargs))


def test_scratchpad_counts_the_cell_and_the_reloads():
    text = """
    lui $v1, (0x1F800044 >> 16)
    lw $v1, (0x1F800044 & 0xFFFF)($v1)
    lui $v1, (0x1F800044 >> 16)
    lw $v1, (0x1F800044 & 0xFFFF)($v1)
    """
    lines = run(hints.scratchpad, text)
    assert len(lines) == 1
    assert "0x1F800044" in lines[0]
    assert "reloaded" in lines[0]


def test_addresses_resolve_through_the_table():
    entry = symbols.Entry("g_Game", 0x80146110, type="PartyMember", size=0x40)
    text = "lui $v0, 0x8014\naddiu $v0, $v0, 0x6110"
    lines = run(hints.addresses, text, table={"exe/a": [entry]})
    assert "0x80146110" in lines[0]
    assert "g_Game" in lines[0]
