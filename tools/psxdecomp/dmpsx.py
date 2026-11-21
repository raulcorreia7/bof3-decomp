"""Rewrite PsyQ DMPSX placeholder words into real GTE cop2 instructions.

PsyQ's ``inline_c.h`` emits each Type 2 GTE command as an invalid SPECIAL word
with funct ``0x3f``; Sony's ``DMPSX.EXE`` replaced those placeholders in the
object after the assembler. This pass does the same rewrite on the assembly
text between cc1/maspsx and GNU as, so the C sources keep the stock SDK macros.

The command table is the cross-checked table in
``tasks/psx-idioms-1020/catalog.md`` section 1.2: 65 command macros, plus the
arg-taking MVMVA/SQR/OP/GPF/GPL bases of ``inline_a.h``. A placeholder's
command index is ``(word >> 6) & 0xFFF``; DMPSX moves the argument bits from
25..18 to their real fields at 19..10.

An unknown placeholder is an error: emitting an untranslated fake command would hide it.
``tools/cc.py`` calls :func:`rewrite_text` on every compile.
"""

from __future__ import annotations

import re

#: A placeholder keeps bits 31-26 clear and funct (bits 5-0) at 0x3f.
_PLACEHOLDER_MASK = 0xFC00003F
_PLACEHOLDER = 0x3F

#: Command index -> retail word. Fixed commands carry zero argument bits; the
#: last five are the bases the arg-taking ``inline_a.h`` macros OR into.
_COMMANDS: dict[int, int] = {
    0x01: 0x4A180001,  # gte_rtps
    0x02: 0x4A280030,  # gte_rtpt
    0x03: 0x4A480012,  # gte_rt
    0x04: 0x4A486012,  # gte_rtv0
    0x05: 0x4A48E012,  # gte_rtv1
    0x06: 0x4A496012,  # gte_rtv2
    0x07: 0x4A49E012,  # gte_rtir
    0x08: 0x4A41E012,  # gte_rtir_sf0
    0x09: 0x4A480012,  # gte_rtv0tr
    0x0A: 0x4A488012,  # gte_rtv1tr
    0x0B: 0x4A490012,  # gte_rtv2tr
    0x0C: 0x4A498012,  # gte_rtirtr
    0x0D: 0x4A482012,  # gte_rtv0bk
    0x0E: 0x4A48A012,  # gte_rtv1bk
    0x0F: 0x4A492012,  # gte_rtv2bk
    0x10: 0x4A49A012,  # gte_rtirbk
    0x15: 0x4A4A6412,  # gte_ll
    0x16: 0x4A4A6012,  # gte_llv0
    0x17: 0x4A4AE012,  # gte_llv1
    0x18: 0x4A4B6012,  # gte_llv2
    0x19: 0x4A4BE012,  # gte_llir
    0x1A: 0x4A4A0012,  # gte_llv0tr
    0x1B: 0x4A4A8012,  # gte_llv1tr
    0x1C: 0x4A4B0012,  # gte_llv2tr
    0x1D: 0x4A4B8012,  # gte_llirtr
    0x1E: 0x4A4A2012,  # gte_llv0bk
    0x1F: 0x4A4AA012,  # gte_llv1bk
    0x20: 0x4A4B2012,  # gte_llv2bk
    0x21: 0x4A4BA012,  # gte_llirbk
    0x26: 0x4A4DA412,  # gte_lc
    0x27: 0x4A4C6012,  # gte_lcv0
    0x28: 0x4A4CE012,  # gte_lcv1
    0x29: 0x4A4D6012,  # gte_lcv2
    0x2A: 0x4A4DE012,  # gte_lcir
    0x2B: 0x4A4C0012,  # gte_lcv0tr
    0x2C: 0x4A4C8012,  # gte_lcv1tr
    0x2D: 0x4A4D0012,  # gte_lcv2tr
    0x2E: 0x4A4D8012,  # gte_lcirtr
    0x2F: 0x4A4C2012,  # gte_lcv0bk
    0x30: 0x4A4CA012,  # gte_lcv1bk
    0x31: 0x4A4D2012,  # gte_lcv2bk
    0x32: 0x4A4DA012,  # gte_lcirbk
    0x37: 0x4A680029,  # gte_dpcl
    0x38: 0x4A780010,  # gte_dpcs
    0x39: 0x4AF8002A,  # gte_dpct
    0x3A: 0x4A980011,  # gte_intpl
    0x3B: 0x4AA80428,  # gte_sqr12
    0x3C: 0x4AA00428,  # gte_sqr0
    0x3D: 0x4AC8041E,  # gte_ncs
    0x3E: 0x4AD80420,  # gte_nct
    0x3F: 0x4AE80413,  # gte_ncds
    0x40: 0x4AF80416,  # gte_ncdt
    0x41: 0x4B08041B,  # gte_nccs
    0x42: 0x4B18043F,  # gte_ncct
    0x43: 0x4B280414,  # gte_cdp
    0x44: 0x4B38041C,  # gte_cc
    0x45: 0x4B400006,  # gte_nclip
    0x46: 0x4B58002D,  # gte_avsz3
    0x47: 0x4B68002E,  # gte_avsz4
    0x48: 0x4B78000C,  # gte_op12
    0x49: 0x4B70000C,  # gte_op0
    0x4A: 0x4B98003D,  # gte_gpf12
    0x4B: 0x4B90003D,  # gte_gpf0
    0x4C: 0x4BA8003E,  # gte_gpl12
    0x4D: 0x4BA0003E,  # gte_gpl0
    0x4E: 0x4A400012,  # MVMVA base, args in bits 25..18
    0x4F: 0x4AA00428,  # SQR base
    0x50: 0x4B70000C,  # OP base
    0x51: 0x4B90003D,  # GPF base
    0x52: 0x4BA0003E,  # GPL base
}

