/* Counts the hold timer at byte 0x09 up to 90 frames and flags it at byte
 * 0x0B; with the screen-mode flag, a message or a script present it steps
 * the work state, and draws the banner record 0x5C at the work y
 * coordinate.
 */
/* func_801F382C (area115), func_801F3840 (area121) */
MATCH void Area_CountHudBannerHold(void) {
    Actor* work;

    work = g_SpadWork;
    if (work->unk_0B == 0) {
        work->unk_09++;
        work = g_SpadWork;
        if (work->unk_09 >= 0x5A) {
            work->unk_0B++;
        }
    }

    if (D_801454F2 != 0 && g_SpadWork->unk_0B != 0) {
        goto bump;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump;
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done;
    }
bump:
    g_SpadWork->unk_03++;
done:
    Area_DrawHudBanner(0x5C, g_SpadWork->unk_30);
}
