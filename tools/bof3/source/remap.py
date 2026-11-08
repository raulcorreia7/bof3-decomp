"""Align a template's instructions with a target's and turn the differences into C edits.

A template is a matched function whose code looks like an assembly function's. When only a
relocation symbol (``%hi/%lo(D_x)``, ``jal func_x``) or one immediate differs, the template's C
works for the target after a rename or a new literal. This module reads both sides symbolically:
the template from its object's relocations, the target from its assembly listing.
"""

from __future__ import annotations

import difflib
import functools
import re
import subprocess
from dataclasses import dataclass, field
from pathlib import Path

from bof3.source.ctext import mask
from bof3.source.index import OBJDUMP

JUMP_OPS = (2, 3)
_HEADER = re.compile(r"^([0-9a-f]+) <(\S+)>:$")
_RELOC = re.compile(r"^\s+([0-9a-f]+):\s+R_MIPS_(\w+)\s+(\S+)")
_WORD = re.compile(r"^\s*([0-9a-f]+):\t([0-9a-f]{8})\s")
_ASM_LINE = re.compile(r"^\s*/\*\s+\w+\s+([0-9A-F]{8})\s+[0-9A-F]{8}\s*\*/\s+(.*)$")
_ASM_SYM = re.compile(
    r"%(hi|lo|gp_rel)\(\s*(\w+)(?:\s*\+\s*(0x[0-9A-Fa-f]+|\d+))?\s*\)"
)
_ASM_JUMP = re.compile(r"^(?:jal|j)\s+(\S+)")
_DEFINE = re.compile(
    r"^[ \t]*#[ \t]*define[ \t]+(\w+)[ \t]+(0[xX][0-9a-fA-F]+|\d+)[uUlL]*[ \t]*(?:/\*.*)?$",
    re.M,
)
_NUMBER = re.compile(r"\b(0[xX][0-9a-fA-F]+|\d+)([uUlL]*)\b")


@dataclass(frozen=True, slots=True)
class Insn:
    """One instruction: its word and the symbol it relocates against.

    ``sym`` is None without a relocation and ``""`` for a local one (a section, a label);
    ``addend`` is the offset added to the symbol of a low-half or gp-relative use.
    """

    word: int
    sym: str | None = None
    addend: int = 0


@dataclass(slots=True)
class Plan:
    """What to change in the template to reach the target."""

    symbols: dict[str, str] = field(default_factory=dict)  # template symbol -> target
    keep: set[str] = field(
        default_factory=set
    )  # template symbols the target must declare
    literals: list[tuple[int, int]] = field(
        default_factory=list
    )  # (template, target) imm16
    hard: int = 0  # positions that no rename or literal explains
    first_hard: str = ""

    @property
    def edits(self) -> bool:
        """True when the template body needs a change."""
        return bool(self.symbols or self.literals)

    sites: int = 0  # positions explained by a symbol rename

    @property
    def total(self) -> int:
        """Instructions that differ before any edit."""
        return self.hard + len(self.literals) + self.sites


def _norm(words: tuple[int, ...]) -> list[int]:
    """Return the words with a jump's target removed."""
    return [-(w >> 26) if w >> 26 in JUMP_OPS else w for w in words]


def diff_count(template: tuple[int, ...], target: tuple[int, ...]) -> int:
    """Return how many instructions differ, ignoring jump targets."""
    a, b = _norm(template), _norm(target)
    matched = sum(
        m.size
        for m in difflib.SequenceMatcher(
            None, a, b, autojunk=False
        ).get_matching_blocks()
    )
    return max(len(a), len(b)) - matched


def template_insns(text: str, name: str, count: int) -> list[Insn]:
    """Pick ``count`` instructions of function ``name`` from ``objdump -dr`` of an object.

    objdump prints each relocation under its instruction; its offset is from the section start.
    """
    words: list[tuple[int, int]] = []
    relocs: dict[int, tuple[str, str]] = {}
    start = None
    for line in text.splitlines():
        m = _HEADER.match(line)
        if m and m.group(2) == name:
            start = int(m.group(1), 16)
            continue
        m = _WORD.match(line)
        if m:
            words.append((int(m.group(1), 16), int(m.group(2), 16)))
            continue
        m = _RELOC.match(line)
        if m:
            relocs[int(m.group(1), 16)] = (m.group(2), m.group(3))
    out = []
    for offset, word in words:
        if start is None or not start <= offset < start + 4 * count:
            continue
        kind, sym = relocs.get(offset, ("", None))
        if sym is None:
            out.append(Insn(word))
            continue
        local = "" if sym.startswith(".") else sym
        low = kind in ("LO16", "GPREL16")
        addend = word & 0xFFFF
        out.append(
            Insn(word, local, addend - 0x10000 * (addend >= 0x8000) if low else 0)
        )
    return out if len(out) == count else []


