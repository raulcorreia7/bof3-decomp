from __future__ import annotations

from bof3.source import decls

ENGINE = "src/engine/slus/f.c"
HEADER = "src/overlays/area/area001/13/area001_13.h"
UNIT = "src/overlays/area/area001/13/g.c"


def rows(files: dict[str, str]) -> list[decls.Problem]:
    """Return the signature rows of a tree of the given files."""
    return decls.signature_rows(decls.Tree(files))


def tree(
    proto: str, definition: str = "MATCH void f(s32 x, u8 y) {\n}\n"
) -> dict[str, str]:
    """Build an engine definition, an image header with ``proto`` and a unit that includes it."""
    return {
        ENGINE: definition,
        HEADER: proto + "\n",
        UNIT: '#include "overlays/area/area001/13/area001_13.h"\nvoid g(void) {\n}\n',
    }


def test_a_prototype_with_other_types_is_a_fault() -> None:
    found = rows(tree("void f(s32 x, s32 y);"))
    assert [(r.name, r.file, r.line) for r in found] == [("f", HEADER, 1)]
    assert "void(s32, s32) vs void(s32, u8)" in found[0].detail


def test_the_owner_signature_passes_whatever_the_names() -> None:
    assert rows(tree("void f(s32 a, u8 b);")) == []
    assert rows(tree("extern void f(s32, u8);")) == []


def test_the_non_prototype_form_needs_the_owner_return_type() -> None:
    assert rows(tree("void f();")) == []
    assert [r.name for r in rows(tree("s32 f();"))] == ["f"]


def test_a_sig_kept_comment_keeps_one_prototype() -> None:
    kept = "/* sig-kept: the retail callers pass words. */\nvoid f(s32 x, s32 y);"
    assert rows(tree(kept)) == []
    far = "/* sig-kept: stale. */\n\n\nvoid f(s32 x, s32 y);"
    assert len(rows(tree(far))) == 1


def test_a_hand_assembled_definition_keeps_its_return_type() -> None:
    assert (
        rows(tree("void f(s32 x, u8 y);", "HAND_ASM void f(s32 x, u8 y) {\n}\n")) == []
    )


def test_another_image_with_the_same_address_name_is_another_function() -> None:
    files = tree("void f(s32 x, s32 y);", "")
    files["src/overlays/area/area002/13/f.c"] = "MATCH void f(s32 x, u8 y) {\n}\n"
    assert rows(files) == []


def test_the_definition_of_the_same_image_owns_the_prototype() -> None:
    files = tree("void f(s32 x, s32 y);", "")
    files["src/overlays/area/area001/13/f.c"] = "MATCH void f(s32 x, u8 y) {\n}\n"
    assert [r.name for r in rows(files)] == ["f"]
