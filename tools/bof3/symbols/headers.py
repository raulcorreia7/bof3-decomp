"""Resolve the named values the headers define."""

from __future__ import annotations

import ast
import re
from dataclasses import dataclass
from pathlib import Path

from bof3.errors import SymbolError
from bof3.resolve.ids import source_folder
from bof3.source import ctext
from bof3.symbols.context import Context
from bof3.symbols.lookup import _address

VALUE_INCLUDE = re.compile(r'^\s*#\s*include\s*([<"])([^>"]+)[>"]', re.M)


COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)


VALUE_DEFINE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+(\w+)(\([^)]*\))?(.*)$")


ENUM_HEAD = re.compile(r"\benum\s*(\w+)?\s*\{")


C_SUFFIX = re.compile(r"\b(0[xX][0-9A-Fa-f]+|\d+)[uUlL]+\b")


C_OCTAL = re.compile(r"\b0([0-7]+)\b")


C_TOKEN = re.compile(r"(0[xX][0-9A-Fa-f]+|\d+)|([A-Za-z_]\w*)")


C_CAST = re.compile(r"\((?:u|s)(?:8|16|32)\)")


C_CHAR = re.compile(r"'(?:\\.|[^\\'])'")


IDENT = re.compile(r"[A-Za-z_]\w*")


@dataclass(frozen=True)
class NamedValue:
    """One enum member or macro with a numeric value."""

    name: str
    value: int
    header: str
    line: int
    family: str


def _without_comments(text: str) -> str:
    return COMMENT.sub(lambda match: re.sub(r"[^\n]", " ", match.group()), text)


def _resolve_include(
    ctx: Context, source: str, name: str, angle: bool, tracked: set[str]
) -> str | None:
    """Return the tracked header an include names, or None when it is a system header."""
    parent = str(Path(source).parent)
    bases = (
        (ctx.root / "include", ctx.root / "include/psyq")
        if angle
        else (ctx.root / parent, ctx.root / "src", ctx.root / "include")
    )
    for base in bases:
        try:
            relative = (base / name).resolve().relative_to(ctx.root).as_posix()
        except (OSError, ValueError):
            continue
        if relative in tracked:
            return relative
    return None


def _value_headers(ctx: Context, image: str | None) -> list[str]:
    """Return the headers the image's sources include, or every tracked header."""
    names = ctext.tracked(ctx.root, "src", "include")
    tracked = set(names)
    if image is None:
        return sorted(name for name in names if name.endswith(".h"))
    try:
        folder = f"src/{source_folder(image)}"
    except (IndexError, ValueError):
        raise SymbolError(f"symbol: {image} is not a target") from None
    queue = [
        name
        for name in names
        if name.startswith(folder + "/") and name.endswith((".c", ".h"))
    ]
    seen: set[str] = set()
    while queue:
        source = queue.pop()
        if source in seen:
            continue
        seen.add(source)
        try:
            text = (ctx.root / source).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        for delimiter, name in VALUE_INCLUDE.findall(_without_comments(text)):
            resolved = _resolve_include(ctx, source, name, delimiter == "<", tracked)
            if resolved is not None and resolved not in seen:
                queue.append(resolved)
    return sorted(name for name in seen if name.endswith(".h"))


RECORD_HEAD = re.compile(r"(?m)\b(?:typedef\s+)?(?:struct|union)\s*(?:(\w+)\s*)?\{")


def source_files(ctx: Context, *, headers: bool = True, psyq: bool = False):
    """Yield ``(path, text)`` of each tracked header (or C file) outside the SDK headers."""
    for path in ctext.tracked_c(ctx.root):
        if (headers and not path.endswith(".h")) or (
            not psyq and path.startswith("include/psyq/")
        ):
            continue
        yield path, ctext.read(ctx.root, path)


def record_blocks(masked: str):
    """Yield ``(opening, closing, names)`` of each struct or union body: its tag and alias."""
    for match in RECORD_HEAD.finditer(masked):
        opening = match.end() - 1
        closing = _match_brace(masked, opening)
        if closing < 0:
            continue
        tail = re.match(r"\s*(\w+)\s*;", masked[closing + 1 :])
        yield (
            opening,
            closing,
            {n for n in (match.group(1), tail and tail.group(1)) if n},
        )


