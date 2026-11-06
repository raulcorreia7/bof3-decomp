/* Starts message AREA_MESSAGE_REQUEST and waits for the message screen to close. One definition shared by the game engine
 * and an area overlay; every change here must verify every member. */
MATCH void Message_RunAreaMessage(void) {
    s8* state;

    state = &g_SaveData.scene_event.step;
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
                g_SaveData.scene_event.mode      = 0;
                *state                           = 0;
                g_SaveData.scene_event.selection = 0;
            }
            return;
    }
}
