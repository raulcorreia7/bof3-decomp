#include "area052_13.h"

MATCH void func_801F43B0(void) {
    Coord x;
    Coord y;

    Area_GetCursor(&x.fixed, &y.fixed);
    Area_StoreHeight(--COORD_INT(x), COORD_INT(y), 0x10);
    g_Task->unk_18 |= (u8)Area_GetCellCode(COORD_INT(x), COORD_INT(y));
    func_801A4BC0(COORD_INT(x), COORD_INT(y), 0x11);
    Area_StoreHeight(COORD_INT(x), ++COORD_INT(y), 0x10);
    g_Task->unk_1C |= (u8)Area_GetCellCode(COORD_INT(x), COORD_INT(y));
    func_801A4BC0(COORD_INT(x), COORD_INT(y), 0x11);
    g_Task->direction_08 = FACING_LEFT;
    func_801ABBA8(g_ScriptState, 7);
    g_ScriptState->unk_07 = 2;
}
