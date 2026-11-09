/* Steps the banner ten units up per frame, loading the work state with 3 at the top row. */
/* func_801F3754 (area115), func_801F3768 (area121), func_801F3814
 * (area104), func_801F42B4 (area088) */
MATCH void Area_RaiseHudBanner(void) {
    Actor* work;
    s16    origin_y;

    work           = g_Task;
    origin_y       = work->screen_y - 0xA;
    work->screen_y = origin_y;
    if (origin_y < 201) {
        work->unk_03++;
    }

    if (D_801454F2 != 0 && g_Task->param.unk_0B != 0) {
        goto force;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto force;
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done;
    }
force:
    g_Task->unk_03 = 3;
done:
    Area_DrawHudBanner(0x5C, g_Task->screen_y);
}
