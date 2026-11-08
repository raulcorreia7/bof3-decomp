"""Prove the C equivalents of the hand-written LZ77 stream decoder against a reference decoder.

``LZ77_DecodeBegin``, ``LZ77_DecodeStep`` and ``func_801642F4`` are assembly in the game
(``HAND_ASM``); their C equivalents under ``#ifdef NON_MATCHING`` compile natively here through
the stand-in header in ``tools/tests/host/lz77``. Synthetic streams run everywhere. Real type-1
payloads come from the extracted disc (``build/disc``) and are skipped when it is absent; no
retail data is committed.
"""

from __future__ import annotations

import json
import random
import shutil
import subprocess
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
HOST = ROOT / "tools/tests/host/lz77"
UNITS = [
    ROOT / "src/engine/slus/LZ77_DecodeBegin.c",
    ROOT / "src/engine/slus/LZ77_DecodeStep.c",
    ROOT / "src/engine/slus/func_801642F4.c",
]
# The longest literal run is 271 bytes and a resumed run is copied without a limit check, so a
# window must hold one; the odd sizes move the window ends across the control bytes.
WINDOWS = (0x400, 0x3F5, 301, 272)
STATES: set[int] = set()
CC = shutil.which("cc") or shutil.which("gcc") or shutil.which("clang")

pytestmark = pytest.mark.skipif(CC is None, reason="no host C compiler")


def reference_decode(payload: bytes) -> bytes:
    """The type-1 codec of ``rebof3-emi/src/lz77.rs`` (``lz77::decode``)."""
    declared = int.from_bytes(payload[:4], "little")
    assert int.from_bytes(payload[4:6], "little") == 0xFFFF
    stream, out, pos = payload[6:], bytearray(), 0
    while pos < len(stream):
        ctrl = stream[pos]
        pos += 1
        if ctrl == 0xFF:
            break
        if ctrl & 0x10:
            length = 0x20 - (ctrl & 0x1F)
            if length == 16:
                length += stream[pos]
                pos += 1
            out += stream[pos : pos + length]
            pos += length
        else:
            distance = 0x800 - (((ctrl & 0xE0) << 3) | stream[pos])
            pos += 1
            code = ctrl & 0x0F
            length = code + 3
            if code == 15:
                length += stream[pos]
                pos += 1
            for _ in range(length):
                out.append(out[-distance])
    assert len(out) == declared
    return bytes(out)


def encode(data: bytes, rng: random.Random) -> bytes:
    """A small type-1 encoder whose frames cover every control shape."""
    out = bytearray(len(data).to_bytes(4, "little") + b"\xff\xff")
    pos, literal = 0, bytearray()

    def flush() -> None:
        nonlocal literal
        while literal:
            run = min(len(literal), 16 + 255)
            if run >= 16:
                out.extend([0x10, run - 16])
            else:
                out.append(0x10 | (0x20 - run))
            out.extend(literal[:run])
            literal = literal[run:]

    while pos < len(data):
        best, distance = 0, 0
        for back in range(1, min(pos, 0x7FF) + 1):
            n = 0
            while (
                pos + n < len(data)
                and n < 3 + 15 + 255
                and data[pos + n] == data[pos + n - back]
            ):
                n += 1
            if n > best:
                best, distance = n, back
        if best >= 3 and rng.random() < 0.9:
            flush()
            low = 0x800 - distance
            code = min(best - 3, 15)
            out.append(((low >> 3) & 0xE0) | code)
            out.append(low & 0xFF)
            if code == 15:
                out.append(best - 18)
            pos += best
        else:
            literal.append(data[pos])
            pos += 1
    flush()
    out.append(0xFF)
    return bytes(out)


@pytest.fixture(scope="module", params=WINDOWS)
def host(
    request: pytest.FixtureRequest, tmp_path_factory: pytest.TempPathFactory
) -> Path:
    exe = tmp_path_factory.mktemp("lz77") / f"lz77_host_{request.param}"
    cmd = [
        CC, "-std=gnu99", "-O1", "-w", "-DNON_MATCHING", f"-DHOST_WINDOW={request.param}u",
        f"-I{HOST}", f"-I{ROOT}/include", str(HOST / "lz77_host.c"), *map(str, UNITS), "-o", str(exe),
    ]  # fmt: skip
    subprocess.run(cmd, check=True, check=False, capture_output=True, text=True)
    return exe


def run_decode(host: Path, tmp_path: Path, payload: bytes) -> bytes:
    """Decode with the C equivalents and record the resume states the window ends produced."""
    src, dst = tmp_path / "in.bin", tmp_path / "out.bin"
    src.write_bytes(payload)
    done = subprocess.run(
        [str(host), "decode", str(src), str(dst)], check=False, capture_output=True, text=True
    )
    assert done.returncode == 0, done.stderr
    STATES.update(int(word) for word in done.stdout.split())
    return dst.read_bytes()


def test_copy_kernel_is_a_forward_copy(host: Path) -> None:
    assert (
        subprocess.run([str(host), "copy"], check=False, capture_output=True, text=True).returncode
        == 0
    )


@pytest.mark.parametrize("seed", range(12))
def test_synthetic_streams_decode_like_the_reference(
    host: Path, tmp_path: Path, seed: int
) -> None:
    rng = random.Random(seed)
    pieces = [
        bytes(rng.randrange(256) for _ in range(rng.randrange(1, 60))) for _ in range(6)
    ]
    data = b"".join(
        rng.choice(pieces) * rng.randrange(1, 40) for _ in range(rng.randrange(5, 60))
    )
    payload = encode(data, rng)
    assert reference_decode(payload) == data
    assert run_decode(host, tmp_path, payload) == data


def type1_payloads() -> list[Path]:
    found = []
    for table in sorted((ROOT / "build/disc").glob("**/emi.json")):
        for entry in json.loads(table.read_text())["entries"]:
            path = table.parent / entry["name"]
            if entry["type"] == 1 and path.is_file():
                found.append(path)
    return found


def test_real_payloads_decode_like_the_reference(host: Path, tmp_path: Path) -> None:
    payloads = type1_payloads()
    if not payloads:
        pytest.skip("no extracted disc under build/disc")
    for path in payloads[:12]:
        payload = path.read_bytes()
        assert run_decode(host, tmp_path, payload) == reference_decode(payload), path


def test_every_resume_state_was_exercised() -> None:
    if len(STATES) == 1:
        pytest.skip("only the fresh state ran")
    assert STATES == {0, 4, 8, 12, 16}
