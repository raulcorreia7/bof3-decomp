/* Outside a game-entry state 1, when the work step byte no longer matches
 * the option flags, or a step-1 actor no longer matches the world context
 * seed, arms the restart: byte 0x48 with 2, byte 0x09 with 8 and handler
 * state 4.
 */
/* func_801F32A4 (area115), func_801F32B8 (area121) */
MATCH void Area_RequestRestartOnContextChange(void) {
    Actor* work;
    u8     step;

    Actor_CenterOnScreen();
    if (g_GameEntryState != 1) {
        work = g_SpadWork;
        step = work->unk_0B;
        if (step == work->option_flags && g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
            if (step != 1) {
                goto tail;
            }
            if (work->unk_18 == g_GameContextSeed) {
                goto tail;
            }
        }
        g_SpadWork->unk_48 = 2;
        g_SpadWork->unk_09 = 8;
        g_SpadWork->unk_01 = 4;
    }
tail:
    Area_AddActor();
}
