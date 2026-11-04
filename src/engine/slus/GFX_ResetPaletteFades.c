#include "engine/slus/slus.h"

/* resets the palette work area: clears the flag byte of each of the
 * 32 0x0C-byte palette work records, then fills the four 16-byte palette maps
 * with 0xFF.
 */
MATCH void GFX_ResetPaletteFades(void) {
    u8  entry;
    u32 offset;
    u8  row;
    u8  column;
    u8* map;

    for (entry = 0; entry < 32; entry++) {
        offset                             = entry * 0x0C;
        *(u8*)((char*)D_80145BD4 + offset) = 0;
    }

    for (row = 0; row < 4; row++) {
        column = 0;
        map    = D_80145D54[row];
        do {
            map[column] = 0xFF;
            column++;
        } while ((u32)column < 16u);
    }
}
