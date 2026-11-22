#include "area104_14.h"

/* func_801F36CC */
MATCH void Area_SlideHudBannerLeft(void) {
    TASK(Actor)->screen_x -= 0x10;
    if ((s16)TASK(Actor)->screen_x < -0x2F) {
        TASK(Actor)->header.step = 0;
    }

    if (D_801454F2 != 2) {
        TASK(Actor)->header.step = 1;
    }

    Area_DrawHud(16, TASK(Actor)->screen_x);
}
