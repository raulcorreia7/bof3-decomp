import json
from pathlib import Path

import pytest

from bof3.emi.catalog import entry_for


def archive(root: Path) -> Path:
    folder = root / "build/disc/BIN/TEST/ARC"
    folder.mkdir(parents=True)
    (folder / "3.bin").write_bytes(b"\x00\x00\x00\x00")
    (folder / "emi.json").write_text(
        json.dumps(
            {
                "entries": [
                    {"index": 3, "name": "3.bin", "type": 0, "ram_ptr": 0x80010000}
                ]
            }
        )
    )
    return folder


def test_entry_for_reads_the_extracted_archive(tmp_path):
    archive(tmp_path)
    entry = entry_for(tmp_path, "BIN/TEST/ARC.EMI#3")
    assert entry["payload_path"].name == "3.bin"
    assert entry["size"] == 4
    assert entry["load_address"] == 0x80010000
    assert entry["payload_kind"] == "ram"


def test_entry_for_names_a_missing_slot(tmp_path):
    archive(tmp_path)
    with pytest.raises(ValueError, match="found 0"):
        entry_for(tmp_path, "BIN/TEST/ARC.EMI#4")
