/* Starts the area message and requests the message game state. */
/* Scene_ShowMessage (scena03), Scene_ShowMessage (scena04) */
MATCH s32 Scene_ShowMessage(s32 message_index) {
    Message_StartAreaMessage(message_index & BYTE_MASK);
    g_GameStateIndex = GAME_REQUEST_MESSAGE;
    g_GameFlags |= GAME_FLAG_SCRIPT_ACTIVE;
    return 1;
}
