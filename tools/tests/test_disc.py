from __future__ import annotations

import hashlib
import tomllib
from pathlib import Path

from bof3.core import disc


def manifest_for(folder: Path, track: Path) -> dict:
    payload = (folder / "A/B.BIN").read_bytes()
    text = disc.render(
        title="Game",
        region="NTSC-U",
        serial="SLUS-00001",
        redump="Game (USA)",
        cue=("Game.cue", disc.digest_file(track)),
        tracks=[(1, track.name, "MODE2/2352", disc.digest_file(track))],
        files=[("A/B.BIN", 24, len(payload), hashlib.sha1(payload).hexdigest())],
    )
    return tomllib.loads(text)


def test_a_rendered_manifest_reads_back_and_names_each_mismatch(tmp_path: Path) -> None:
    (tmp_path / "A").mkdir()
    (tmp_path / "A/B.BIN").write_bytes(b"data")
    track = tmp_path / "Game (Track 1).bin"
    track.write_bytes(b"track")
    data = manifest_for(tmp_path, track)
    assert data["disc"]["serial"] == "SLUS-00001"
    assert disc.verify_tracks(data, [track]) == []
    assert disc.verify_files(data, tmp_path) == []
    (tmp_path / "A/B.BIN").write_bytes(b"DATA")
    track.write_bytes(b"other")
    assert disc.verify_files(data, tmp_path) == ["A/B.BIN: SHA-1 differs"]
    assert disc.verify_tracks(data, [track]) == [
        f"{track.name}: SHA-1 {hashlib.sha1(b'other').hexdigest()}, expected "
        f"{hashlib.sha1(b'track').hexdigest()}"
    ]
    (tmp_path / "A/B.BIN").unlink()
    assert disc.verify_files(data, tmp_path) == ["A/B.BIN: missing"]


def test_the_shallowest_complete_set_wins(tmp_path: Path) -> None:
    (tmp_path / "deep").mkdir()
    for folder in (tmp_path, tmp_path / "deep"):
        (folder / "t.bin").write_bytes(b"")
        (folder / "g.cue").write_text('FILE "t.bin" BINARY\n  TRACK 01 MODE2/2352\n')
    (tmp_path / "broken.cue").write_text('FILE "gone.bin" BINARY\n')
    cue, bins = disc.disc_set(tmp_path) or (None, [])
    assert cue == tmp_path / "g.cue"
    assert bins == [(tmp_path / "t.bin").resolve()]
