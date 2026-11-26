"""Scan matched bodies for literals whose role is declared."""

from __future__ import annotations

import collections
import re
from dataclasses import dataclass
from pathlib import Path

from bof3.source import ctext
from bof3.symbols.accesses import _task_types
from bof3.symbols.context import Context
from bof3.symbols.headers import (
    _read_header_values,
    _resolve_values,
    _value_headers,
    record_blocks,
    source_files,
)
from bof3.symbols.layers import _layer_manifests

VALUE_LITERAL = re.compile(r"(?<![\w.])(0[xX][0-9A-Fa-f]+|\d+)([uUlL]*)(?![\w.])")


VALUE_BODY = re.compile(
    r"\b(MATCH|NON_MATCHING|HAND_ASM)\b([^;{}]*?)\b(\w+)\s*\(([^;{}]*)\)\s*\{"
)


VALUE_MEMBER_LINE = re.compile(
    r"^\s*(?:const\s+|volatile\s+)*(?:(struct|union)\s+)?"
    r"([A-Za-z_]\w*(?:\s*\*+)?)\s+(\w+)\s*((?:\[[^\]]*\]\s*)*)"
    r"\s*(?::\s*\d+)?\s*;\s*(?:/\*\s*(.*?)\s*\*/)?\s*$"
)


VALUE_ANON_LINE = re.compile(r"\b(?:struct|union)\s*\{([^{}]*)\}\s*(\w+)\s*;")


VALUE_GLOBAL_LINE = re.compile(
    r"^\s*extern\s+(?:const\s+|volatile\s+)*"
    r"((?:struct\s+|union\s+)?\w+(?:\s*\*+)?(?:\s+(?:const|volatile))*)"
    r"\s+(\w+)\s*((?:\[[^\]]*\]\s*)*)\s*;",
    re.M,
)


VALUE_TYPEDEF_LINE = re.compile(r"^\s*typedef\s+([^;{}()]+?)\s+(\w+)\s*;", re.M)


VALUE_VIEW_ANY = re.compile(
    r"#\s*define\s+(\w+)\s+\(\(\s*(?:volatile\s+)?(\w+)\s*\*\s*\)\s*\1\s*\)"
)


VALUE_PROTO = re.compile(
    r"^[ \t]*(?:const\s+|volatile\s+)*"
    r"((?:struct\s+|union\s+)?[A-Za-z_]\w*(?:\s*\*+)?)"
    r"\s+(\w+)\s*\(([^;{}()]*)\)\s*;",
    re.M,
)


VALUE_LOCAL_LINE = re.compile(
    r"^\s*(?:const\s+|volatile\s+)*((?:struct\s+|union\s+)?[A-Za-z_]\w*)"
    r"\s*(\*?)\s*(\w+)\s*((?:\[[^\]]*\]\s*)*)\s*(?:=[^;]*)?;",
    re.M,
)


VALUE_CAST = re.compile(
    r"^\(\s*(?:volatile\s+|const\s+)*(?:struct\s+|union\s+)?(\w+)\s*(\*+)\s*\)"
)


VALUE_LEFTOVER = re.compile(
    r"(\([^()]*\)|[A-Za-z_][\w.\[\]\->]*?)\s*"
    r"(==|!=|<=|>=|<|>|=|\+=|-=|\*=|/=|&=|\|=|\^=|<<|>>)\s*$"
)


VALUE_RIGHT_OPERATOR = re.compile(
    r"^\s*(==|!=|<=|>=|<|>|\+|-|\*|/|&|\||\^|<<|>>)\s*([A-Za-z_][\w.\[\]\->]*)"
)


VALUE_SWITCH = re.compile(r"\bswitch\s*\(")


VALUE_CASE = re.compile(r"\bcase\s+(0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\s*:")


VALUE_COUNT_NAME = re.compile(
    r"(?:^count$|_count$|^counter$|_counter$|^timer$|_timer$|^limit$|^total$|"
    r"^wait$|^amount$|^radius$|^distance$|^frames$|^steps$|^hp$|^mp$|"
    r"^damage$|^price$|^exp$|^gold$|^percent$|^percentage$)"
)


