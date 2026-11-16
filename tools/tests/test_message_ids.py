"""The message-id generator masks comments and strings, skips MESSAGE_NONE and rewrites once."""

from __future__ import annotations

import message_ids


def values(text: str) -> set[int]:
    return {value for _, _, value, _ in message_ids.sites(message_ids.masked(text))}


def test_masked_keeps_offsets_and_blanks_comments_and_strings() -> None:
    text = (
        "Message_StartAreaMessage(5);\n"
        "/* Message_StartAreaMessage(6) */\n"
        "// MESSAGE_START_WAIT(7)\n"
        'char* s = "Message_Request(8)";\n'
    )
    masked = message_ids.masked(text)
    assert len(masked) == len(text)
    assert text.count("\n") == masked.count("\n")
    assert values(text) == {5}
    assert "Message_StartAreaMessage(5)" in masked
    assert "Message_StartAreaMessage(6)" not in masked
    assert "Message_Request(8)" not in masked


def test_sites_reads_every_site_and_skips_message_none() -> None:
    text = (
        "Message_StartAreaMessage(0x30);\n"
        "Message_Request(MSG_060);\n"
        "MESSAGE_START_WAIT(0x2A1u);\n"
        "g_MessageRequest = 0xFFFF;\n"
        "MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, 96);\n"
    )
    assert values(text) == {0x30, 60, 0x2A1, 96}


def test_render_sorts_and_pads() -> None:
    text = message_ids.render({7: [], 100: []}, 3)
    assert "#define MSG_007 7" in text
    assert "#define MSG_100 100" in text
    assert text.index("MSG_007") < text.index("MSG_100")


def test_rewrite_names_the_site_once() -> None:
    names = {60: "MSG_060"}
    once = message_ids.rewrite_text("Message_StartAreaMessage(60);", names)
    assert once == "Message_StartAreaMessage(MSG_060);"
    assert message_ids.rewrite_text(once, names) == once
    assert (
        message_ids.rewrite_text("/* Message_Request(60) */", names)
        == "/* Message_Request(60) */"
    )
