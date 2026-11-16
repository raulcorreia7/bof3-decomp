#include "area052_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3280(void) {
    s16 column;
    s16 row;
    s16 cell;
    u8  i;

    if (g_GameStateIndex == 5) {
        g_ScriptState->cursor -= 2;
        return;
    }
    column         = FIX_INT(g_Task->pos.x.fixed - COORD_HALF);
    row            = FIX_INT(g_Task->pos.y.fixed - COORD_HALF);
    g_Task->unk_18 = 0;
    g_Task->unk_1C = 0;
    i              = 0;
    do {
        cell = column + i;
        Area_StoreHeight(column + i, row, 0x10);
        g_Task->unk_18 |= (u8)Area_GetCellCode(cell, row) << (i * 8);
        Area_SetCellCode(column + i, row, 0x11);
        Area_StoreHeight(column + i, row + 1, 0x10);
        g_Task->unk_1C |= (u8)Area_GetCellCode(cell, FIX_INT(TO_COORD(row + 1))) << (i * 8);
        Area_SetCellCode(column + i, row + 1, 0x11);
        i++;
    } while (i < 2);
}
#else
INCLUDE_ASM(func_801F3280);
#endif
