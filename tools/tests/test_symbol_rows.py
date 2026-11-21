from __future__ import annotations

from bof3.source import symtab


def table(*rows: str) -> str:
    return "\n".join(['["exe/a"]', *rows, "", '["exe/c"]', "Z = { addr = 0x1 }", ""])


def test_a_row_lands_in_address_order() -> None:
    text = table("A = { addr = 0x10 }", "C = { addr = 0x30 }")
    row = symtab.format_row("B", 0x20, type="func", size=8, source="seen at x")
    assert (
        row
        == 'B = { addr = 0x00000020, type = "func", size = 0x8, source = "seen at x" }'
    )
    out = symtab.add_row(text, "exe/a", "B", row, 0x20).split("\n")
    assert [line[:1] for line in out[1:4]] == ["A", "B", "C"]
    assert out[-3:] == ['["exe/c"]', "Z = { addr = 0x1 }", ""]
