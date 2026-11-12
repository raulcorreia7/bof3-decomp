"""The symbol-table check reports ordering as a failure and the owner lists as text."""

from __future__ import annotations

import argparse
from pathlib import Path

import pytest

import symbol
from bof3.link.symbols import Entry


def test_an_out_of_order_table_fails(
    monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    entries = [Entry("B", 0x20), Entry("A", 0x10, source="why")]
    monkeypatch.setattr(symbol.symbols, "load", lambda _root: {"exe/a": entries})
    assert symbol.check(argparse.Namespace()) == 1
    out = capsys.readouterr().out
    assert out.startswith("order\texe/a\tA 0x00000010 after B 0x00000020")


def test_repeats_and_unused_aliases_are_listed(
    monkeypatch: pytest.MonkeyPatch, capsys: pytest.CaptureFixture[str]
) -> None:
    entries = [
        Entry("Name", 0x10, source="why"),
        Entry("Alias", 0x10, "u8", 1, "why", True),
        Entry("Bare", 0x20),
    ]
    monkeypatch.setattr(
        symbol.symbols,
        "load",
        lambda _root: {"exe/a": entries, "emi/b": [Entry("Name", 0x10, source="why")]},
    )
    monkeypatch.setattr(symbol, "mentioned", lambda _names: set())
    assert symbol.check(argparse.Namespace()) == 0
    out = capsys.readouterr().out
    assert "repeat\t2\tName\t0x00000010\t-\texe/a emi/b" in out
    assert "alias-unused\texe/a\tAlias 0x00000010" in out
    assert "no-source\texe/a\tBare 0x00000020" in out


def test_the_shipped_table_is_ordered() -> None:
    root = Path(__file__).resolve().parents[2]
    for target, entries in symbol.symbols.load(root).items():
        addresses = [entry.addr for entry in entries]
        assert addresses == sorted(addresses), target
