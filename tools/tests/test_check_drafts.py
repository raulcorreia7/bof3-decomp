from __future__ import annotations

from check_drafts import arguments_for

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


def test_a_new_source_borrows_the_flags_of_its_folder() -> None:
    assert arguments_for("src/a/y.c", COMMANDS) == ["-O2", "-DNON_MATCHING", "-Isrc/a"]
    assert arguments_for("src/b/y.c", COMMANDS) is None
