/* Starts message AREA_MESSAGE_REQUEST and waits for the message screen to close. */
MATCH void Message_RunAreaMessage(void) {
    s8* state;

    state = &g_SceneEventStep;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            Message_StartAreaMessage(AREA_MESSAGE_REQUEST);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = (u8)*state + 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventMode      = SCENE_EVENT_NONE;
                *state                = 0;
                g_SceneEventSelection = 0;
            }
            return;
    }
}
