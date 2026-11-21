"""Prove each function's signature from its callers."""

from __future__ import annotations

import argparse
import collections
import json
from collections.abc import Sequence

from bof3.adapters.config import read_symbols
from bof3.source import asmtext
from bof3.symbols.accesses import _normalized_type
from bof3.symbols.assembly import (
    Assembly,
    SymbolIndex,
    _assembly,
    _declared_kind,
    _declared_prototype,
    _declared_return_kind,
    _folder_system,
    _name_system,
    _render_declared,
    _symbol_system,
    _unique_data_rows,
    _visible_sources,
)
from bof3.symbols.context import RESIDENT, Context
from bof3.symbols.layers import (
    _layer_layouts,
    _layer_manifests,
    _layer_tables,
    _layer_tree,
    _looks_like_table,
    _retail_table_entries,
    _table_entries,
    assign_layers,
)
from bof3.symbols.mips import _reg_name
from bof3.symbols.probe import Row, locate, type_layout


def _pointer_record(
    ctx: Context, use, index: SymbolIndex, callers: Sequence, position: int, declared
) -> str | None:
    """Return the record a pointer argument's accesses and callers support, else None."""
    accesses = [access for access in use.accesses if access.width]
    if not accesses:
        return None
    if (
        declared is not None
        and not declared.unspecified
        and position < len(declared.params)
    ):
        ctype = declared.params[position][0]
        text = _normalized_type(ctype)
        if text.endswith(" *") and "*" not in text[:-2]:
            record = text[:-2].strip()
            if _fits(ctx, record, accesses):
                return record
    for caller, call in callers:
        if 4 + position not in call.arguments:
            continue
        row = _argument_global(index, caller, call, position)
        if row is None:
            continue
        record = _record_type(ctx, row)
        if record and _fits(ctx, record, accesses):
            return record
    return None


def _argument_global(index: SymbolIndex, caller, call, position: int):
    """Return the global whose address one caller puts in one argument register, if any."""
    insns = caller.insns
    start = next(
        (number for number, insn in enumerate(insns) if insn.address == call.address),
        None,
    )
    if start is None:
        return None
    for number in range(start - 1, max(-1, start - 20), -1):
        insn = insns[number]
        if insn.mnemonic in ("jal", "jalr", "jr"):
            break
        ops = asmtext.operands(insn.operands)
        dest, _reads = asmtext.read_write(insn.mnemonic, ops)
        if dest != 4 + position or insn.mnemonic != "lui" or len(ops) < 2:
            continue
        named = asmtext.symbol(ops[1])
        if named is None:
            continue
        row = index.resolve(caller.image, named[0])
        if row is not None:
            return row
    return None


def _record_type(ctx: Context, row: Row) -> str | None:
    """Return the record a global row is or points at, when its type names one."""
    text = _normalized_type(row.type)
    if not text:
        return None
    if text.endswith(" *"):
        text = text[:-2].strip()
    layout = type_layout(ctx, text) if text else None
    return text if layout is not None and layout.record else None


def _fits(ctx: Context, record: str, accesses: list) -> bool:
    """Whether every access of a pointer argument lands on a member of one record."""
    layout = type_layout(ctx, record)
    if layout is None or not layout.record:
        return False
    for access in accesses:
        if access.offset < 0 or access.offset + access.width > layout.size:
            return False
        if not locate(ctx, layout, access.offset):
            return False
    return True


def _v0_after_call(caller, call) -> str | None:
    """Return how a caller uses the value a call returns, else None."""
    insns = caller.insns
    start = next(
        (number for number, insn in enumerate(insns) if insn.address == call.address),
        None,
    )
    if start is None:
        return None
    for insn in insns[start + 2 : start + 9]:
        mnemonic = insn.mnemonic
        ops = asmtext.operands(insn.operands)
        dest, reads = asmtext.read_write(mnemonic, ops)
        if 2 in reads:
            for operand in ops:
                part = asmtext.memory(operand)
                if part is not None and part[1] == 2:
                    return "pointer"
            if mnemonic in ("slt", "sltu", "slti", "sltiu"):
                return "bool"
            if mnemonic in ("beq", "bne", "beqz", "bnez", "bgez", "blez", "bltz"):
                return "bool"
            return "value"
        if mnemonic in ("jal", "jalr", "jr", "j") or dest == 2:
            break
    return None


