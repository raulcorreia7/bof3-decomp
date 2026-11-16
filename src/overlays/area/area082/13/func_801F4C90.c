#include "area082_13.h"

/* Steps the screen ramp colour with the work timer and flags its end. */
MATCH void func_801F4C90(void) {
    s32 level;
    u32 color;

    level      = g_Task->timer;
    color      = (u32)1 << 28 | ((u32)(level / 5 + 6) << 10) | ((u32)(level / 5) << 5) | (u32)(5 - (u8)((u32)level / 24));
    D_8014933A = 0;
    Area_DrawGradient((s32)color);
    g_Task->timer++;
    if (g_Task->timer >= 0x79) {
        D_8014933A = 1;
        g_Task->header.step++;
    }
}
