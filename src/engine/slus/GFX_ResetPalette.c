#include "engine/slus/slus.h"

/* clears the four 0x200-byte rows 0x1C..0x1F of the 0x80033800 palette
 * work area, then copies all 0x20 rows of that area into the palette
 * destination at g_GraphicsPaletteDst.
 */
MATCH void GFX_ResetPalette(void) {
    u16  row;
    u16  column;
    u16* row_base;

    for (row = 28; (u32)row < 32u; row++) {
        column   = 0;
        row_base = (u16*)((u8*)MEM_PTR(const u16, 0x80033800u) + (u32)row * 0x200);
        while ((u32)column < 256u) {
            row_base[column] = 0;
            column++;
        }
    }

    for (row = 0; (u32)row < 32u; row++) {
        memcpy((u8*)g_GraphicsPaletteDst + (u32)row * 0x200, (u8*)MEM_PTR(const u16, 0x80033800u) + (u32)row * 0x200,
               0x200);
    }
}
