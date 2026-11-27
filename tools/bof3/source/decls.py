"""Declarations, definitions and calls of the C tree, and the problems they show."""

from __future__ import annotations

import collections
import os
import re
from dataclasses import dataclass, field

from bof3.source.ctext import mask, split_args

_KEYWORDS = frozenset(
    "if while for switch return sizeof else do case goto defined typeof __attribute__".split()
)
_TYPES = frozenset("void s8 s16 s32 u8 u16 u32 int char short long unsigned".split())
_QUALIFIERS = frozenset(("struct", "union", "enum", "unsigned", "signed", "const"))
_MARKERS = re.compile(
    r"\b(static|extern|inline|INLINE|STATIC|MATCH|NON_MATCHING|HAND_ASM|FAKE_MATCH|MATCH_FAKE)\b"
)
_HEAD = re.compile(
    r"(?:^|(?<=[;}]))\s*((?:[\w\s\*]+?)[\s\*])(\w+)\s*"
    r"\(([^;{}()]*(?:\([^()]*\)[^;{}()]*)*)\)\s*([;{])"
)
_PLACEHOLDER = re.compile(r"^arg\d+$")
_CALL_CAST = re.compile(
    r"\(\s*\(\s*([^()]*?)\(\s*\*\s*\)\s*\(([^()]*)\)\s*\)\s*(\w+)\s*\)"
)
_RETURN_CAST = re.compile(r"\(\s*((?:struct\s+|union\s+)?\w+\s*\*+)\s*\)\s*(\w+)\s*\(")
_INCLUDE = re.compile(r'^\s*#\s*include\s*[<"]([^>"]+)[>"]', re.M)


@dataclass(frozen=True, slots=True)
class Decl:
    """A prototype (``kind == "proto"``) or a definition (``"def"``)."""

    kind: str
    file: str
    line: int
    ret: str
    params: tuple[tuple[str, str], ...]  # (type, name)
    unspecified: bool  # written with empty parentheses


@dataclass(frozen=True, slots=True)
class Call:
    """A call inside a function body."""

    name: str
    file: str
    line: int
    before: str  # the text just before the name


@dataclass(frozen=True, slots=True)
class Problem:
    """One prototype that disagrees with its owner."""

    kind: str
    name: str
    file: str
    line: int
    detail: str


def strip_comments(text: str) -> str:
    """Blank comments, ``extern "C"`` wrappers and preprocessor lines; keep line numbers."""
    if re.search(r'extern\s+"C"\s*\{', text):
        text = re.sub(r'extern\s+"C"\s*\{', "", text)
        end = text.rfind("\n}")
        if end >= 0:
            text = text[:end] + text[end + 2 :]
    text = mask(text)
    out, continued = [], False
    for line in text.split("\n"):
        if continued or line.lstrip().startswith("#"):
            continued = line.rstrip().endswith("\\")
            out.append("")
        else:
            out.append(line)
    return "\n".join(out)


def normalize(text: str) -> str:
    return re.sub(r"\s+", " ", re.sub(r"\s*\*\s*", "*", text)).strip()


def split_param(param: str) -> tuple[str, str]:
    """Split one parameter into ``(type, name)``; the name is empty when absent."""
    if param == "...":
        return ("...", "")
    pointer = re.match(r"^(.*)\(\s*\*\s*(\w+)\s*\)(.*)$", param, re.S)
    match = re.match(r"^(.*?)(\w+)((?:\[[^\]]*\])*)$", param, re.S)
    if not match or not match.group(1).strip() or match.group(1).strip() in _QUALIFIERS:
        return (normalize(param), "")
    if pointer:
        return (
            normalize(pointer.group(1) + "(*)" + pointer.group(3)),
            pointer.group(2),
        )
    return (normalize(match.group(1) + match.group(3)), match.group(2))


def _top_level(text: str) -> tuple[str, list[tuple[int, int]]]:
    """Return ``text`` with every top-level body emptied (lines kept) and the body spans."""
    spans, depth, start = [], 0, 0
    for i, ch in enumerate(text):
        if ch == "{":
            if depth == 0:
                start = i
            depth += 1
        elif ch == "}":
            depth -= 1
            if depth == 0:
                spans.append((start, i))
    parts, pos = [], 0
    for a, b in spans:
        parts.append(text[pos : a + 1])
        parts.append(re.sub(r"[^\n]", "", text[a + 1 : b]))
        pos = b
    parts.append(text[pos:])
    return "".join(parts), spans


