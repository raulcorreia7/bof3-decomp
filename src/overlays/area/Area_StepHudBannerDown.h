/* Steps the HUD banner ten units down per frame and clears the work state byte at the bottom row. */
/* func_801F392C (area115), func_801F3940 (area121), func_801F448C
 * (area088), func_801F37EC (area152), func_801F395C (area087) */
MATCH void Area_StepHudBannerDown(void) {
    Actor* work;
    s16    origin_y;

    work           = g_Task;
    origin_y       = work->screen_y + 0xA;
    work->screen_y = origin_y;
    if (origin_y >= 240) {
        work->unk_03 = 0;
    }

    if (D_801454F2 == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
        work         = g_Task;
        work->unk_03 = 1;
    }

    Area_DrawHudBanner(0x5C, g_Task->screen_y);
}
