from __future__ import annotations

from check_drafts import DRAFT, arguments_for

COMMANDS = {
    "src/a/x.c": [
        "python",
        "cc.py",
        "--build-dir",
        "/b",
        "--empty-on-failure",
        "-O2",
        "-DNON_MATCHING",
        "-Isrc/a",
        "-MMD",
        "-MP",
        "-MF",
        "x.d",
        "-c",
        "src/a/x.c",
        "-o",
        "x.o",
    ]
}


def test_a_draft_marker_starts_a_line() -> None:
    assert DRAFT.search("#ifdef NON_MATCHING\nNON_MATCHING void f(void) {\n}\n")
    assert not DRAFT.search("/* NON_MATCHING in a comment */\n#ifdef NON_MATCHING\n")


def test_flags_come_from_the_draft_without_the_build_options() -> None:
    assert arguments_for("src/a/x.c", COMMANDS) == ["-O2", "-DNON_MATCHING", "-Isrc/a"]


def test_a_new_source_borrows_the_flags_of_its_folder() -> None:
    assert arguments_for("src/a/y.c", COMMANDS) == ["-O2", "-DNON_MATCHING", "-Isrc/a"]
    assert arguments_for("src/b/y.c", COMMANDS) is None
