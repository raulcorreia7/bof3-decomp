#include "engine/game/00/game_00.h"

MATCH u8 GFX_PaletteFindCell(u8 value) {
    u8        row;
    u8        column;
    const u8* entry;

    for (row = 0u; row < 4u; row++) {
        column = 0u;
        entry  = g_PaletteCells[row];
        do {
            if (entry[column] == value) {
                ((u8*)&g_ScratchPad)[0] = row;
                ((u8*)&g_ScratchPad)[1] = column;
                return value;
            }
            column++;
        } while (column < 16u);
    }
    return 0xFFu;
}
