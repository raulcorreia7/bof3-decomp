#include "engine/slus/slus.h"

/* resets the palette work area. */
MATCH void GFX_ResetPaletteFades(void) {
    u8  entry;
    u8  row;
    u8  column;
    u8* map;

    for (entry = 0; entry < PALETTE_FADE_COUNT; entry++) {
        g_PaletteFades[entry].flags = 0;
    }

    for (row = 0; row < PALETTE_MAP_ROWS; row++) {
        column = 0;
        map    = D_80145D54[row];
        do {
            map[column] = 0xFF;
            column++;
        } while (column < 16u);
    }
}
