"""The symbol-table check reports ordering as a failure and the owner lists as text."""

from __future__ import annotations

import pytest

from bof3.link import symbols
from bof3.link.symbols import Entry
from bof3.symbols import check
from bof3.symbols.context import Context


def test_an_out_of_order_table_fails(monkeypatch: pytest.MonkeyPatch) -> None:
    entries = [Entry("B", 0x20), Entry("A", 0x10, source="why")]
    monkeypatch.setattr(symbols, "load", lambda _root: {"exe/a": entries})
    report = check.check(Context())
    assert report.failed
    assert report.findings[0] == "order\texe/a\tA 0x00000010 after B 0x00000020"
