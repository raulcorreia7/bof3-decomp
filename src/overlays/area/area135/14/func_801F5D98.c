#include "area135_14.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F5D98(void) {
    s32 column;
    s16 row;
    s16 cell;
    s16 column_next;
    u8  i;

    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        g_ScriptState->cursor -= 2;
        return;
    }
    column               = FIX_INT(TASK(Actor)->pos.x.fixed - COORD_HALF);
    TASK(Actor)->gravity = 0;
    row                  = FIX_INT(TASK(Actor)->pos.y.fixed - COORD_HALF);
    column_next          = column + 1;
    i                    = 0;
    do {
        cell = row + i;
        Area_HeightSet(column, cell, 0x10);
        TASK(Actor)->gravity |= (u8)Area_CellGetCode(column, cell) << (i * 8);
        Area_CellSetCode(column, row + i, 0x11);
        Area_HeightSet(column_next, cell, 0x10);
        TASK(Actor)->gravity |= (u8)Area_CellGetCode(column_next, cell) << ((i + 2) * 8);
        Area_CellSetCode(column + 1, row + i, 0x11);
        i++;
    } while (i < 2);
}
#else
INCLUDE_ASM(func_801F5D98);
#endif
