#include "game_00.h"

MATCH u8 GFX_FindPaletteCell(u8 value) {
    u8        row;
    u8        column;
    const u8* entry;

    for (row = 0u; row < 4u; row++) {
        column = 0u;
        entry  = D_80145D54[row];
        do {
            if (entry[column] == value) {
                ((u8*)&D_1F800000)[0] = row;
                ((u8*)&D_1F800000)[1] = column;
                return value;
            }
            column++;
        } while ((u32)column < 16u);
    }
    return 0xFFu;
}
