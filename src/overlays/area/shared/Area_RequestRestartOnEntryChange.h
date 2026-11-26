/* Outside a game-entry state 1, when the work step byte no longer matches
 * the option flags, or a step-1 actor no longer matches the entry
 * area id, arms the restart: byte 0x48 with 2, byte 0x09 with 8 and handler
 * state 4.
 */
/* func_801F31D4 (area033), func_801F32A4 (area115), func_801F32B8 (area121), func_801F32D8 (area065), func_801F3164 (area152), func_801F3E04 (area088) */
MATCH void Area_RequestRestartOnEntryChange(void) {
    Actor* work;
    u8     step;

    Actor_SetScreenOrigin();
    if (g_GameEntryState != 1) {
        work = SELF(Actor);
        step = work->param.unk_0B;
        if (step == work->option_flags && g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
            if (step != 1) {
                goto tail; /* skips the arming stores: run the step only */
            }
            if (work->unk_18 == g_GameEntryAreaId) {
                goto tail; /* skips the arming stores: run the step only */
            }
        }
        SELF(Actor)->unk_48      = 2;
        SELF(Actor)->timer       = 8;
        SELF(Actor)->header.mode = 4;
    }
tail:
    Area_AddActor();
}
