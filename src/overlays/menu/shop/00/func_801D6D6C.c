#include "shop_00.h"

MATCH void func_801D6D6C(s32 strip_x, s32 strip_y) {
    u16 x;
    u16 y;
    s32 i;

    x = strip_x;
    y = strip_y;
    UI_DrawWindow((x + 4), (y + 4), 82, 72, 0, D_80144952);
    Menu_DrawPanelFrame(x, y, 9, 8);
    for (i = 0; (i & 0xFF) < 3U; i++) {
        /* The inner u16 cast keeps the sum grouped as the retail code does. */
        WinDrawCueText(x + 28, (u16)((u8)i * 20 + 11 + y), (i & 0xFF) + 0xD2);
    }
    Menu_DrawCursorSprite((x + 0x1C) & 0xFFFF, (y + 0xD + D_801E60F0 * 0x14) & 0xFFFF, 0);
}
