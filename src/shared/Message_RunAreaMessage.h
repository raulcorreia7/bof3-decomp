/* Starts message AREA_MESSAGE_REQUEST and waits for the message screen to close. One definition shared by the game engine
 * and an area overlay; every change here must verify every member. */
MATCH void Message_RunAreaMessage(void) {
    s8* state;

    state = &D_801448EC;
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
                D_801448EB = 0;
                *state     = 0;
                D_801448ED = 0;
            }
            return;
    }
}
