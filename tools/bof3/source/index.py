"""The function index: one record per function of every linked image.

It reads ``build/meson/<image>.elf`` and ``.map`` (after ``meson compile``) and caches the
records in ``build/func_index.json.gz``. The cache is rebuilt when an ELF is newer.
"""

from __future__ import annotations

import bisect
import gzip
import hashlib
import json
import re
import struct
import subprocess
from concurrent.futures import ThreadPoolExecutor
from dataclasses import dataclass
from pathlib import Path

from bof3.source.ctext import read

CACHE = "build/func_index.json.gz"
OBJDUMP = "bin/internal/binutils/objdump"
_SECTION = re.compile(
    r"^ (\.text\S*)\s+0x([0-9a-f]+)\s+0x([0-9a-f]+)\s+(\S+\.o)\s*$", re.M
)
_INCLUDE_ASM = re.compile(r"^\s*INCLUDE_ASM\(\s*(\w+)\s*\)", re.M)


@dataclass(frozen=True, slots=True)
class Func:
    """One function. ``status`` is ``C`` (lifted), ``ASM`` (still assembly) or ``LIB`` (SDK)."""

    image: str
    name: str
    addr: int
    size: int
    words: tuple[int, ...]
    sha1: str
    status: str
    src: str | None  # the C file, for a lifted function or an INCLUDE_ASM stub

    @property
    def ref(self) -> str:
        """The project's ``TARGET@0xADDRESS`` form."""
        return f"{self.image}@0x{self.addr:08X}"


def opcode_token(word: int) -> int:
    """Return the instruction's opcode alone: registers, immediates and targets masked."""
    if word == 0:
        return 0
    op = word >> 26
    if op == 0:
        return 64 + (word & 63)
    if op == 1:
        return 128 + ((word >> 16) & 31)
    if op in (0x10, 0x12):
        if word & (1 << 25):
            return 256 + 64 * (op == 0x12) + (word & 63)
        return 192 + 32 * (op == 0x12) + ((word >> 21) & 31)
    return op + 1


def opcode_string(words: tuple[int, ...]) -> str:
    """Return the opcode tokens as one string, for sequence-similarity scorers."""
    return "".join(chr(0x100 + opcode_token(w)) for w in words)


def _objdump(root: Path, *args: str) -> list[str]:
    result = subprocess.run(
        [str(root / OBJDUMP), *args], capture_output=True, text=True, check=True
    )
    return result.stdout.splitlines()


def _one_image(root: Path, elf: Path) -> list[dict]:
    image = elf.stem.replace("+", "/")
    funcs = []
    for line in _objdump(root, "-t", str(elf)):
        p = line.split()
        if len(p) >= 5 and "F" in p[1:3] and p[-3].startswith("."):
            funcs.append((p[-1], int(p[0], 16), int(p[-2], 16)))
    if not funcs:
        return []
    words = {}
    for line in _objdump(root, "-d", str(elf)):
        m = re.match(r"^\s*([0-9a-f]+):\t([0-9a-f]{8}) ", line)
        if m:
            words[int(m.group(1), 16)] = int(m.group(2), 16)
    text = elf.with_suffix(".map").read_text(errors="replace")
    text = text[text.find("Linker script and memory map") :]
    spans = sorted(
        (int(a, 16), int(s, 16), o)
        for _, a, s, o in _SECTION.findall(text)
        if int(s, 16) and int(a, 16)
    )
    starts = [s[0] for s in spans]
    stubs: dict[str, set[str]] = {}
    out = []
    for name, addr, size in funcs:
        ws = [words.get(a, 0xFFFFFFFF) for a in range(addr, addr + size, 4)]
        i = bisect.bisect_right(starts, addr) - 1
        obj = spans[i][2] if i >= 0 and addr < spans[i][0] + spans[i][1] else None
        src = obj[:-2].replace("+", "/") if obj and obj.endswith(".c.o") else None
        if src and src not in stubs:
            try:
                stubs[src] = set(_INCLUDE_ASM.findall(read(root, src)))
            except OSError:
                stubs[src] = set()
        asm = bool(obj and obj.startswith("asm+")) or (
            src is not None and name in stubs[src]
        )
        lib = obj is not None and not asm and src is None
        out.append(
            {
                "name": name,
                "addr": addr,
                "size": size,
                "words": struct.pack(f"<{len(ws)}I", *ws).hex(),
                "status": "LIB" if lib else "ASM" if asm else "C",
                "src": src,
                "image": image,
            }
        )
    return out


def _decode(row: dict) -> Func:
    raw = bytes.fromhex(row["words"])
    words = struct.unpack(f"<{len(raw) // 4}I", raw)
    return Func(
        row["image"],
        row["name"],
        row["addr"],
        row["size"],
        words,
        hashlib.sha1(raw).hexdigest()[:16],
        row["status"],
        row["src"],
    )


def load_index(root: Path, rebuild: bool = False) -> list[Func]:
    """Return every function of every built image, rebuilding a stale cache."""
    cache = root / CACHE
    elfs = sorted((root / "build/meson").glob("*.elf"))
    if not elfs:
        raise SystemExit("index: no built images. Run: meson compile -C build/meson")
    if (
        rebuild
        or not cache.is_file()
        or cache.stat().st_mtime < max(e.stat().st_mtime for e in elfs)
    ):
        with ThreadPoolExecutor() as pool:
            rows = [
                row
                for part in pool.map(lambda e: _one_image(root, e), elfs)
                for row in part
            ]
        with gzip.open(cache, "wt", encoding="utf-8") as out:
            json.dump(rows, out, separators=(",", ":"))
    else:
        with gzip.open(cache, "rt", encoding="utf-8") as stream:
            rows = json.load(stream)
    return [_decode(row) for row in rows]


def find(funcs: list[Func], spec: str) -> Func:
    """Resolve ``TARGET@NAME`` or ``TARGET@0xADDRESS`` to one function."""
    if "@" not in spec:
        raise SystemExit(f"{spec}: write TARGET@NAME or TARGET@0xADDRESS")
    image, _, ident = spec.partition("@")
    for f in funcs:
        if f.image == image and (f.name == ident or _same_address(f, ident)):
            return f
    raise SystemExit(f"not in the index: {spec}")


def _same_address(f: Func, ident: str) -> bool:
    try:
        return f.addr == int(ident, 16)
    except ValueError:
        return False
