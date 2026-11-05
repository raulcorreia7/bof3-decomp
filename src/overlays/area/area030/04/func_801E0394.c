#include "area030_04.h"

/* While the scratchpad work-object gate byte is set, decrements it
 * and integrates the object's three velocity components into its three
 * position accumulators. */
MATCH void func_801E0394(void) {
    FishingState* work;

    if (g_SpadWork->unk_09 != 0) {
        g_SpadWork->unk_09 = (u8)(g_SpadWork->unk_09 - 1u);
        work               = FISHING_STATE;
        work->motion_34.unk_34 += work->pos_x_0C;
        work->y_38.pos_y += work->cursor_10;
        *(u16*)((u8*)work + 0x3E) = (u16)(*(u16*)((u8*)work + 0x3E) + work->step_14);
    }
}
