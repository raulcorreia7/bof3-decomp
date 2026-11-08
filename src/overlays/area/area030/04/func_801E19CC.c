#include "area030_04.h"

/* Draws the AREA030 selector box. */
MATCH void func_801E19CC(s32 x, s32 y) {
    u16 panel_x;
    s16 sx = x;
    s16 sy = y;
    s32 i;

    panel_x = x;
    UI_DrawWindow(panel_x, ((y + 1)), 179, 66, 0x80, g_WindowStyle);
    func_801E0C80(9, 1);
    func_801E0DCC(0x25, 1, sx, sy);
    for (i = 0; i < 15; i++) {
        func_801E0DCC(0x26, 1, (sx + 32 + i * 8), sy);
    }
    func_801E0DCC(0x27, 1, (sx + 152), sy);
    func_801E0DCC(0x28, 1, (sx + 176), sy);
    func_801D799C(sx, (sy + 24), 40, 0);
    func_801D799C((sx + 176), (sy + 24), 40, 1);
    func_801E0DCC(0x30, 1, sx, (sy + 64));
    for (i = 0; i < 21; i++) {
        func_801E0DCC(0x31, 1, (sx + 8 + i * 8), (sy + 64));
    }
    func_801E0DCC(0x32, 1, (sx + 176), (sy + 64));
    UI_DrawText((sx + 62), (sy + 6), 0, 0xFF, MESSAGE_BANK_TEXT(AREA_MESSAGE_BANK, FISHING_MSG_CAUTION));
    UI_DrawText((sx + 6), (sy + 25), 0, 0xFF, MESSAGE_BANK_TEXT(AREA_MESSAGE_BANK, FISHING_MSG_TOO_MANY_ITEMS));
}