VALUE_INDEX_NAME = re.compile(
    r"(?:^index$|_index$|^slot$|_slot$|^row$|_row$|^column$|_column$|^position$)"
)


VALUE_COORD_NAME = re.compile(r"(?:^x$|^y$|^z$|^vx$|^vy$|^vz$|^width$|^height$)")


VALUE_COLOUR_NAME = re.compile(r"(?:^colou?r$|_colou?r$|^red$|^green$|^blue$)")


VALUE_FLAGS_NAME = re.compile(r"(?:^flags$|_flags$)")


VALUE_STATE_NAME = re.compile(r"(?:^state$|_state$|^mode$|_mode$|^step$|_step$)")


VALUE_ANGLE_NAME = re.compile(r"(?:^angle$|_angle$)", re.I)


VALUE_FIXED_COMMENT = re.compile(r"\b16\.16\b")


VALUE_ANGLE_CONSTANTS = (
    (512, "ANGLE_45"),
    (1024, "ANGLE_90"),
    (2048, "ANGLE_180"),
    (3072, "ANGLE_270"),
)


VALUE_ALL_ONES = {1: "BYTE_MASK", 2: "HALF_MASK"}


@dataclass(frozen=True)
class ValueFamily:
    """One enum: its tag, the name prefix its members share, and their values."""

    tag: str
    prefix: str
    members: tuple[tuple[str, int], ...]
    header: str


@dataclass(frozen=True)
class ValueSignal:
    """What the declaration around one literal says about its role."""

    role: str
    family: str
    confidence: str
    comment: str
    ctype: str


@dataclass(frozen=True)
class ValueSite:
    """One numeric literal of a matched body and what its role is."""

    file: str
    line: int
    literal: str
    role: str
    family: str
    constant: str
    form: str
    confidence: str


def _value_prefix(names: list[str]) -> str:
    """Return the common ``TAG_`` prefix of the names."""
    if not names:
        return ""
    prefix = names[0]
    for name in names[1:]:
        while prefix and not name.startswith(prefix):
            prefix = prefix[:-1]
    return prefix[: prefix.rfind("_") + 1] if "_" in prefix else ""


def _header_values(
    ctx: Context,
    headers: list[str],
) -> tuple[list, list, dict[str, int]]:
    """Return each header's enums, macros and the resolved value of every name."""
    enums, defines = _read_header_values(ctx, headers)
    return enums, defines, _resolve_values(enums, defines)


def _value_families(
    ctx: Context, headers: list[str]
) -> tuple[dict[str, ValueFamily], set[str]]:
    """Return each visible enum by its tag, and every visible constant's name."""
    enums, _, values = _header_values(ctx, headers)
    families: dict[str, ValueFamily] = {}
    for header, tag, members in enums:
        if not tag:
            continue
        resolved = tuple(
            (name, values[name]) for name, _, _ in members if name in values
        )
        if not resolved:
            continue
        family = ValueFamily(
            tag, _value_prefix([name for name, _ in resolved]), resolved, header
        )
        existing = families.get(tag)
        if existing is None or len(resolved) > len(existing.members):
            families[tag] = family
    return families, set(values)


def _value_members(
    body: str, records: dict[str, dict[str, tuple[str, str]]]
) -> dict[str, tuple[str, str]]:
    """Return the members of one aggregate body, registering its anonymous ones."""
    members: dict[str, tuple[str, str]] = {}
    stack = [members]
    pending: list[str] = []
    count = 0
    for line in body.split("\n"):
        for match in VALUE_ANON_LINE.finditer(line):
            count += 1
            name = f"value_anon_{count}"
            inner = _value_members(match.group(1), records)
            records[name] = inner
            stack[-1][match.group(2)] = (name, "")
        if VALUE_ANON_LINE.search(line):
            continue
        match = VALUE_MEMBER_LINE.match(line)
        if match is not None and "{" not in line and not line.strip().startswith("}"):
            ctype = (match.group(2) + match.group(4)).strip()
            stack[-1][match.group(3)] = (ctype, (match.group(5) or "").strip())
            continue
        if re.search(r"\b(?:struct|union)\s*\{", line):
            count += 1
            name = f"value_anon_{count}"
            inner: dict[str, tuple[str, str]] = {}
            records[name] = inner
            stack.append(inner)
            pending.append(name)
            continue
        closing = re.match(r"\}\s*(\w+)?\s*(?:\[[^\]]*\])?\s*;", line.strip())
        if closing is not None and len(stack) > 1:
            stack.pop()
            name = pending.pop()
            if closing.group(1):
                stack[-1][closing.group(1)] = (name, "")
    return members


