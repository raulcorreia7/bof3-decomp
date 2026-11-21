"""The message-id generator masks comments and strings, skips MESSAGE_NONE and rewrites once."""

from __future__ import annotations

import message_ids


def values(text: str) -> set[int]:
    return {value for _, _, value, _ in message_ids.sites(message_ids.masked(text))}


def test_rewrite_names_the_site_once() -> None:
    names = {60: "MSG_060"}
    once = message_ids.rewrite_text("Message_StartAreaMessage(60);", names)
    assert once == "Message_StartAreaMessage(MSG_060);"
    assert message_ids.rewrite_text(once, names) == once
    assert (
        message_ids.rewrite_text("/* Message_Request(60) */", names)
        == "/* Message_Request(60) */"
    )
