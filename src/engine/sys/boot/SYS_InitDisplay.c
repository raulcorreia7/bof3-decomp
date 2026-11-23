#include "engine/slus/slus.h"

/* initializes both display/draw environment pairs used by the
 * boot-side double buffer.
 */
MATCH void SYS_InitDisplay(void) {
    DRAWENV* draw;

    draw = &g_GfxBuffers[0].draw;
    SetDefDrawEnv(draw, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDispEnv(&g_GfxBuffers[0].disp, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDrawEnv(&g_GfxBuffers[1].draw, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    SetDefDispEnv(&g_GfxBuffers[1].disp, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
}