def _value_records(
    ctx: Context,
) -> tuple[dict[str, dict[str, tuple[str, str]]], dict[str, str]]:
    """Return each record's members and each typedef alias's type, from every header."""
    records: dict[str, dict[str, tuple[str, str]]] = {}
    typedefs: dict[str, str] = {}
    for _, text in source_files(ctx):
        masked = ctext.mask(text)
        for opening, closing, found in record_blocks(masked):
            members = _value_members(text[opening + 1 : closing], records)
            for name in found:
                if name not in records or len(members) > len(records[name]):
                    records[name] = members
        for match in VALUE_TYPEDEF_LINE.finditer(masked):
            base = match.group(1).strip()
            if base.split()[0] in ("struct", "union", "enum"):
                continue
            typedefs.setdefault(match.group(2), base)
    return records, typedefs


def _value_globals(ctx: Context) -> dict[str, str]:
    """Return each ``extern`` global's declared type."""
    found: dict[str, str] = {}
    for _, text in source_files(ctx):
        for match in VALUE_GLOBAL_LINE.finditer(ctext.mask(text)):
            found.setdefault(match.group(2), (match.group(1) + match.group(3)).strip())
    return found


def _value_prototypes(
    ctx: Context,
) -> tuple[dict[str, list[tuple[str, str]]], dict[str, str]]:
    """Return each function's parameters and return type from its prototypes."""
    from bof3.source import decls

    params: dict[str, list[tuple[str, str]]] = {}
    returns: dict[str, str] = {}
    for _, text in source_files(ctx):
        for match in VALUE_PROTO.finditer(ctext.mask(text)):
            name = match.group(2)
            if name in ("if", "while", "for", "switch", "sizeof", "return"):
                continue
            found = [
                decls.split_param(part) for part in decls.split_args(match.group(3))
            ]
            params.setdefault(name, found)
            returns.setdefault(name, match.group(1).strip())
    return params, returns


def _value_views(ctx: Context) -> list[tuple[str, str, str]]:
    """Return ``(folder, macro, type)`` for each macro that views a global as a record."""
    found = []
    for path, text in source_files(ctx):
        for match in VALUE_VIEW_ANY.finditer(text):
            found.append((str(Path(path).parent), match.group(1), match.group(2)))
    return found


def _value_dereference(ctype: str) -> str | None:
    """Return what one ``*`` or one array subscript of the type gives."""
    text = " ".join(ctype.split())
    index = text.find("[")
    if index >= 0:
        return text[:index].strip()
    if text.endswith("*"):
        return text[:-1].strip() or None
    return None


def _value_member(
    index: dict,
    ctype: str,
    name: str,
) -> tuple[str, str] | None:
    """Return the ``(type, comment)`` of one member of ``ctype``."""
    text = " ".join(ctype.split())
    text = re.sub(r"\b(?:const|volatile)\b", " ", text)
    for _ in range(4):
        text = " ".join(text.split())
        stripped = _value_dereference(text)
        if stripped is not None:
            text = stripped
            continue
        base = re.sub(r"^(?:struct|union)\s+", "", text)
        base = index["typedefs"].get(base, base)
        base = re.sub(r"^(?:struct|union)\s+", "", base)
        record = index["records"].get(base)
        if record is None:
            return None
        found = record.get(name)
        if found is not None:
            return found
        # A member of an anonymous union shares its enclosing record's scope.
        for member_type, _ in record.values():
            inner = index["records"].get(member_type)
            if inner is not None and name in inner:
                return inner[name]
        return None
    return None


