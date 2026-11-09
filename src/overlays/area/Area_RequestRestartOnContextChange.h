/* Outside a game-entry state 1. */
/* func_801F32A4 (area115), func_801F32B8 (area121) */
MATCH void Area_RequestRestartOnContextChange(void) {
    Actor* work;
    u8     step;

    Actor_CenterOnScreen();
    if (g_GameEntryState != 1) {
        work = g_Task;
        step = work->param.unk_0B;
        if (step == work->option_flags && g_GameStateIndex != GAME_REQUEST_AREA_CHANGE) {
            if (step != 1) {
                goto tail;
            }
            if (work->unk_18 == g_GameContextSeed) {
                goto tail;
            }
        }
        g_Task->unk_48      = 2;
        g_Task->timer       = 8;
        g_Task->header.mode = 4;
    }
tail:
    Area_AddActor();
}
