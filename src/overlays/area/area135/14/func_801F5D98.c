#include "area135_14.h"

/* Saves the cell codes of the two-by-two block under the actor in its gravity word, a byte per cell, and blocks the four cells. */
MATCH void func_801F5D98(void) {
    s32 column;
    s32 row;
    s32 cell;
    u8  i;

    if (g_GameStateIndex == GAME_REQUEST_AREA_CHANGE) {
        g_ScriptState->cursor -= 2;
        return;
    }
    column               = FIX_INT(SELF(Actor)->pos.x.fixed - COORD_HALF);
    SELF(Actor)->gravity = 0;
    row                  = FIX_INT(SELF(Actor)->pos.y.fixed - COORD_HALF);
    i                    = 0;
    do {
        cell = (s16)(i + row);
        Area_HeightSet((s16)column, cell, 0x10);
        SELF(Actor)->gravity |= (u8)Area_CellGetCode((s16)column, cell) << (i * 8);
        Area_CellSetCode((s16)column, (s16)row + i, 0x11);
        Area_HeightSet((s16)((s16)column + 1), cell, 0x10);
        SELF(Actor)->gravity |= (u8)Area_CellGetCode((s16)((s16)column + 1), cell) << ((i + 2) * 8);
        Area_CellSetCode((s16)column + 1, (s16)row + i, 0x11);
        i++;
    } while (i < 2);
}
