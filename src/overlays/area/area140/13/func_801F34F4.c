#include "area140_13.h"

MATCH void func_801F34F4(void) {
    s16 height;

    height               = (u16)COORD_INT(g_Task->z) + 0x10;
    COORD_INT(g_Task->z) = height;
    if (height >= 0x80) {
        Area_SetCellPalette((s32)COORD_INT(g_Task->x), (s32)COORD_INT(g_Task->y));
        Area_ClearCellPalette((s32)(s16)((u16)COORD_INT(g_Task->x) + 1), (s32)(s16)((u16)COORD_INT(g_Task->y) + 1));
        g_Task->step += 1;
    }
    func_801F3950(g_Task->direction_08, COORD_INT(g_Task->z));
}