def _caller_map(assembly: Assembly) -> dict[tuple[str, str], list]:
    """Return, per function, its direct callers with the call's evidence."""
    if assembly.callers is not None:
        return assembly.callers
    found: dict[tuple[str, str], list] = collections.defaultdict(list)
    for (image, name), facts in assembly.facts.items():
        caller = assembly.by_image[image][name]
        for call in facts.calls:
            target = assembly.resolve(image, call.callee)
            if target is None:
                continue
            found[(target.image, target.name)].append((caller, call))
    assembly.callers = dict(found)
    return assembly.callers


def _table_callees(
    ctx: Context, assembly: Assembly, manifests: dict, tree
) -> dict[tuple[str, str], list]:
    """Return the function names each function's indirect calls reach through a table."""
    known = {
        function.name
        for functions in assembly.functions.values()
        for function in functions
    }
    tables, names = _layer_tables(tree, known, manifests)
    symbols = read_symbols(ctx.root)
    for rows in symbols.values():
        for name, row in rows.items():
            if isinstance(row, dict) and _looks_like_table(row):
                names.add(name)
    referenced: dict[str, set[str]] = collections.defaultdict(set)
    for (image, _name), facts in assembly.facts.items():
        if facts.indirect:
            referenced[image].update(name for _table, name in facts.symbols)
    wanted = names & {name for values in referenced.values() for name in values}
    if not wanted:
        return {}
    layouts, payloads = _layer_layouts(ctx, manifests)
    by_address: dict[int, list] = collections.defaultdict(list)
    for functions in assembly.functions.values():
        for function in functions:
            by_address[function.address].append(function)
    found: dict[tuple[str, str], list[str]] = {}

    def resolve_table(image: str, name: str) -> list[str]:
        entries = _table_entries(tables, image, name)
        if not entries:
            entries = _retail_table_entries(
                image, name, symbols, layouts, payloads, by_address
            )
        return entries

    for image, names_here in sorted(referenced.items()):
        for name in sorted(names_here & wanted):
            found[(image, name)] = resolve_table(image, name)
    return found


def _table_callers(
    assembly: Assembly, table_callees: dict[tuple[str, str], list]
) -> dict[tuple[str, str], list]:
    """Return, per function, the functions whose indirect calls reach it through a table."""
    reverse: dict[tuple[str, str], list] = collections.defaultdict(list)
    for (image, caller_name), names in table_callees.items():
        for callee in names:
            target = assembly.resolve(image, callee)
            if target is not None:
                reverse[(target.image, target.name)].append((image, caller_name))
    return reverse


def _layers(
    assembly: Assembly,
    table_callees: dict[tuple[str, str], list],
) -> dict[tuple[str, str], int]:
    """Return every function's call-graph layer."""
    nodes = [
        (image, function.name)
        for image, functions in sorted(assembly.functions.items())
        for function in functions
    ]
    position = {node: index for index, node in enumerate(nodes)}
    edges: list[set[int]] = [set() for _ in nodes]
    for index, (image, name) in enumerate(nodes):
        facts = assembly.facts[(image, name)]
        callees = [call.callee for call in facts.calls]
        callees.extend(table_callees.get((image, name), ()))
        for callee in callees:
            target = assembly.resolve(image, callee)
            other = position.get((target.image, target.name)) if target else None
            if other is not None:
                edges[index].add(other)
    levels = assign_layers(len(nodes), edges)
    return {node: levels[index] for index, node in enumerate(nodes)}