def _match_brace(text: str, opening: int) -> int:
    """Return the index of the brace that closes the one at ``opening``."""
    depth = 0
    for index in range(opening, len(text)):
        if text[index] == "{":
            depth += 1
        elif text[index] == "}":
            depth -= 1
            if depth == 0:
                return index
    return -1


def _split_commas(body: str):
    """Yield ``(start, part)`` for each top-level comma-separated part of an enum body."""
    start = 0
    depth = 0
    for index, char in enumerate(body):
        if char in "([{":
            depth += 1
        elif char in ")]}":
            depth -= 1
        elif char == "," and depth == 0:
            yield start, body[start:index]
            start = index + 1
    yield start, body[start:]


def _enum_values(
    text: str,
) -> list[tuple[str, list[tuple[str, str | None, int]]]]:
    """Return each enum's family and its members with their raw expressions and lines."""
    masked = _without_comments(text)
    found = []
    for match in ENUM_HEAD.finditer(masked):
        opening = masked.find("{", match.start())
        closing = _match_brace(masked, opening)
        if closing < 0:
            continue
        tag = match.group(1) or ""
        tail = re.match(r"\s*(\w+)\s*;", masked[closing + 1 :])
        family = tag or (tail.group(1) if tail else "")
        body = masked[opening + 1 : closing]
        members = []
        for start, part in _split_commas(body):
            piece = part.strip()
            if not piece:
                continue
            member = re.match(r"(\w+)\s*(?:=\s*(.*))?$", piece, re.S)
            if member is None:
                continue
            name = member.group(1)
            expression = member.group(2)
            offset = opening + 1 + start + part.find(name)
            line = masked.count("\n", 0, offset) + 1
            members.append((name, expression.strip() if expression else None, line))
        found.append((family, members))
    return found


def _define_values(text: str) -> list[tuple[str, str, int]]:
    """Return each object-like macro's name, raw body and line."""
    masked = _without_comments(text)
    lines = masked.split("\n")
    found = []
    index = 0
    while index < len(lines):
        start = index
        line = lines[index]
        while line.rstrip().endswith("\\") and index + 1 < len(lines):
            index += 1
            line = line.rstrip()[:-1] + " " + lines[index]
        index += 1
        match = VALUE_DEFINE.match(line)
        if match is None:
            continue
        name, params, body = match.groups()
        body = body.strip()
        if params or not body:
            continue
        found.append((name, body, start + 1))
    return found


def _char_code(literal: str) -> int:
    """Return the value of a one-character C literal."""
    escapes = {"n": 10, "t": 9, "r": 13, "0": 0, "\\": 92, "'": 39, '"': 34}
    char = literal[1:-1]
    if char.startswith("\\") and len(char) >= 2:
        return escapes.get(char[1], ord(char[1]))
    return ord(char[0]) if char else 0


def _eval_node(node: ast.AST) -> int | None:
    if isinstance(node, ast.Constant):
        return node.value if type(node.value) is int else None
    if isinstance(node, ast.UnaryOp):
        value = _eval_node(node.operand)
        if value is None:
            return None
        if isinstance(node.op, ast.UAdd):
            return value
        if isinstance(node.op, ast.USub):
            return -value
        if isinstance(node.op, ast.Invert):
            return ~value
        return None
    if isinstance(node, ast.BinOp):
        left = _eval_node(node.left)
        right = _eval_node(node.right)
        if left is None or right is None:
            return None
        if isinstance(node.op, ast.Add):
            return left + right
        if isinstance(node.op, ast.Sub):
            return left - right
        if isinstance(node.op, ast.Mult):
            return left * right
        if isinstance(node.op, (ast.Div, ast.FloorDiv)) and right:
            return left // right
        if isinstance(node.op, ast.Mod) and right:
            return left % right
        if isinstance(node.op, ast.LShift):
            return left << right
        if isinstance(node.op, ast.RShift):
            return left >> right
        if isinstance(node.op, ast.BitOr):
            return left | right
        if isinstance(node.op, ast.BitAnd):
            return left & right
        if isinstance(node.op, ast.BitXor):
            return left ^ right
        return None
    return None


