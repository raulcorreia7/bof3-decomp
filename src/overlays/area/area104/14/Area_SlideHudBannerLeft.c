#include "area104_14.h"

/* func_801F36CC */
MATCH void Area_SlideHudBannerLeft(void) {
    SELF(Actor)->screen_x -= 0x10;
    if ((s16)SELF(Actor)->screen_x < -0x2F) {
        SELF(Actor)->header.step = 0;
    }

    if (D_801454F2 != 2) {
        SELF(Actor)->header.step = 1;
    }

    Area_DrawHud(16, SELF(Actor)->screen_x);
}
