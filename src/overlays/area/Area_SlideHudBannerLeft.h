/* Slides the banner x coordinate sixteen pixels left per frame and clears the handler index off the left edge. */
/* func_801F360C (area115), func_801F3620 (area121), func_801F416C
 * (area088), func_801F363C (area087) */
MATCH void Area_SlideHudBannerLeft(void) {
    Actor* work;
    s16    origin_x;
    u8     mode;

    work           = g_Task;
    origin_x       = work->screen_x - 0x10;
    work->screen_x = origin_x;
    if (origin_x < -47) {
        work->header.step = 0;
    }

    if (D_801454F2 != 2) {
        mode              = 1;
        work              = g_Task;
        work->header.step = mode;
    }

    Area_DrawHud(0x10, g_Task->screen_x);
}