def _c_expression(expression: str, values: dict[str, int]) -> int | None:
    """Evaluate a C integer constant expression, resolving known names."""
    text = C_SUFFIX.sub(r"\1", expression)
    text = C_CAST.sub("", text)
    text = C_CHAR.sub(lambda match: str(_char_code(match.group(0))), text)
    text = C_OCTAL.sub(lambda match: str(int(match.group(1), 8)), text)

    def replace(match: re.Match[str]) -> str:
        if match.group(1) is not None:
            return match.group(0)
        name = match.group(0)
        if name not in values:
            raise KeyError(name)
        return str(values[name])

    try:
        text = C_TOKEN.sub(replace, text)
        tree = ast.parse(text, mode="eval")
    except (KeyError, SyntaxError):
        return None
    return _eval_node(tree.body)


def _value_family(name: str) -> str:
    """Return a macro's prefix family, such as ``ENEMY_ID_``."""
    head, separator, _ = name.rpartition("_")
    return head + separator if separator else name


def _matches_type(name: str, family: str, wanted: str | None) -> bool:
    if not wanted:
        return True
    if name.startswith(wanted):
        return True
    if family == wanted or family == f"enum {wanted}":
        return True
    return family.endswith("_") and family[:-1] == wanted


def _read_header_values(ctx: Context, headers: list[str]) -> tuple[list, list]:
    """Return the enums and numeric macros of the headers, each with its header."""
    enums = []
    defines = []
    for header in headers:
        try:
            text = (ctx.root / header).read_text(encoding="utf-8", errors="replace")
        except OSError:
            continue
        enums.extend(
            (header, family, members) for family, members in _enum_values(text)
        )
        defines.extend(
            (header, name, body, line) for name, body, line in _define_values(text)
        )
    return enums, defines


def _resolve_enum(members: list, values: dict[str, int]) -> bool:
    """Evaluate one enum's members into ``values``; True when any was added."""
    changed = False
    previous: int | None = -1
    for name, body, _ in members:
        if name in values:
            previous = values[name]
            continue
        value = (
            _c_expression(body, values)
            if body is not None
            else (previous + 1 if previous is not None else None)
        )
        if value is not None:
            values[name] = value
            previous = value
            changed = True
        else:
            previous = None
    return changed


def _resolve_values(enums: list, defines: list) -> dict[str, int]:
    """Evaluate every macro and enum member whose expression resolves."""
    values: dict[str, int] = {}
    for _ in range(5):
        changed = False
        for _, name, body, _ in defines:
            if name in values:
                continue
            value = _c_expression(body, values)
            if value is not None:
                values[name] = value
                changed = True
        for _, _, members in enums:
            changed = _resolve_enum(members, values) or changed
        if not changed:
            break
    return values


def _named_values(
    ctx: Context, headers: list[str], wanted: int, kind: str | None
) -> list[NamedValue]:
    """Return every enum member and numeric macro with ``wanted`` among the headers."""
    enums, defines = _read_header_values(ctx, headers)
    values = _resolve_values(enums, defines)
    found: list[NamedValue] = []
    for header, family, members in enums:
        for name, _, line in members:
            if name in values and values[name] == wanted:
                label = f"enum {family}" if family else "enum"
                if _matches_type(name, label, kind):
                    found.append(NamedValue(name, values[name], header, line, label))
    for header, name, _, line in defines:
        if name in values and values[name] == wanted:
            family = _value_family(name)
            if _matches_type(name, family, kind):
                found.append(NamedValue(name, values[name], header, line, family))
    return found


def _value_rank(header: str, image: str | None, folder: str | None) -> int:
    """Rank a header's scope: the image's own, the group's, then the include tree."""
    if image is None:
        if header.startswith("include/psyq/"):
            return 2
        return 0 if header.startswith("include/") else 1
    if folder is not None and header.startswith(folder + "/"):
        return 0
    if header.startswith("src/"):
        return 1
    if header.startswith("include/psyq/"):
        return 3
    return 2


def value(
    ctx: Context, number: str, image: str | None, family: str | None
) -> list[NamedValue]:
    """Return the enum members and numeric macros with one value, nearest scope first."""
    folder = None
    if image is not None:
        try:
            folder = f"src/{source_folder(image)}"
        except (IndexError, ValueError):
            raise SymbolError(f"symbol: {image} is not a target") from None
    found = _named_values(ctx, _value_headers(ctx, image), _address(number), family)
    found.sort(
        key=lambda item: (
            _value_rank(item.header, image, folder),
            item.header,
            item.line,
            item.name,
        )
    )
    return found