#: `.word` with one literal; cc1 emits hex, maspsx keeps it.
_WORD = re.compile(r"(\.word[ \t]+)(0x[0-9a-fA-F]+|[0-9]+)")

#: Data directives that start a section. A placeholder is an instruction, so a
#: data word is never rewritten even when its bits match the placeholder mask.


class UnknownPlaceholder(ValueError):
    """A word looks like a DMPSX placeholder but has no command index."""


def _arguments(word: int) -> int:
    return (
        (((word >> 18) & 1) << 10)
        | (((word >> 19) & 3) << 13)
        | (((word >> 21) & 3) << 15)
        | (((word >> 23) & 3) << 17)
        | (((word >> 25) & 1) << 19)
    )


def translate(word: int) -> int | None:
    """Return the retail word for a DMPSX placeholder, or None for any other word."""
    if word & _PLACEHOLDER_MASK != _PLACEHOLDER:
        return None
    index = (word >> 6) & 0xFFF
    base = _COMMANDS.get(index)
    if base is None:
        raise UnknownPlaceholder(f"unknown GTE placeholder 0x{word:08x}")
    return base | _arguments(word)


def _section_of(line: str, current: str) -> str:
    """Return the section a directive line selects, or the one already current."""
    stripped = line.strip()
    if stripped.startswith(".section"):
        parts = stripped.split(None, 1)
        return parts[1].split(",", 1)[0].strip() if len(parts) == 2 else current
    if stripped in {".text", ".data", ".rdata", ".rodata", ".sdata", ".bss"}:
        return stripped
    return current


def rewrite_text(text: str) -> tuple[str, int]:
    """Return ``text`` with every placeholder in code rewritten, and the count."""
    for word in _WORD.finditer(text):
        if int(word.group(2), 0) & _PLACEHOLDER_MASK == _PLACEHOLDER:
            break
    else:
        return text, 0
    pieces: list[str] = []
    count = 0
    section = ".text"
    line = 1
    for line_text in text.splitlines(keepends=True):
        section = _section_of(line_text, section)
        if not section.startswith(".text"):
            pieces.append(line_text)
            line += 1
            continue

        def rewrite(match: re.Match[str], number: int = line) -> str:
            nonlocal count
            try:
                real = translate(int(match.group(2), 0))
            except UnknownPlaceholder as exc:
                raise UnknownPlaceholder(f"line {number}: {exc}") from exc
            if real is None:
                return match.group(0)
            count += 1
            return f"{match.group(1)}0x{real:08X}"

        pieces.append(_WORD.sub(rewrite, line_text))
        line += 1
    return "".join(pieces), count
