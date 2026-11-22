#include "area151_13.h"

/* func_801F3578 */
MATCH void Area_SlideHudBannerLeft(void) {
    Actor* scratch;
    u8     mode;

    scratch = TASK(Actor);
    scratch->screen_x -= 0x10;
    if ((s16)scratch->screen_x < -0x2F) {
        scratch->header.step = 0;
    }

    if (D_801454F2 != 2) {
        mode                 = 1;
        scratch              = TASK(Actor);
        scratch->header.step = mode;
    }

    Area_DrawHud(16, TASK(Actor)->screen_x);
}
