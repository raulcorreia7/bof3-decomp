#include "area030_04.h"

/* Draws one status-panel column at (x, y). */
MATCH void func_801D7D68(s16 x, s16 y, u8 column_mode) {
    s32 i;

    UI_DrawWindow((x + 2), (y + 2), 40, 16, 0, g_WindowStyle);
    func_801E0C80(8, 1);
    func_801E0DCC((u8)(column_mode * 4 + 0x1D), 1, x, y);
    func_801E0DCC((u8)(column_mode * 4 + 0x1E), 1, x, y + 16);
    for (i = 0; i < 4; i++) {
        func_801E0DCC((u8)(column_mode * 4 + 0x1F), 1, x + (i + 1) * 8, y + 16);
    }
    func_801E0DCC((u8)(column_mode * 4 + 0x20), 1, x + 40, y + 16);
}
