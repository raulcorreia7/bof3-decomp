/* Counts the hold timer at byte 0x09 up to 90 frames and flags it at byte
 * 0x0B; with the screen-mode flag, a message or a script present it steps
 * the work state, and draws the banner record 0x5C at the work y
 * coordinate.
 */
/* func_801F36EC (area152), func_801F3798 (area151), func_801F382C (area115), func_801F3840 (area121), func_801F385C (area087), func_801F438C (area088), func_801F38EC (area104) */
MATCH void Area_CountHudBannerHold(void) {
    Actor* work;

    work = SELF(Actor);
    if (work->param.unk_0B == 0) {
        work->timer++;
        work = SELF(Actor);
        if (work->timer >= 90) {
            work->param.unk_0B++;
        }
    }

    if (D_801454F2 != 0 && SELF(Actor)->param.unk_0B != 0) {
        goto bump;
    }
    if (g_GameStateIndex == GAME_REQUEST_MESSAGE) {
        goto bump;
    }
    if (GAME_SCRIPT_ACTIVE() == 0) {
        goto done;
    }
bump:
    SELF(Actor)->unk_03++;
done:
    Area_DrawHudBanner(0x5C, SELF(Actor)->screen_y);
}