def _value_type(
    expression: str,
    index: dict,
    scope: dict[str, str],
    depth: int = 0,
) -> str | None:
    """Return the declared type of an expression, or None when it cannot be resolved."""
    if depth > 8:
        return None
    text = expression.strip()
    while text.startswith("(") and text.endswith(")"):
        inner = text[1:-1]
        if not _value_balanced(inner):
            break
        text = inner.strip()
    if not text:
        return None
    cast = VALUE_CAST.match(text)
    if cast is not None:
        return cast.group(1) + cast.group(2)
    if text.startswith("*"):
        base = _value_type(text[1:], index, scope, depth + 1)
        return _value_dereference(base) if base else None
    if text.startswith("&"):
        base = _value_type(text[1:], index, scope, depth + 1)
        return base + "*" if base else None
    identifier = re.fullmatch(r"[A-Za-z_]\w*", text)
    if identifier is not None:
        name = identifier.group(0)
        if name in scope:
            return scope[name]
        view = index["views"].get(name)
        if view is not None:
            return view + "*"
        if name in index["globals"]:
            return index["globals"][name]
        return None
    call = re.match(r"^([A-Za-z_]\w*)\s*\(", text)
    if call is not None:
        return index["returns"].get(call.group(1))
    # The last top-level member access decides the type.
    split = _value_last_access(text)
    if split is not None:
        base, operator, name = split
        ctype = _value_type(base, index, scope, depth + 1)
        if ctype is None:
            return None
        if operator == "->":
            ctype = _value_dereference(ctype)
            if ctype is None:
                return None
        found = _value_member(index, ctype, name)
        return found[0] if found is not None else None
    # A trailing subscript takes the element type of what it indexes.
    subscript = re.match(r"^(.*)\[[^\]]*\]\s*$", text, re.S)
    if subscript is not None:
        base = _value_type(subscript.group(1), index, scope, depth + 1)
        return _value_dereference(base) if base else None
    return None


def _value_balanced(text: str) -> bool:
    """True when every bracket of the text is closed inside it."""
    depth = 0
    for char in text:
        depth += char in "([{"
        depth -= char in ")]}"
        if depth < 0:
            return False
    return depth == 0


def _value_last_access(text: str) -> tuple[str, str, str] | None:
    """Split an expression at its last top-level ``.`` or ``->``."""
    depth = 0
    found = None
    index = 0
    while index < len(text):
        char = text[index]
        if char in "([{":
            depth += 1
        elif char in ")]}":
            depth -= 1
        elif depth == 0 and char == ".":
            found = (index, ".")
        elif depth == 0 and char == "-" and text[index + 1 : index + 2] == ">":
            found = (index, "->")
            index += 1
        index += 1
    if found is None:
        return None
    position, operator = found
    name = re.match(r"\s*(\w+)", text[position + len(operator) :])
    if name is None:
        return None
    return text[:position], operator, name.group(1)


def _value_member_map(
    index: dict,
) -> dict[str, list[tuple[str, str]]]:
    """Return each member name's ``(type, comment)`` in every record that declares it."""
    found: dict[str, list[tuple[str, str]]] = collections.defaultdict(list)
    for record in index["records"].values():
        for name, info in record.items():
            found[name].append(info)
    return found


def _value_signal(
    index: dict,
    target: str,
    scope: dict[str, str],
) -> ValueSignal | None:
    """Return what the declaration of ``target`` says about a literal beside it."""
    text = target.strip()
    while text.startswith("(") and text.endswith(")") and _value_balanced(text[1:-1]):
        text = text[1:-1].strip()
    if not text or text.count("[") != text.count("]"):
        return None
    if not re.fullmatch(r"[A-Za-z_][\w.\[\]\->]*", text):
        return None
    split = _value_last_access(text)
    name = split[2] if split is not None else text
    ctype = _value_type(text, index, scope)
    member = None
    if split is not None:
        base = _value_type(split[0], index, scope)
        if base is not None:
            if split[1] == "->":
                base = _value_dereference(base) or base
            member = _value_member(index, base, name)
    if member is None and ctype is None:
        candidates = set(index["member_map"].get(name, []))
        if len(candidates) == 1:
            member = candidates.pop()
    comment = member[1] if member is not None else ""
    if not ctype and member is not None:
        ctype = member[0]
    comments = _value_chain_comments(index, text, scope)
    return _value_name_signal(
        name,
        comment,
        ctype or "",
        index["families"],
        any(VALUE_FIXED_COMMENT.search(item) for item in comments),
    )