def _majority(votes: collections.Counter, lowest: dict[str, int], tiebreak: int) -> str:
    """Return the system with the most votes; a tie goes to the lowest layer, then the name."""
    if not votes:
        return ""
    return min(
        votes,
        key=lambda system: (-votes[system], lowest.get(system, tiebreak), system),
    )


def _confidence(votes: collections.Counter, found_home: str) -> str:
    """Return proven when every vote agrees, likely over 80% and open otherwise."""
    total = sum(votes.values())
    if not total or not found_home:
        return "open"
    share = votes[found_home] / total
    if share == 1.0 and total >= 2:
        return "proven"
    if share >= 0.8:
        return "likely"
    return "open"


def _function_home(function, manifests: dict) -> str:
    return _name_system(function.name) or _folder_system(
        manifests[function.image].source_dir
    )


def _call_window(caller, call) -> list[int]:
    """Return the instructions a caller writes an argument in, nearest first."""
    insns = caller.insns
    start = next(
        (number for number, insn in enumerate(insns) if insn.address == call.address),
        None,
    )
    if start is None:
        return []
    positions = [start + 1] if start + 1 < len(insns) else []
    for step in range(1, 13):
        position = start - step
        if position < 0:
            break
        if insns[position].mnemonic in ("jal", "jalr", "jr", "j"):
            break
        positions.append(position)
    return positions


def _call_sources(caller, call) -> dict[int, int]:
    """Return, per callee argument position, the register its value was copied from."""
    sources: dict[int, int] = {}
    for position in _call_window(caller, call):
        insn = caller.insns[position]
        dest, reads = asmtext.read_write(insn.mnemonic, asmtext.operands(insn.operands))
        if dest is None or dest not in asmtext.ARG_REGISTERS or dest - 4 in sources:
            continue
        source = next(
            (register for register in reads if register in asmtext.ARG_REGISTERS),
            -1,
        )
        sources[dest - 4] = source
    return sources


def _previous_call(insns, index: int, skip: int | None) -> str | None:
    """Return the callee of the call whose result a register still holds, if any."""
    for position in range(index - 1, max(-1, index - 10), -1):
        if position == skip:
            continue
        insn = insns[position]
        if insn.mnemonic in ("jal", "jalr"):
            ops = asmtext.operands(insn.operands)
            named = asmtext.symbol(ops[0]) if ops else None
            return named[0] if named is not None else None
        if insn.mnemonic in ("jr", "j"):
            break
    return None


def _caller_argument_kind(caller, call, position: int, tree, visible: set[str]) -> str:
    """Return the type a caller's argument register holds before one call."""
    narrow = {"lb": "s8", "lbu": "u8", "lh": "s16", "lhu": "u16"}
    start = next(
        (
            number
            for number, insn in enumerate(caller.insns)
            if insn.address == call.address
        ),
        None,
    )
    for index in _call_window(caller, call):
        insn = caller.insns[index]
        ops = asmtext.operands(insn.operands)
        dest, reads = asmtext.read_write(insn.mnemonic, ops)
        if dest != 4 + position:
            continue
        if 2 in reads:
            callee = _previous_call(caller.insns, index, start)
            if callee:
                decl = _declared_prototype(tree, callee, visible)
                if decl is not None and _declared_return_kind(decl.ret) == "pointer":
                    return "pointer"
        if insn.mnemonic in narrow:
            return narrow[insn.mnemonic]
        if insn.mnemonic == "andi" and len(ops) >= 3:
            mask = asmtext.integer(ops[2])
            if mask == 0xFF:
                return "u8"
            if mask == 0xFFFF:
                return "u16"
        if insn.mnemonic in ("sll", "sra", "srl") and len(ops) >= 3:
            amount = asmtext.integer(ops[2])
            if amount == 24:
                return "s8"
            if amount == 16:
                return "s16"
        if insn.mnemonic == "lui" or any(
            "%hi(" in operand or "%lo(" in operand for operand in ops
        ):
            return "pointer"
        return "s32"
    return "s32"


