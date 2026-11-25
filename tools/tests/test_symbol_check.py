"""The symbol-table check reports ordering as a failure and the owner lists as text."""

from __future__ import annotations

import subprocess
from pathlib import Path

import pytest
from fixture import put_symbols

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


def test_alias_liveness_excludes_tables_but_keeps_source_and_config(
    tmp_path: Path,
) -> None:
    subprocess.run(["git", "init", "-q", str(tmp_path)], check=True)
    put_symbols(
        tmp_path,
        '["exe/a"]\n'
        'TableOnly = { addr = 0x80000000, alias = true, source = "test" }\n'
        'SourceAlias = { addr = 0x80000004, alias = true, source = "test" }\n'
        'ConfigAlias = { addr = 0x80000008, alias = true, source = "test" }\n',
    )
    files = {
        "config/exe/a/splat.yaml": "segments: []\n",
        "config/sdk/example.toml": 'exports = ["ConfigAlias"]\n',
        "src/a.c": "extern int SourceAlias;\nint f(void) { return SourceAlias; }\n",
    }
    for relative, text in files.items():
        path = tmp_path / relative
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_text(text)
    subprocess.run(["git", "-C", str(tmp_path), "add", "."], check=True)

    report = check.check(Context(tmp_path))
    assert not report.failed
    assert report.findings == ["alias-unused\texe/a\tTableOnly 0x80000000"]