def _value_chain_comments(index: dict, text: str, scope: dict[str, str]) -> list[str]:
    """Return the comments of each record member on an access chain."""
    comments = []
    current = text
    for _ in range(8):
        split = _value_last_access(current)
        if split is None:
            break
        base, operator, name = split
        ctype = _value_type(base, index, scope)
        if ctype is not None:
            if operator == "->":
                ctype = _value_dereference(ctype) or ctype
            member = _value_member(index, ctype, name)
            if member is not None:
                comments.append(member[1])
        current = base
    return comments


def _value_family_role(tag: str) -> str:
    """Return the role an enum tag's name declares."""
    if tag.endswith("Flags"):
        return "flags"
    if tag.endswith("Id"):
        return "id"
    if tag.endswith("Index"):
        return "index"
    if tag.endswith(("Type", "Category", "Kind")):
        return "type"
    return "state"


def _value_camel(stem: str) -> str:
    return "".join(part.capitalize() for part in stem.split("_"))


def _value_name_signal(
    name: str,
    comment: str,
    ctype: str,
    families: dict[str, ValueFamily],
    fixed: bool = False,
) -> ValueSignal | None:
    """Return the role a member's name, comment or type declares."""
    for word in re.findall(r"[A-Za-z_]\w*", comment):
        if word not in families:
            continue
        return ValueSignal(_value_family_role(word), word, "typed", comment, ctype)
    enum_type = re.sub(r"^(?:struct|union)\s+", "", " ".join(ctype.split()))
    if enum_type in families:
        return ValueSignal(
            _value_family_role(enum_type), enum_type, "typed", comment, ctype
        )
    if name.endswith("_id"):
        tag = _value_camel(name[: -len("_id")]) + "Id"
        if tag in families:
            return ValueSignal("id", tag, "typed", comment, ctype)
        return ValueSignal("id", "", "family", comment, ctype)
    if name.endswith("_index") or VALUE_INDEX_NAME.search(name):
        stem = name[: -len("_index")] if name.endswith("_index") else ""
        tag = _value_camel(stem) + "Index" if stem else ""
        if tag in families:
            return ValueSignal("index", tag, "typed", comment, ctype)
        return ValueSignal("index", "", "typed", comment, ctype)
    if fixed or name == "fixed" or VALUE_FIXED_COMMENT.search(comment):
        return ValueSignal("fixed", "", "typed", comment, ctype)
    if "*" in ctype or "[" in ctype:
        return None
    if VALUE_COUNT_NAME.search(name) and not VALUE_FLAGS_NAME.search(name):
        return ValueSignal("count", "", "typed", comment, ctype)
    if VALUE_COORD_NAME.search(name):
        return ValueSignal("coordinate", "", "typed", comment, ctype)
    if VALUE_COLOUR_NAME.search(name):
        return ValueSignal("colour", "", "typed", comment, ctype)
    if VALUE_ANGLE_NAME.search(name):
        return ValueSignal("angle", "", "typed", comment, ctype)
    if ctype.strip() == "bool":
        return ValueSignal("bool", "", "typed", comment, ctype)
    if VALUE_FLAGS_NAME.search(name):
        return ValueSignal("flags", "", "family", comment, ctype)
    if VALUE_STATE_NAME.search(name):
        return ValueSignal("state", "", "family", comment, ctype)
    return None


def _value_family_member(family: ValueFamily, value: int) -> str:
    """Return the one member of the family with ``value``, else empty."""
    names = {name for name, member_value in family.members if member_value == value}
    return names.pop() if len(names) == 1 else ""


def _value_operator(masked: str, start: int, end: int) -> str:
    """Return the operator the literal is an operand of: ``mask``, ``shift`` or empty."""
    before = masked[max(0, start - 40) : start]
    after = masked[end : end + 40]
    if re.search(r"<<\s*$", before) or re.match(r"\s*>>", after):
        return "shift"
    left = re.search(r"([&|^])=?\s*$", before)
    if left is not None:
        operator = left.group(1)
        if operator == "&" and before[max(0, left.start() - 1) : left.start()] == "&":
            return ""
        if operator == "|" and before[max(0, left.start() - 1) : left.start()] == "|":
            return ""
        if before[left.start() + 1 : left.start() + 2] == "=":
            return ""
        return "mask"
    right = re.match(r"\s*([&|^])(?![&=|])", after)
    if right is not None:
        return "mask"
    return ""