def _argument_live_at(function, call, position: int) -> bool:
    """Whether an argument register still holds the caller's value when a call copies it."""
    insns = function.insns
    writer = None
    for index in _call_window(function, call):
        dest, _reads = asmtext.read_write(
            insns[index].mnemonic, asmtext.operands(insns[index].operands)
        )
        if dest == 4 + position:
            writer = index
            break
    if writer is None:
        return True
    for insn in insns[:writer]:
        if insn.mnemonic in ("jal", "jalr"):
            return False
        dest, _reads = asmtext.read_write(
            insn.mnemonic, asmtext.operands(insn.operands)
        )
        if dest == 4 + position:
            return False
    return True


def _forwarded_pointer(
    function, facts, position: int, tree, visible: set[str]
) -> str | None:
    """Return the pointer type an argument is forwarded as to one declared callee parameter."""
    for call in facts.calls:
        if not _argument_live_at(function, call, position):
            continue
        declared = _declared_prototype(tree, call.callee, visible)
        if declared is None or declared.unspecified:
            continue
        params = [
            ctype
            for ctype, param in declared.params
            if not (ctype == "void" and not param) and ctype != "..."
        ]
        sources = _call_sources(function, call)
        for callee_position, ctype in enumerate(params):
            text = _normalized_type(ctype)
            if not text.endswith(" *"):
                continue
            if sources.get(callee_position) == 4 + position:
                return text[:-2].strip() or "void"
    return None


