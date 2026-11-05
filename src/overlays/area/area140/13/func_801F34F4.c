#include "area140_13.h"

MATCH void func_801F34F4(void) {
    s16 height;

    height                 = (u16)g_Task->z.part.integer + 0x10;
    g_Task->z.part.integer = height;
    if (height >= 0x80) {
        Area_SetCellPalette((s32)g_Task->x.part.integer, (s32)g_Task->y.part.integer);
        Area_ClearCellPalette((s32)(s16)((u16)g_Task->x.part.integer + 1), (s32)(s16)((u16)g_Task->y.part.integer + 1));
        g_Task->step += 1;
    }
    func_801F3950(g_Task->direction_08, g_Task->z.part.integer);
}
