#include "area151_13.h"

/* func_801F3578 */
MATCH void Area_SlideHudBannerLeft(void) {
    Actor* scratch;
    u8     mode;

    scratch = SELF(Actor);
    scratch->screen_x -= 0x10;
    if ((s16)scratch->screen_x < -0x2F) {
        scratch->header.step = 0;
    }

    if (D_801454F2 != 2) {
        mode                 = 1;
        scratch              = SELF(Actor);
        scratch->header.step = mode;
    }

    Area_DrawHud(16, SELF(Actor)->screen_x);
}