def _function_signature(
    ctx: Context,
    function,
    facts,
    callers: Sequence,
    index: SymbolIndex,
    tree,
    visible: set[str],
    table_callers: Sequence = (),
) -> dict:
    """Build one signature row from a function's facts and its callers."""
    declared = _declared_prototype(tree, function.name, visible)
    arguments = []
    counts = [
        max(call.arguments) - 3 if call.arguments else 0 for _caller, call in callers
    ]
    used = max(facts.args) + 1 if facts.args else 0
    for position in range(used):
        use = facts.args.get(position)
        record = None
        forwarded = None
        proof = None
        if use and use.accesses:
            kind = "pointer"
            proof = "callee"
            record = _pointer_record(ctx, use, index, callers, position, declared)
        else:
            forwarded = _forwarded_pointer(function, facts, position, tree, visible)
            caller_kinds = [
                _caller_argument_kind(caller, call, position, tree, visible)
                for caller, call in callers
            ]
            if forwarded is not None:
                kind = "pointer"
                proof = "forwarded"
                layout = type_layout(ctx, forwarded) if forwarded != "void" else None
                record = forwarded if layout is not None and layout.record else None
            elif callers and all(value == "pointer" for value in caller_kinds):
                kind = "pointer"
                proof = "callers"
                forwarded = "void"
            else:
                kind = use.narrow if use and use.narrow else "s32"
                proof = "callee" if use and use.narrow else None
        arguments.append(
            {
                "index": position,
                "register": _reg_name(4 + position),
                "kind": kind,
                "type": f"{record}*" if record else ("void*" if forwarded else kind),
                "record": record,
                "narrow": use.narrow if use else None,
                "proof": proof,
                "used": use is not None,
                "accesses": [
                    {
                        "offset": f"0x{access.offset:X}",
                        "width": access.width,
                        "signed": access.signed,
                        "mnemonic": access.mnemonic,
                        "write": access.write,
                    }
                    for access in use.accesses
                ]
                if use
                else [],
            }
        )
    for position in range(facts.stack_arguments):
        pointer = position in facts.stack_pointers
        arguments.append(
            {
                "index": 4 + position,
                "register": f"0x{0x10 + position * 4:X}(sp)",
                "kind": "pointer" if pointer else "s32",
                "type": "void*" if pointer else "s32",
                "record": None,
                "narrow": None,
                "accesses": [],
            }
        )
    caller_uses = [_v0_after_call(caller, call) for caller, call in callers]
    returns = list(facts.return_writes)
    if not returns:
        returned = {"kind": "void", "width": None, "sign": None}
    elif all(asmtext.bool_write(mnemonic, text) for mnemonic, text in returns):
        returned = {"kind": "bool", "width": 1, "sign": False}
    elif any(kind == "pointer" for kind in caller_uses):
        returned = {"kind": "pointer", "width": 4, "sign": None}
    else:
        width, sign = facts.return_width or (None, None)
        returned = {"kind": "value", "width": width, "sign": sign}
    declared_text = _render_declared(function.name, declared)
    found_text = _render_found(function.name, arguments, returned)
    differs = []
    declared_params: list = []
    if declared is not None and not declared.unspecified:
        declared_params = [
            (ctype, param)
            for ctype, param in declared.params
            if not (ctype == "void" and not param) and ctype != "..."
        ]
        if len(declared_params) != len(arguments):
            differs.append(
                f"arguments {len(declared_params)} declared, {len(arguments)} found"
            )
        for position, (ctype, _param) in enumerate(declared_params):
            if position >= len(arguments):
                break
            kind = _declared_kind(ctype)
            if kind != arguments[position]["kind"]:
                differs.append(
                    f"arg{position} {kind} declared, "
                    f"{arguments[position]['kind']} found"
                )
        declared_return = _declared_return_kind(declared.ret)
        if declared_return != returned["kind"]:
            differs.append(
                f"return {declared_return} declared, {returned['kind']} found"
            )
    confidence = "open"
    if counts:
        share = sum(1 for count in counts if count == used) / len(counts)
        if share == 1.0 and not facts.stack_arguments:
            confidence = "proven"
        elif share >= 0.8:
            confidence = "likely"
    elif facts.args or returns:
        confidence = "likely"
    narrow = {"u8", "s8", "u16", "s16"}
    if any(
        argument["kind"] == "pointer" and argument.get("proof") == "callers"
        for argument in arguments
    ):
        confidence = "likely" if confidence == "proven" else confidence
    if not returns and facts.ambiguous_return:
        confidence = "likely" if confidence == "proven" else confidence
    for position, argument in enumerate(arguments):
        declared_kind = (
            _declared_kind(declared_params[position][0])
            if declared_params and position < len(declared_params)
            else None
        )
        if argument["kind"] in narrow:
            caller_kinds = [
                _caller_argument_kind(caller, call, position, tree, visible)
                for caller, call in callers
            ]
            if not all(kind in narrow for kind in caller_kinds):
                confidence = "likely" if confidence == "proven" else confidence
        elif declared_kind in narrow and argument["kind"] == "s32":
            confidence = "likely" if confidence == "proven" else confidence
        elif declared_kind == "pointer" and argument["kind"] != "pointer":
            confidence = "likely" if confidence == "proven" else confidence
    evidence = [
        f"{caller.image}@0x{call.address:08X} {caller.name} "
        f"args={','.join(_reg_name(register) for register in call.arguments)}"
        for caller, call in callers[:5]
    ]
    evidence.extend(f"table caller {image}:{name}" for image, name in table_callers[:3])
    for access in facts.accesses[:5]:
        offset = f"+0x{access.offset:X}" if access.offset else ""
        evidence.append(
            f"{function.image}@0x{access.address:08X} {access.mnemonic} "
            f"{access.name or 'argument'}{offset}"
        )
    return {
        "function": function.name,
        "image": function.image,
        "address": f"0x{function.address:08X}",
        "declared": declared_text,
        "found": found_text,
        "callee_args": used,
        "stack_args": facts.stack_arguments,
        "caller_args_min": min(counts) if counts else None,
        "caller_args_max": max(counts) if counts else None,
        "disagree": bool(differs),
        "differs": differs,
        "args": arguments,
        "return": returned,
        "callers": len(callers) + len(table_callers),
        "evidence": evidence,
        "confidence": confidence,
    }


