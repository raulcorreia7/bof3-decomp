/* Counts the hold timer at byte 0x09 up to 90 frames and flags it at byte 0x0B. */
/* func_801F382C (area115), func_801F3840 (area121), func_801F438C
 * (area088), func_801F385C (area087) */
MATCH void Area_CountHudBannerHold(void) {
    Actor* work;

    work = g_Task;
    if (work->param.unk_0B == 0) {
        work->timer++;
        work = g_Task;
        if (work->timer >= 90) {
            work->param.unk_0B++;
        }
    }

    if (D_801454F2 != 0 && g_Task->param.unk_0B != 0) {
        goto bump;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump;
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done;
    }
bump:
    g_Task->unk_03++;
done:
    Area_DrawHudBanner(0x5C, g_Task->screen_y);
}
