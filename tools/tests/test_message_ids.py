"""The message-id generator masks comments and strings, skips MESSAGE_NONE and rewrites once."""

from __future__ import annotations

import message_ids


def values(text: str) -> set[int]:
    return {value for _, _, value, _ in message_ids.sites(message_ids.masked(text))}


def test_sites_reads_every_site_and_skips_message_none() -> None:
    text = (
        "Message_StartAreaMessage(0x30);\n"
        "Message_Request(MSG_060);\n"
        "MESSAGE_START_WAIT(0x2A1u);\n"
        "g_MessageRequest = 0xFFFF;\n"
        "MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, 96);\n"
    )
    assert values(text) == {0x30, 60, 0x2A1, 96}


def test_rewrite_names_the_site_once() -> None:
    names = {60: "MSG_060"}
    once = message_ids.rewrite_text("Message_StartAreaMessage(60);", names)
    assert once == "Message_StartAreaMessage(MSG_060);"
    assert message_ids.rewrite_text(once, names) == once
    assert (
        message_ids.rewrite_text("/* Message_Request(60) */", names)
        == "/* Message_Request(60) */"
    )


def test_a_tagged_module_gets_its_names() -> None:
    message_ids.TAG_NAMES.clear()
    message_ids.TAG_NAMES["MSG_AREA037_ASK_REST"] = ("area037", 2)
    try:
        names = {2: "MSG_AREA037_ASK_REST", 7: "MSG_AREA037_007"}
        assert (
            message_ids.rewrite_text(
                "Message_Request(MSG_002); Message_Request(7);", names
            )
            == "Message_Request(MSG_AREA037_ASK_REST); Message_Request(MSG_AREA037_007);"
        )
        assert message_ids.tag_name("area037", 7, None) == "MSG_AREA037_007"
    finally:
        message_ids.TAG_NAMES.clear()


def test_message_request_reads_the_system_table() -> None:
    message_ids.TAG_NAMES.clear()
    message_ids.TAG_NAMES_SECTIONS.add("system")
    try:
        text = "Message_Request(5); Message_StartAreaMessage(5);"
        out = message_ids.rewrite_text(
            text, {5: "MSG_AREA037_005"}, {5: "MSG_SYSTEM_005"}
        )
        assert (
            out
            == "Message_Request(MSG_SYSTEM_005); Message_StartAreaMessage(MSG_AREA037_005);"
        )
    finally:
        message_ids.TAG_NAMES_SECTIONS.clear()