def _render_found(name: str, arguments: list[dict], returned: dict) -> str:
    params = ", ".join(argument["type"] for argument in arguments)
    return f"{_return_type(returned)} {name}({params or 'void'})"


def _return_type(returned: dict) -> str:
    """Write a returned kind as the C type its width and sign state."""
    kind = returned["kind"]
    if kind in ("void", "bool"):
        return kind
    if kind == "pointer":
        return "void*"
    width = returned["width"]
    sign = returned["sign"]
    if width == 1:
        return "u8" if sign is False else "s8"
    if width == 2:
        return "u16" if sign is False else "s16"
    return "s32"


def _home_of(manifests: dict, key: tuple[str, str]) -> str:
    """Return a function's declared system from its name prefix or its folder."""
    image, name = key
    return _name_system(name) or _folder_system(manifests[image].source_dir)


def _function_candidates(
    function,
    facts,
    index: SymbolIndex,
    manifests: dict,
    callers: dict[tuple[str, str], list],
    writers: dict,
    readers: dict,
    previous,
    following,
    declared: str,
    local: bool,
) -> dict[str, list[str]]:
    """Return the systems a function's bytes move it to, each with its rule evidence."""
    rules: dict[str, list[str]] = collections.defaultdict(list)
    sites = callers.get((function.image, function.name), ())
    caller_systems = collections.Counter(
        _function_home(caller, manifests) for caller, _call in sites
    )
    if not local and sum(caller_systems.values()) >= 3:
        system, count = caller_systems.most_common(1)[0]
        if count / sum(caller_systems.values()) >= 0.8:
            rules[system].append(
                f"rule a: {count} of {sum(caller_systems.values())} callers are {system}"
            )
    if not local:
        for access in facts.accesses:
            if not access.write or not access.name:
                continue
            row = index.resolve(function.image, access.name)
            if row is None:
                continue
            key = (access.name, row.addr)
            if writers.get(key) != {(function.image, function.name)}:
                continue
            others = readers.get(key, set()) - {(function.image, function.name)}
            if not others:
                continue
            systems = {_home_of(manifests, other) for other in others}
            if len(systems) == 1:
                system = next(iter(systems))
                rules[system].append(
                    f"rule b: only writer of {access.name}, read by "
                    f"{len(others)} function(s) in {system}"
                )
    if previous is not None and following is not None:
        left = _function_home(previous, manifests)
        right = _function_home(following, manifests)
        if left == right and left != declared:
            declared_callers = [
                caller
                for caller, _call in sites
                if _function_home(caller, manifests) == declared
            ]
            if not declared_callers:
                rules[left].append(
                    f"rule c: between {previous.name} and {following.name} in address "
                    f"order and no {declared} caller"
                )
    return rules


def _function_rows(
    assembly: Assembly,
    manifests: dict,
    index: SymbolIndex,
    layers: dict[tuple[str, str], int],
    callers: dict[tuple[str, str], list],
    table_callees: dict[tuple[str, str], list],
    writers: dict,
    readers: dict,
) -> list[dict]:
    """Build one home row per function, from the call and data graph."""
    rows = []
    for image, functions in sorted(assembly.functions.items()):
        folder = _folder_system(manifests[image].source_dir)
        order = sorted(functions, key=lambda function: function.address)
        prefixes = {_name_system(function.name) for function in functions}
        for position, function in enumerate(order):
            key = (image, function.name)
            facts = assembly.facts[key]
            declared = _name_system(function.name) or folder
            local = image.startswith("emi/") and declared in prefixes
            rules = _function_candidates(
                function,
                facts,
                index,
                manifests,
                callers,
                writers,
                readers,
                order[position - 1] if position else None,
                order[position + 1] if position + 1 < len(order) else None,
                declared,
                local,
            )
            if rules:
                found_home = min(
                    rules, key=lambda system: (-len(rules[system]), system)
                )
                evidence = rules[found_home]
            else:
                found_home = declared
                evidence = []
            sites = callers.get(key, ())
            rows.append(
                {
                    "kind": "function",
                    "name": function.name,
                    "image": image,
                    "address": f"0x{function.address:08X}",
                    "layer": layers.get(key, 0),
                    "declared_home": declared,
                    "found_home": found_home,
                    "folder": folder,
                    "counts": {
                        "callers": len(sites),
                        "callees": len(facts.calls),
                        "data": sum(1 for table, _name in facts.symbols if table),
                        "systems": dict(
                            collections.Counter(
                                _function_home(caller, manifests)
                                for caller, _call in sites
                            )
                        ),
                    },
                    "evidence": evidence[:4],
                    "confidence": "proven"
                    if len(evidence) >= 2
                    else "likely"
                    if evidence
                    else "open",
                }
            )
    return rows