def target_insns(words: tuple[int, ...], listing: list[str]) -> list[Insn]:
    """Pair each target word with the symbol its assembly line names."""
    out = []
    for word, line in zip(words, listing, strict=True):
        m = _ASM_SYM.search(line)
        if m:
            kind, sym, add = m.groups()
            addend = int(add, 0) if add and kind != "hi" else 0
            out.append(Insn(word, sym, addend))
            continue
        m = _ASM_JUMP.match(line.strip())
        if m:
            sym = m.group(1)
            out.append(Insn(word, "" if sym.startswith(".") else sym))
            continue
        out.append(Insn(word))
    return out


def align(
    template: list[Insn], target: list[Insn], linked: tuple[int, ...]
) -> Plan | None:
    """Compare two equal-length instruction lists; None when the lengths differ.

    ``linked`` holds the template's words as linked in its image: where they equal the
    target's, the symbols name one address and the instruction needs no edit beyond the name.
    """
    if len(template) != len(target) or len(linked) != len(target):
        return None
    plan = Plan()
    for i, (t, g) in enumerate(zip(template, target, strict=True)):
        if t.sym is not None and linked[i] == g.word:
            if t.sym and g.sym and t.sym != g.sym:
                if plan.symbols.setdefault(t.sym, g.sym) != g.sym:
                    plan.hard += 1
                    plan.first_hard = (
                        plan.first_hard or f"+0x{4 * i:X} {t.sym} maps to two symbols"
                    )
                else:
                    plan.sites += 1
            elif t.sym:
                plan.keep.add(t.sym)
            continue
        if t.sym is None and g.sym is None:
            if t.word == g.word:
                continue
            if t.word >> 16 == g.word >> 16 and t.word >> 26 not in JUMP_OPS:
                plan.literals.append((t.word & 0xFFFF, g.word & 0xFFFF))
                continue
            why = f"+0x{4 * i:X} word 0x{t.word:08X} vs 0x{g.word:08X}"
        elif t.sym is None or g.sym is None:
            why = f"+0x{4 * i:X} relocation on one side only"
        else:
            keep = 0xFC000000 if t.word >> 26 in JUMP_OPS else 0xFFFF0000
            if (t.word ^ g.word) & keep or t.addend != g.addend:
                why = f"+0x{4 * i:X} operands differ beside the symbol"
            elif t.sym == g.sym:
                continue
            elif not t.sym or not g.sym:
                why = f"+0x{4 * i:X} local against global symbol"
            elif plan.symbols.setdefault(t.sym, g.sym) != g.sym:
                why = f"+0x{4 * i:X} {t.sym} maps to two symbols"
            else:
                plan.sites += 1
                continue
        plan.hard += 1
        plan.first_hard = plan.first_hard or why
    return plan


def rename(body: str, old: str, new: str) -> str | None:
    """Return ``body`` with the identifier ``old`` as ``new``; None if ``old`` is absent."""
    pattern = re.compile(r"\b" + re.escape(old) + r"\b")
    return pattern.sub(new, body) if pattern.search(body) else None


def _signed(value: int) -> int:
    return value - 0x10000 if value >= 0x8000 else value


def substitute_literals(body: str, pairs: list[tuple[int, int]]) -> str | None:
    """Replace each template literal by the target's; None unless each is found exactly once.

    A literal may be the signed immediate, the unsigned one, or the negated one (a subtraction).
    """
    spans: list[tuple[int, int, str]] = []
    targets: dict[int, set[int]] = {}
    for want, got in pairs:
        targets.setdefault(want, set()).add(got)
    if any(len(v) > 1 for v in targets.values()):
        return None
    for want, (got,) in ((w, tuple(v)) for w, v in targets.items()):
        forms = {_signed(want): _signed(got), want: got, -_signed(want): -_signed(got)}
        hits = [
            (m, forms[int(m.group(1), 0)])
            for m in _NUMBER.finditer(mask(body))
            if int(m.group(1), 0) in forms
        ]
        if len(hits) != pairs.count((want, got)):
            return None
        for m, value in hits:
            is_hex = m.group(1).lower().startswith("0x") and value >= 0
            text = f"0x{value:X}" if is_hex else str(value)
            spans.append((m.start(1), m.end(1), text))
    out, last = [], 0
    for start, end, text in sorted(spans):
        if start < last:
            return None
        out += [body[last:start], text]
        last = end
    out.append(body[last:])
    return "".join(out)


