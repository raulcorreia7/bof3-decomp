/* Starts message AREA_MESSAGE_REQUEST and waits for the message screen to close. */
MATCH void UI_MessageRunArea(void) {
    s8* state;

    state = &g_SceneEventState.step;
    switch (*state) {
        case 0:
            Game_SetScriptActive();
            UI_MessageStartArea(AREA_MESSAGE_REQUEST);
            g_GameStateIndex = GAME_REQUEST_MESSAGE;
            *state           = (u8)*state + 1;
            return;
        case 1:
            if (g_GameStateIndex != GAME_REQUEST_MESSAGE) {
                Game_ClearScriptActive();
                g_SceneEventState.mode      = SCENE_EVENT_NONE;
                *state                      = 0;
                g_SceneEventState.selection = 0;
            }
            return;
    }
}