@dataclass
class Tree:
    """The declarations and calls of a set of C files, keyed by repo-relative path."""

    texts: dict[str, str]
    decls: dict[str, list[Decl]] = field(
        default_factory=lambda: collections.defaultdict(list)
    )
    calls: list[Call] = field(default_factory=list)
    stripped: dict[str, str] = field(default_factory=dict)
    includes: dict[str, list[str]] = field(default_factory=dict)
    macros: set[str] = field(default_factory=set)
    variables: set[str] = field(default_factory=set)

    def __post_init__(self) -> None:
        for name in sorted(self.texts):
            self._read(name)
        self._includes()

    def _includes(self) -> None:
        known = set(self.texts)
        for name, text in self.texts.items():
            found = []
            for m in _INCLUDE.finditer(text):
                for base in (os.path.dirname(name), "src", "include", "include/psyq"):
                    candidate = os.path.normpath(os.path.join(base, m.group(1)))
                    if candidate in known:
                        found.append(candidate)
                        break
            self.includes[name] = found

    def _read(self, name: str) -> None:
        text = strip_comments(self.texts[name])
        self.stripped[name] = text
        top, spans = _top_level(text)
        for m in _HEAD.finditer(top):
            ret, fname, params, end = m.groups()
            ret = ret.strip()
            if fname in _KEYWORDS or "=" in ret or ret.split()[-1:] == ["return"]:
                continue
            if re.search(r"\btypedef\b", ret):
                continue
            line = top.count("\n", 0, m.start(2)) + 1
            self.decls[fname].append(
                Decl(
                    "def" if end == "{" else "proto",
                    name,
                    line,
                    normalize(_MARKERS.sub("", ret)),
                    tuple(split_param(p) for p in split_args(params)),
                    params.strip() == "",
                )
            )
        for a, b in spans:
            body = text[a : b + 1]
            for m in re.finditer(r"(?<![\w.>])(\w+)\s*\(", body):
                callee = m.group(1)
                if callee in _KEYWORDS or callee in _TYPES:
                    continue
                self.calls.append(
                    Call(
                        callee,
                        name,
                        text.count("\n", 0, a + m.start()) + 1,
                        body[max(0, m.start() - 12) : m.start()],
                    )
                )
        for m in re.finditer(r"^\s*#\s*define\s+(\w+)", self.texts[name], re.M):
            self.macros.add(m.group(1))
        for m in re.finditer(r"\(\s*\*\s*(\w+)\s*\)", text):
            self.variables.add(m.group(1))
        for m in re.finditer(r"[\s\*](\w+)\s*(?:=|\[)", text):
            self.variables.add(m.group(1))

    def kind(self, name: str, kind: str) -> list[Decl]:
        return [d for d in self.decls.get(name, ()) if d.kind == kind]

    def views(self) -> dict[str, list[set[str]]]:
        """Return what each file sees, once per unit that compiles it (a body header is in several)."""
        included_by: dict[str, list[str]] = collections.defaultdict(list)
        for name, found in self.includes.items():
            for inc in found:
                included_by[inc].append(name)
        closures: dict[str, set[str]] = {}

        def units(name: str) -> set[str]:
            seen, stack, found = {name}, [name], set()
            while stack:
                current = stack.pop()
                if current.endswith(".c"):
                    found.add(current)
                for parent in included_by.get(current, ()):
                    if parent not in seen:
                        seen.add(parent)
                        stack.append(parent)
            return found

        result = {}
        for name in self.texts:
            result[name] = []
            for root in sorted(units(name) or {name}):
                if root not in closures:
                    closures[root] = self.closure(root)
                result[name].append(closures[root])
        return result

    def closure(self, name: str) -> set[str]:
        """Return ``name`` and every file it includes, directly or not."""
        seen, stack = {name}, [name]
        while stack:
            for inc in self.includes.get(stack.pop(), ()):
                if inc not in seen:
                    seen.add(inc)
                    stack.append(inc)
        return seen


def signature_rows(tree: Tree) -> list[Problem]:
    """Return the prototypes that are neither their owner's signature nor its non-prototype form."""
    views = tree.views()
    rows: list[Problem] = []
    for name, found in tree.decls.items():
        defs = [d for d in found if d.kind == "def"]
        if not defs:
            continue
        for p in (d for d in found if d.kind == "proto"):
            sees = set().union(*views[p.file]) if views[p.file] else set()
            owners = [d for d in defs if _owns(d, p, sees)]
            if (
                not owners
                or any(_same_signature(d, p) for d in owners)
                or _kept(tree, p)
            ):
                continue
            owner = owners[0]
            rows.append(
                Problem(
                    "signature_differs",
                    name,
                    p.file,
                    p.line,
                    f"{_shape(p)} vs {_shape(owner)} ({owner.file})",
                )
            )
    return sorted(rows, key=lambda r: (r.file, r.line, r.name))


def _shape(d: Decl) -> str:
    """Write a declaration as ``ret(types)``; empty parentheses mean no prototype."""
    if d.unspecified:
        return f"{d.ret}()"
    return f"{d.ret}({', '.join(t for t, _ in d.params)})"


def _image(path: str) -> str:
    return "/".join(path.split("/")[:5]) if path.startswith("src/overlays/") else ""


def _owns(d: Decl, p: Decl, sees: set[str]) -> bool:
    return (
        d.file in sees
        or d.file.startswith("src/engine/")
        or bool(_image(p.file) and _image(d.file) == _image(p.file))
    )


def _same_signature(d: Decl, p: Decl) -> bool:
    if d.ret != p.ret:
        return False
    if p.unspecified or d.unspecified:
        return True
    types = lambda x: [t for t, _ in x.params if t != "void"]  # noqa: E731
    return types(d) == types(p)


def _kept(tree: Tree, p: Decl) -> bool:
    lines = tree.texts[p.file].split("\n")
    return any("sig-kept:" in line for line in lines[max(0, p.line - 3) : p.line])
