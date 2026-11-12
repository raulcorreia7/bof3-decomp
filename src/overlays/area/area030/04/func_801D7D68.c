#include "area030_04.h"

/* Draws one status-panel column at (x, y): the panel frame, two
 * label rows, four row icons and the footer; column_mode (the caller passes one bit of
 * its mask) selects the second set of sprite ids, 4 apart. */
MATCH void func_801D7D68(s16 x, s16 y, u8 column_mode) {
    s32 i;

    UI_DrawWindow((x + 2), (y + 2), 40, 16, 0, g_WindowStyle);
    Fishing_SetDrawMode(8, 1);
    Fishing_DrawSprite((u8)(column_mode * 4 + 0x1D), 1, x, y);
    Fishing_DrawSprite((u8)(column_mode * 4 + 0x1E), 1, x, y + 16);
    for (i = 0; i < 4; i++) {
        Fishing_DrawSprite((u8)(column_mode * 4 + 0x1F), 1, x + (i + 1) * 8, y + 16);
    }
    Fishing_DrawSprite((u8)(column_mode * 4 + 0x20), 1, x + 40, y + 16);
}