def statements(text: str) -> list[str]:
    """Return the top-level declaration statements of C text, one string each."""
    masked = mask(text)
    masked = re.sub(
        r"^[ \t]*#.*(?:\\\n.*)*$",
        lambda m: re.sub(r"[^\n]", " ", m.group(0)),
        masked,
        flags=re.M,
    )
    out, start, depth, body = [], 0, 0, False
    for i, ch in enumerate(masked):
        if ch == "{":
            if depth == 0:
                body = masked[start:i].rstrip().endswith(")")
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0 and body:
                start, body = i + 1, False
        elif ch == ";" and depth == 0:
            out.append(" ".join(masked[start : i + 1].split()))
            start = i + 1
    return out


def declaration(text: str, name: str) -> str | None:
    """Return the one-line ``extern`` or prototype that declares ``name``, or None."""
    for stmt in statements(text):
        if "," in stmt.split("(")[0] or not re.search(
            r"\b" + re.escape(name) + r"\b", stmt
        ):
            continue
        if stmt.startswith("extern ") or re.search(
            r"\b" + re.escape(name) + r"\s*\(", stmt
        ):
            if not stmt.startswith(("typedef", "static")) and "=" not in stmt:
                return stmt
    return None


def read_listing(root: Path, image: str) -> dict[int, str]:
    """Return ``{address: instruction text}`` of the image's assembly files."""
    return _listing(str(root), image)


@functools.lru_cache(maxsize=2)
def _listing(root: str, image: str) -> dict[int, str]:
    lines: dict[int, str] = {}
    base = Path(root) / "asm" / image
    for path in [*sorted(base.glob("*.s")), *sorted((base / "hand").glob("*.s"))]:
        for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
            m = _ASM_LINE.match(line)
            if m:
                lines[int(m.group(1), 16)] = m.group(2).strip()
    return lines


@functools.lru_cache(maxsize=64)
def _disassembly(root: str, obj: str) -> str:
    path = Path(root) / "build/meson" / obj
    if not path.is_file():
        return ""
    return subprocess.run(
        [str(Path(root) / OBJDUMP), "-dr", str(path)],
        capture_output=True,
        text=True,
        check=False,
    ).stdout


def object_insns(root: Path, obj: str, name: str, count: int) -> list[Insn] | None:
    """Return the ``count`` instructions of ``name`` in ``build/meson/<obj>`` with relocations."""
    return template_insns(_disassembly(str(root), obj), name, count) or None


def macro_edits(
    body: str, pairs: list[tuple[int, int]], texts: list[str]
) -> tuple[list[tuple[int, int]], list[str]]:
    """Explain literals that the template writes as a numeric macro of its own image.

    Return the pairs still to substitute and one ``#define`` per macro, valued as the target.
    """
    defines = numeric_defines(texts)
    words = re.findall(r"\b[A-Za-z_]\w*\b", mask(body))
    left, out = list(pairs), []
    for want, got in dict.fromkeys(pairs):
        forms = {_signed(want): _signed(got), want: got, -_signed(want): -_signed(got)}
        names = {
            w: (defines[w], forms[int(defines[w], 0)])
            for w in set(words)
            if w in defines and int(defines[w], 0) in forms
        }
        if len(names) != 1 or any(
            words.count(w) != pairs.count((want, got)) for w in names
        ):
            continue
        ((name, (old, value)),) = names.items()
        hexed = old.lower().startswith("0x") and value >= 0
        out.append(f"#define {name} {f'0x{value:X}' if hexed else value}")
        left = [p for p in left if p != (want, got)]
    return left, out


def numeric_defines(texts: list[str]) -> dict[str, str]:
    """Return ``{name: value text}`` of the numeric ``#define`` lines of the texts."""
    defines: dict[str, str] = {}
    for text in texts:
        for m in _DEFINE.finditer(text):
            defines.setdefault(m.group(1), m.group(2))
    return defines


def used_defines(body: str, texts: list[str]) -> list[str]:
    """Return a ``#define`` line for each numeric macro of the texts that ``body`` uses."""
    defines = numeric_defines(texts)
    names = sorted(
        {w for w in re.findall(r"\b[A-Za-z_]\w*\b", mask(body)) if w in defines}
    )
    return [f"#define {n} {defines[n]}" for n in names]
