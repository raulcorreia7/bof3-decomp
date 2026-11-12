#include "area140_13.h"

MATCH void func_801F34F4(void) {
    s16 height;

    height                   = (u16)COORD_INT(g_Task->pos.z) + 0x10;
    COORD_INT(g_Task->pos.z) = height;
    if (height >= 128) {
        Area_SetCellPalette((s32)COORD_INT(g_Task->pos.x), (s32)COORD_INT(g_Task->pos.y));
        Area_ClearCellPalette((s32)(s16)((u16)COORD_INT(g_Task->pos.x) + 1), (s32)(s16)((u16)COORD_INT(g_Task->pos.y) + 1));
        g_Task->header.step += 1;
    }
    func_801F3950(g_Task->direction_08, COORD_INT(g_Task->pos.z));
}