def _value_target(masked: str, start: int, end: int) -> str:
    """Return the expression the literal is an operand of or is compared with."""
    before = masked[max(0, start - 90) : start]
    after = masked[end : end + 70]
    left = VALUE_LEFTOVER.search(before)
    if left is not None:
        return left.group(1).strip()
    right = VALUE_RIGHT_OPERATOR.match(after)
    if right is not None:
        return right.group(2).strip()
    return ""


def _value_call_argument(masked: str, start: int, end: int) -> tuple[str, int] | None:
    """Return the callee and argument index when the literal is a whole call argument."""
    depth = 0
    opening = -1
    for index in range(start - 1, -1, -1):
        char = masked[index]
        if char in ")]}":
            depth += 1
        elif char in "([{":
            if depth == 0:
                if char != "(":
                    return None
                opening = index
                break
            depth -= 1
    if opening < 0:
        return None
    callee = re.search(r"([A-Za-z_]\w*)\s*$", masked[:opening])
    if callee is None:
        return None
    keyword = callee.group(1)
    if keyword in ("if", "while", "for", "switch", "sizeof", "return", "do"):
        return None
    inner = masked[opening + 1 : start]
    commas = 0
    brackets = 0
    last = 0
    for offset, char in enumerate(inner):
        if char in "([{":
            brackets += 1
        elif char in ")]}":
            brackets -= 1
        elif char == "," and brackets == 0:
            commas += 1
            last = offset + 1
    before_argument = inner[last:]
    if before_argument.strip() and not re.fullmatch(
        r"\s*(?:\(?\s*(?:u|s)(?:8|16|32)\s*\)?)?\s*", before_argument
    ):
        return None
    after = re.match(r"\s*([,)])", masked[end:])
    if after is None:
        return None
    return keyword, commas


def _value_form(literal: str, value: int, signal: ValueSignal) -> str:
    """Return the rewrite when only the form is wrong, else empty."""
    suffix = re.search(r"[uUlL]+$", literal)
    tail = suffix.group(0) if suffix else ""
    if signal.role == "index" and value == 0xFF:
        return ""
    if signal.role in ("count", "index", "coordinate", "colour"):
        return str(value) + tail if not _is_decimal(literal) else ""
    if signal.role == "mask":
        width = _value_width(signal.ctype)
        if width is not None and value == (1 << (8 * width)) - 1:
            return ""
        return f"0x{value:X}{tail}"
    if signal.role == "offset":
        if _is_decimal(literal):
            return f"0x{value:X}{tail}"
        return ""
    return ""


def _is_decimal(literal: str) -> bool:
    return not literal.lower().startswith("0x")


def _value_width(ctype: str) -> int | None:
    """Return the byte width a declared type names, when it is a plain integer."""
    text = " ".join(ctype.split())
    return {"u8": 1, "s8": 1, "u16": 2, "s16": 2, "u32": 4, "s32": 4}.get(text)


def _value_role_constant(
    index: dict, signal: ValueSignal, value: int
) -> tuple[str, str]:
    """Return the ``(constant, form)`` a signal gives one value."""
    families = index["families"]
    if signal.family:
        family = families.get(signal.family)
        if family is not None:
            constant = _value_family_member(family, value)
            if constant:
                return constant, ""
    if signal.role == "mask":
        width = _value_width(signal.ctype)
        name = VALUE_ALL_ONES.get(width) if width is not None else None
        if name is None:
            name = {0xFF: "BYTE_MASK", 0xFFFF: "HALF_MASK"}.get(value)
        if name and name in index["names"]:
            return name, ""
    if signal.role == "angle":
        for angle, name in VALUE_ANGLE_CONSTANTS:
            if angle == value and name in index["names"]:
                return name, ""
    if signal.role == "index" and value == 0xFF and "GAME_NONE" in index["names"]:
        return "GAME_NONE", ""
    if signal.role == "bool":
        if value == 1:
            return "true", ""
        if value == 0:
            return "false", ""
    return "", ""


