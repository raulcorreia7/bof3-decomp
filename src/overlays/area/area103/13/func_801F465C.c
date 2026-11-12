#include "area103_13.h"

MATCH void func_801F465C(void) {
    s16 count;

    if (g_Task->timer == 15) {
        g_Task->timer = 0;
    }
    count = g_Task->unk_32;
    if (count > 0) {
        g_Task->unk_32 = count - 1;
    } else if (!((g_Task->timer / 5) & BYTE_MASK)) {
        g_Task->header.step += 1;
    }
    if (!((g_Task->timer % 5) & BYTE_MASK)) {
        func_801F4E70(((g_Task->timer / 5) & BYTE_MASK) + 7);
    }
    g_Task->timer += 1;
    Area_SetCellPalette(66, (s16)(((s16)g_Task->unk_32 / 6) + 0x18));
}
