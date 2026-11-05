/* Slides the banner x coordinate sixteen pixels left per frame and clears
 * the handler index off the left edge; with screen mode 2 it holds state 1,
 * and draws HUD record 0x10 at the banner x coordinate.
 */
/* func_801F360C (area115), func_801F3620 (area121), func_801F416C
 * (area088), func_801F363C (area087) */
MATCH void Area_SlideHudBannerLeft(void) {
    Actor* work;
    s16    origin_x;
    u8     mode;

    work         = g_SpadWork;
    origin_x     = work->unk_2E - 0x10;
    work->unk_2E = origin_x;
    if (origin_x < -47) {
        work->state_02 = 0;
    }

    if (D_801454F2 != 2) {
        mode           = 1;
        work           = g_SpadWork;
        work->state_02 = mode;
    }

    Area_DrawHud(0x10, g_SpadWork->unk_2E);
}