def _global_rows(
    assembly: Assembly,
    manifests: dict,
    index: SymbolIndex,
    layers: dict[tuple[str, str], int],
    functions: dict[tuple[str, str], dict],
    extents: list[dict],
    uses: dict,
    writers: dict,
    readers: dict,
) -> list[dict]:
    """Build one home row per global whose writers all sit in one system."""
    absorbed: dict[tuple[str, int], str] = {}
    for row in extents:
        start = int(row["address"], 16)
        for name in row["absorbs"]:
            absorbed[(name, start)] = row["symbol"]
    rows = []
    for row in _unique_data_rows(index):
        key = (row.name, row.addr)
        written_by = writers.get(key)
        if not written_by:
            continue
        systems = {
            functions.get(item, {}).get("found_home") or _home_of(manifests, item)
            for item in written_by
        }
        if len(systems) != 1:
            continue
        found_home = next(iter(systems))
        image = index.canonical(row.name, row.addr) or row.table
        declared = _symbol_system(row.name, assembly.systems) or _folder_system(
            manifests[image].source_dir if image in manifests else row.table
        )
        read_by = readers.get(key, set())
        found = uses.get(key, ())
        rows.append(
            {
                "kind": "global",
                "name": row.name,
                "image": image,
                "address": f"0x{row.addr:08X}",
                "declared_home": declared,
                "found_home": found_home,
                "member_of": absorbed.get(key),
                "counts": {
                    "reads": sum(1 for _i, _f, access in found if not access.write),
                    "writes": sum(1 for _i, _f, access in found if access.write),
                    "writers": len(written_by),
                    "readers": len(read_by),
                    "images": len(assembly.functions) if image in RESIDENT else 1,
                    "systems": {
                        system: sum(
                            1
                            for item in written_by
                            if (
                                functions.get(item, {}).get("found_home")
                                or _home_of(manifests, item)
                            )
                            == system
                        )
                        for system in systems
                    },
                },
                "evidence": [
                    f"writer {item[0]}:{item[1]}" for item in sorted(written_by)[:4]
                ],
                "confidence": "proven",
            }
        )
    return rows


def _unit_of(tree, visible: set[str], function) -> str:
    """Return the source file a function belongs to: its C unit, else its split unit."""
    for decl in tree.decls.get(function.name, ()):
        if decl.kind == "def" and decl.file in visible:
            return decl.file
    return function.source


def _is_split_unit(unit: str) -> bool:
    return unit.startswith(("asm/", "build/asm/"))


