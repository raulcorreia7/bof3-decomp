from __future__ import annotations

import sys
from pathlib import Path

import pytest

from bof3.source import ctext, decls

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import typeloss
from bof3.symbols import context


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
    assert context.tables_with(text, "Foo") == ["a/1", "b/2"]
    assert context.tables_with(text, "Bar") == ["a/1"]
