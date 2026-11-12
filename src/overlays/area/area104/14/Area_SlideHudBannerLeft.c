#include "area104_14.h"

/* func_801F36CC */
MATCH void Area_SlideHudBannerLeft(void) {
    g_Task->screen_x -= 0x10;
    if ((s16)g_Task->screen_x < -0x2F) {
        g_Task->header.step = 0;
    }

    if (D_801454F2 != 2) {
        g_Task->header.step = 1;
    }

    Area_DrawHud(16, g_Task->screen_x);
}