def _file_rows(
    assembly: Assembly,
    manifests: dict,
    tree,
    visible: dict[str, set[str]],
    function_rows: list[dict],
) -> list[dict]:
    """Build one home row per source file, with contiguity evidence from the address order."""
    homes = {(row["image"], row["name"]): row["found_home"] for row in function_rows}
    rows: list[dict] = []
    for image, functions in sorted(assembly.functions.items()):
        order = sorted(functions, key=lambda function: function.address)
        systems: dict[str, collections.Counter] = collections.defaultdict(
            collections.Counter
        )
        names: dict[str, list[str]] = collections.defaultdict(list)
        unit_runs: list[tuple[str, str]] = []
        system_runs: list[str] = []
        folder = _folder_system(manifests[image].source_dir)
        for function in order:
            unit = _unit_of(tree, visible.get(image, set()), function)
            system = homes.get((image, function.name)) or folder
            systems[unit][system] += 1
            names[unit].append(function.name)
            if not unit_runs or unit_runs[-1][0] != unit:
                unit_runs.append((unit, system))
            if not system_runs or system_runs[-1] != system:
                system_runs.append(system)
        evidence: dict[str, list[str]] = collections.defaultdict(list)
        for position in range(len(unit_runs) - 1):
            unit, system = unit_runs[position]
            other_unit, other_system = unit_runs[position + 1]
            if not (_is_split_unit(unit) or _is_split_unit(other_unit)):
                continue
            if system != other_system:
                continue
            if len(names[unit]) < 2 and len(names[other_unit]) < 2:
                continue
            evidence[unit].append(
                f"continues {other_unit} in the address order: one unit split"
            )
            evidence[other_unit].append(
                f"continues {unit} in the address order: one unit split"
            )
        if len(system_runs) > 1 and all(
            _name_system(function.name) for function in order
        ):
            evidence_for_all = (
                f"the systems are split into {len(system_runs)} address runs: "
                "another system's units sit between"
            )
            for unit, _system in unit_runs:
                evidence[unit].append(evidence_for_all)
        for unit, counter in systems.items():
            declared = _folder_system(manifests[image].source_dir)
            found_home = _majority(counter, {}, 0) or declared
            for name in names[unit][:4]:
                if homes.get((image, name)) != found_home:
                    evidence[unit].append(f"{name} is {homes.get((image, name))}")
            rows.append(
                {
                    "kind": "file",
                    "name": unit,
                    "image": image,
                    "declared_home": declared,
                    "found_home": found_home,
                    "counts": {
                        "functions": len(names[unit]),
                        "systems": dict(counter),
                    },
                    "evidence": evidence.get(unit, [])[:6],
                    "confidence": _confidence(counter, found_home),
                }
            )
    return [row for row in rows if not row["name"].startswith(("asm/", "build/asm/"))]


def signatures(ctx: Context, args: argparse.Namespace) -> int:
    """Print the signature the bytes prove for each function, beside its declaration."""
    assembly = _assembly(ctx)
    index = SymbolIndex(ctx, read_symbols(ctx.root))
    manifests = _layer_manifests(ctx)
    tree = _layer_tree(ctx)
    visible = _visible_sources(tree, manifests)
    callers = _caller_map(assembly)
    table_callers = _table_callers(
        assembly, _table_callees(ctx, assembly, manifests, tree)
    )
    rows = []
    for image, functions in sorted(assembly.functions.items()):
        for function in functions:
            if args.function and function.name != args.function:
                continue
            rows.append(
                _function_signature(
                    ctx,
                    function,
                    assembly.facts[(image, function.name)],
                    callers.get((image, function.name), ()),
                    index,
                    tree,
                    visible.get(image, set()),
                    table_callers.get((image, function.name), ()),
                )
            )
    keys = [
        "function",
        "image",
        "address",
        "declared",
        "found",
        "callee_args",
        "stack_args",
        "caller_args_min",
        "caller_args_max",
        "disagree",
        "differs",
        "args",
        "return",
        "callers",
        "evidence",
        "confidence",
    ]
    if args.jsonl:
        for row in rows:
            print(json.dumps({key: row[key] for key in keys}, ensure_ascii=False))
        return 0
    print(
        "\t".join(
            [
                "function",
                "image",
                "address",
                "declared",
                "found",
                "callers",
                "confidence",
            ]
        )
    )
    for row in rows:
        print(
            "\t".join(
                [
                    row["function"],
                    row["image"],
                    row["address"],
                    row["declared"] or "",
                    row["found"],
                    str(row["callers"]),
                    row["confidence"],
                ]
            )
        )
    return 0