def _value_scan_file(
    ctx: Context, path: str, image: str | None, index: dict
) -> list[ValueSite]:
    """Return every classified literal of one source file."""
    text = ctext.read(ctx.root, path)
    masked = ctext.mask(text)
    found: list[ValueSite] = []
    for match in VALUE_BODY.finditer(masked):
        if match.group(1) != "MATCH":
            continue
        body_start = match.end()
        depth = 1
        position = body_start
        while position < len(masked) and depth:
            depth += (masked[position] == "{") - (masked[position] == "}")
            position += 1
        body = masked[body_start:position]
        scope: dict[str, str] = {}
        for local in VALUE_LOCAL_LINE.finditer(body):
            ctype = (local.group(1) + local.group(2) + local.group(4)).strip()
            scope.setdefault(local.group(3), ctype)
        from bof3.source import decls

        for part in decls.split_args(match.group(4)):
            ctype, name = decls.split_param(part)
            if name:
                scope.setdefault(name, ctype)
        _value_scan_body(path, text, body_start, body, scope, index, found)
        _value_switch_sites(path, text, body_start, body, scope, index, found)
    return found


def _value_number(literal: str) -> int:
    """Return the value of a C numeric literal, without its suffix."""
    text = re.sub(r"[uUlL]+$", "", literal)
    return int(text, 0)


def _value_scan_body(
    path: str,
    text: str,
    body_start: int,
    body: str,
    scope: dict[str, str],
    index: dict,
    found: list[ValueSite],
) -> None:
    """Classify the literals of one matched body into ``found``."""
    for literal_match in VALUE_LITERAL.finditer(body):
        literal = literal_match.group(0)
        value = _value_number(literal)
        start, end = literal_match.start(), literal_match.end()
        signal = None
        target = _value_target(body, start, end)
        if target:
            signal = _value_signal(index, target, scope)
        operator = _value_operator(body, start, end)
        if signal is None and operator == "mask":
            signal = ValueSignal("mask", "", "typed", "", "")
        argument = None
        if signal is None:
            argument = _value_call_argument(body, start, end)
            if argument is not None:
                callee, slot = argument
                if callee == "FIELD" and slot == 2:
                    signal = ValueSignal("offset", "", "typed", "", "u32")
                else:
                    params = index["prototypes"].get(callee)
                    if params is not None and slot < len(params):
                        ctype, name = params[slot]
                        if name:
                            signal = _value_signal(index, name, {name: ctype})
                            if signal is not None:
                                signal = ValueSignal(
                                    signal.role,
                                    signal.family,
                                    signal.confidence,
                                    signal.comment,
                                    ctype,
                                )
        if signal is not None and signal.role == "mask" and operator != "mask":
            continue
        if signal is None:
            continue
        constant, role_form = _value_role_constant(index, signal, value)
        if not constant and operator == "mask" and signal.role != "mask":
            signal = ValueSignal(
                "mask", signal.family, "typed", signal.comment, signal.ctype
            )
        form = role_form or _value_form(literal, value, signal)
        if form.lower() == literal.lower():
            form = ""
        if not constant and not form and not signal.family:
            continue
        line = text.count("\n", 0, body_start + start) + 1
        found.append(
            ValueSite(
                path,
                line,
                literal,
                signal.role,
                signal.family,
                constant,
                form,
                signal.confidence,
            )
        )


def _value_switch_sites(
    path: str,
    text: str,
    body_start: int,
    body: str,
    scope: dict[str, str],
    index: dict,
    found: list[ValueSite],
) -> None:
    """Classify the ``case`` labels of each switch by what the switch tests."""
    for switch in VALUE_SWITCH.finditer(body):
        close = body.find(")", switch.end())
        if close < 0:
            continue
        target = body[switch.end() : close]
        signal = _value_signal(index, target, scope)
        if signal is None:
            continue
        opening = body.find("{", close)
        if opening < 0:
            continue
        depth, position = 1, opening + 1
        while position < len(body) and depth:
            depth += (body[position] == "{") - (body[position] == "}")
            position += 1
        region = body[opening:position]
        for case in VALUE_CASE.finditer(region):
            literal = case.group(1)
            value = _value_number(literal)
            constant, form = _value_role_constant(index, signal, value)
            if not constant and not form and not signal.family:
                continue
            offset = opening + case.start(1)
            found.append(
                ValueSite(
                    path,
                    text.count("\n", 0, body_start + offset) + 1,
                    literal,
                    signal.role,
                    signal.family,
                    constant,
                    form,
                    signal.confidence,
                )
            )


