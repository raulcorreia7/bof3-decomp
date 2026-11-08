from __future__ import annotations

import sys
from pathlib import Path

import pytest

from bof3.source import ctext, decls, index

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import symbol
import typeloss


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


def test_type_loss_allows_only_the_recorded_integer_correction(
    monkeypatch: pytest.MonkeyPatch,
) -> None:
    path = "src/overlays/area/area075/13/area075_13.h"
    old = {path: "void func_801F2E64(void* arg0, s32 arg1);"}
    new = {path: "void func_801F2E64(s32 arg0, s32 arg1);"}
    monkeypatch.setattr(
        typeloss, "sources", lambda rev: iter((old if rev == "old" else new).items())
    )
    assert typeloss.main(["old", "new"]) == 0
    new[path] = "void func_801F2E64(u32 arg0, s32 arg1);"
    assert typeloss.main(["old", "new"]) == 1
    new[path] = (
        "void func_801F2E64(s32 arg0, s32 arg1);\nvoid func_801F2E64(u32 arg0, s32 arg1);"
    )
    assert typeloss.main(["old", "new"]) == 1


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


def test_tables_with_lists_every_image_that_has_the_row():
    text = '["a/1"]\nFoo = { addr = 0x1 }\nBar = { addr = 0x2 }\n["b/2"]\nFoo = { addr = 0x1 }\n'
    assert symbol.tables_with(text, "Foo") == ["a/1", "b/2"]
    assert symbol.tables_with(text, "Bar") == ["a/1"]
