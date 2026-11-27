#include "area052_13.h"

/* Saves the cell codes of the two-by-two block under the actor in its two words, a byte per cell, and blocks the four cells. */
MATCH void func_801F3280(void) {
    s32 column;
    s32 row;
    s32 cell;
    u8  i;

    if (g_GameStateIndex == 5) {
        g_ScriptState->cursor -= 2;
        return;
    }
    column              = FIX_INT(SELF(Actor)->pos.x.fixed - COORD_HALF);
    row                 = FIX_INT(SELF(Actor)->pos.y.fixed - COORD_HALF);
    SELF(Actor)->unk_18 = 0;
    SELF(Actor)->unk_1C = 0;
    i                   = 0;
    do {
        Area_HeightSet((s16)column + i, (s16)row, 0x10);
        cell = (s16)(i + column);
        SELF(Actor)->unk_18 |= (u8)Area_CellGetCode(cell, (s16)row) << (i * 8);
        Area_CellSetCode((s16)column + i, (s16)row, 0x11);
        Area_HeightSet((s16)column + i, (s16)row + 1, 0x10);
        SELF(Actor)->unk_1C |= (u8)Area_CellGetCode(cell, (s16)((s16)row + 1)) << (i * 8);
        Area_CellSetCode((s16)column + i, (s16)row + 1, 0x11);
        i++;
    } while (i < 2);
}
