#include "engine/slus/slus.h"

/* clears the four 0x200-byte rows 0x1C..0x1F of the 0x80033800 palette
 * work area, then copies all 0x20 rows of that area into the palette
 * destination at g_GraphicsPaletteDst.
 */
MATCH void GFX_PaletteReset(void) {
    u16  row;
    u16  column;
    u16* row_base;

    for (row = AREA_PALETTE_ROWS - 4; row < AREA_PALETTE_ROWS; row++) {
        column   = 0;
        row_base = (u16*)((u8*)MEM_PTR(const u16, AREA_PALETTE_ARENA) + row * AREA_PALETTE_ROW);
        while (column < AREA_PALETTE_COLORS) {
            row_base[column] = 0;
            column++;
        }
    }

    for (row = 0; row < AREA_PALETTE_ROWS; row++) {
        memcpy((u8*)g_GraphicsPaletteDst + row * AREA_PALETTE_ROW, (u8*)MEM_PTR(const u16, AREA_PALETTE_ARENA) + row * AREA_PALETTE_ROW, AREA_PALETTE_ROW);
    }
}
