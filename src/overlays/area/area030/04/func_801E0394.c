#include "area030_04.h"

/* While the scratchpad work-object gate byte is set, decrements it
 * and integrates the object's three velocity components into its three
 * position accumulators. */
MATCH void func_801E0394(void) {
    FishingState* work;

    if (((u8*)g_SpadWork)[0x09] != 0) {
        ((u8*)g_SpadWork)[0x09] = (u8)(((u8*)g_SpadWork)[0x09] - 1u);
        work                    = FISHING_STATE;
        work->motion_34.unk_34 += work->pos_x_0C;
        work->y_38.pos_y += work->cursor_10;
        work->bounce_3C.half.key_3E = (u16)(work->bounce_3C.half.key_3E + work->step_14);
    }
}
