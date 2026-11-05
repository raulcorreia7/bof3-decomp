/* Steps the HUD banner ten units down per frame and clears the work state
 * byte at the bottom row; without the screen-mode flag and with no message
 * or script active it loads state 1 instead, and draws the banner record
 * 0x5C at the work y coordinate.
 */
/* func_801F392C (area115), func_801F3940 (area121) */
MATCH void Area_StepHudBannerDown(void) {
Actor* work;
    s16    origin_y;

    work         = g_SpadWork;
    origin_y     = work->unk_30 + 0xA;
    work->unk_30 = origin_y;
    if (origin_y >= 240) {
        work->unk_03 = 0;
    }

    if (D_801454F2 == 0 && g_GameStateIndex != GAME_REQUEST_MESSAGE && GAME_SCRIPT_ACTIVE() == 0) {
        work         = g_SpadWork;
        work->unk_03 = 1;
    }

    Area_DrawHudBanner(0x5C, g_SpadWork->unk_30);
}
