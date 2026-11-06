#include "area140_13.h"

MATCH void func_801F38C4(void) {
    s16 temp_v0;

    temp_v0              = (u16)COORD_INT(g_Task->z) - 0x10;
    COORD_INT(g_Task->z) = temp_v0;
    if ((temp_v0 << 0x10) <= 0) {
        Area_ClearCellPalette((s32)(s16)((u16)COORD_INT(g_Task->x) + 1), (s32)(s16)((u16)COORD_INT(g_Task->y) + 1));
        g_Task->header.step = 1;
    }
    func_801F3950(g_Task->direction_08, COORD_INT(g_Task->z));
}
