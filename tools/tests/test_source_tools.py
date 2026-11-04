from __future__ import annotations

import sys
from pathlib import Path

import pytest

from bof3.source import ctext, decls, index

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import shapes
import typeloss
import values


def test_opcode_tokens_ignore_registers_and_immediates() -> None:
    addiu_a = 0x24000000 | (4 << 16) | 1
    addiu_b = 0x24000000 | (5 << 16) | 0x7FFF
    assert index.opcode_token(addiu_a) == index.opcode_token(addiu_b)
    assert index.opcode_token(0) == 0
    assert index.opcode_token(0x03E00008) != index.opcode_token(addiu_a)


def test_a_definition_is_found_by_name_not_by_call() -> None:
    text = "void f(int a);\nvoid g(void) { f(1); }\nint f(int a)\n{\n    return a;\n}\n"
    start, end = ctext.find_definition(text, "f") or (0, 0)
    assert text[start:end].startswith("int f(int a)")
    assert text[start:end].endswith("}")
    assert ctext.find_definition(text, "h") is None
    assert ctext.split_args("int a, void (*cb)(int, int), char *c") == [
        "int a",
        "void (*cb)(int, int)",
        "char *c",
    ]


def test_a_comment_hides_its_text_from_the_scan() -> None:
    masked = ctext.mask('int a; /* f(1) */ char *s = "f(2)";')
    assert "f(" not in masked
    assert len(masked) == len('int a; /* f(1) */ char *s = "f(2)";')


def test_type_loss_measures_how_much_type_a_prototype_names() -> None:
    assert typeloss.strength("Unit *u, s32 n") > typeloss.strength("void *u, s32 n")
    assert typeloss.strength("void") == 0
    assert typeloss.lost_extern({"Unit *"}, {"void *"})
    assert not typeloss.lost_extern({"Unit *"}, {"Unit *"})


def test_type_loss_keys_address_names_by_folder(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    old = {
        "src/a/x.h": "void func_80000000(Unit* u);",
        "src/b/y.h": "void func_80000000(void);",
    }
    new = {"src/b/y.h": "void func_80000000(void);"}
    monkeypatch.setattr(
        typeloss, "sources", lambda rev: iter((old if rev == "old" else new).items())
    )
    before, after = typeloss.scan("old")[0], typeloss.scan("new")[0]
    assert set(before) == {"func_80000000@src/a", "func_80000000@src/b"}
    assert set(after) == {"func_80000000@src/b"}


def test_hex_literals_become_decimal_unless_they_are_bit_operands() -> None:
    assert values.decimal("x = 0x10;") == "x = 16;"
    assert values.decimal("x = a & 0xFF;") == "x = a & 0xFF;"
    assert values.decimalize_fields("    p->x = 0x20;\n") == "    p->x = 32;\n"


def test_byte_initializers_are_classified() -> None:
    assert shapes.numbers("1, 0x2, 3") == bytes([1, 2, 3])
    assert shapes.numbers("1, name") is None
    assert shapes.classify(b"Hello world\0") == "ascii-text"
    assert shapes.classify(bytes([1, 2, 3])) == "bytes"


def test_a_prototype_that_differs_from_its_definition_is_a_problem() -> None:
    tree = decls.Tree(
        {
            "src/a.c": '#include "a.h"\ns32 f(s32 a)\n{\n    return a;\n}\n',
            "include/a.h": "s16 f(s32 a);\n",
        }
    )
    kinds = {(row.kind, row.name) for row in decls.problems(tree)}
    assert any(name == "f" for _kind, name in kinds)
    assert decls.strip_comments("int a; // x\n/* y */int b;").split() == [
        "int",
        "a;",
        "int",
        "b;",
    ]