def _value_index(ctx: Context, image: str | None) -> dict:
    """Return the declarations and constants one source file sees."""
    key = image or ""
    cached = ctx.value_index.get(key)
    if cached is not None:
        return cached
    shared = ctx.value_shared
    if image is None:
        headers = [
            name
            for name in ctext.tracked(ctx.root, "include")
            if name.endswith(".h") and not name.startswith("include/psyq/")
        ]
    else:
        headers = _value_headers(ctx, image)
    families, names = _value_families(ctx, headers)
    index = {
        "records": shared["records"],
        "typedefs": shared["typedefs"],
        "globals": shared["globals"],
        "prototypes": shared["prototypes"],
        "returns": shared["returns"],
        "member_map": shared["member_map"],
        "families": families,
        "names": names,
        "views": _value_views_for(ctx, image),
    }
    ctx.value_index[key] = index
    return index


def _value_views_for(ctx: Context, image: str | None) -> dict[str, str]:
    """Return the globals a source of ``image`` reads through a record-view macro."""
    if image is None:
        return {}
    found: dict[str, str] = {}
    from bof3.resolve.ids import source_folder

    folder = f"src/{source_folder(image)}"
    for parent, macro, ctype in ctx.value_views:
        if parent == "" or folder == parent or folder.startswith(parent + "/"):
            found[macro] = ctype
    task = _task_types(ctx).get(image)
    if task is not None:
        found["g_Self"] = task
    return found


def _value_images(ctx: Context) -> dict[str, str]:
    """Return source folder -> the image whose sources it holds."""
    found: dict[str, str] = {}
    for image, manifest in _layer_manifests(ctx).items():
        found.setdefault(manifest.source_dir, image)
        found.update({path: image for path in manifest.outside_sources})
    return found


def _value_image_of(path: str, images: dict[str, str]) -> str | None:
    """Return the image whose source folder holds ``path``, longest folder first."""
    parts = path.split("/")
    for length in range(len(parts), 0, -1):
        folder = "/".join(parts[:length])
        if folder in images:
            return images[folder]
    return None


def _value_sites(ctx: Context) -> list[ValueSite]:
    """Return every classified literal of every matched body."""
    images = _value_images(ctx)
    sites: list[ValueSite] = []
    for path in ctext.tracked(ctx.root, "src"):
        if not path.endswith((".c", ".h")):
            continue
        image = _value_image_of(path, images)
        index = _value_index(ctx, image)
        sites.extend(_value_scan_file(ctx, path, image, index))
    return sites


@dataclass(frozen=True)
class ValuesResult:
    sites: list[ValueSite]
    counts: dict[str, collections.Counter[str]]


def values(ctx: Context) -> ValuesResult:
    """Scan the matched bodies for numeric literals whose role is declared."""
    if not ctx.value_shared:
        records, typedefs = _value_records(ctx)
        prototypes, returns = _value_prototypes(ctx)
        ctx.value_shared = {
            "records": records,
            "typedefs": typedefs,
            "globals": _value_globals(ctx),
            "prototypes": prototypes,
            "returns": returns,
            "member_map": _value_member_map({"records": records, "typedefs": typedefs}),
        }
        ctx.value_views = _value_views(ctx)
    sites = _value_sites(ctx)
    sites.sort(key=lambda site: (site.file, site.line, site.literal))
    counts = {
        "role": collections.Counter(site.role for site in sites),
        "family": collections.Counter(site.family for site in sites if site.family),
        "confidence": collections.Counter(site.confidence for site in sites),
        "subsystem": collections.Counter(_value_subsystem(site.file) for site in sites),
    }
    return ValuesResult(sites, counts)


def _value_subsystem(path: str) -> str:
    """Return the overlay or engine group a source belongs to."""
    parts = path.split("/")
    if len(parts) > 3 and parts[1] == "overlays":
        return parts[2]
    if len(parts) > 3 and parts[1] == "engine":
        return parts[2]
    return parts[0]
