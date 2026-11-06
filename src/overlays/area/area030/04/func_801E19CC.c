#include "area030_04.h"

/* Draws the AREA030 selector box. */
MATCH void func_801E19CC(s32 x, s32 y) {
    u16 panel_x;
    s16 sx = x;
    s16 sy = y;
    s32 i;

    panel_x = x;
    UI_DrawWindow(panel_x, ((y + 1)), 0xB3, 0x42, 0x80, g_SaveData.window_style);
    func_801E0C80(9, 1);
    func_801E0DCC(0x25, 1, sx, sy);
    for (i = 0; i < 15; i++) {
        func_801E0DCC(0x26, 1, (sx + 0x20 + i * 8), sy);
    }
    func_801E0DCC(0x27, 1, (sx + 0x98), sy);
    func_801E0DCC(0x28, 1, (sx + 0xB0), sy);
    func_801D799C(sx, (sy + 0x18), 0x28, 0);
    func_801D799C((sx + 0xB0), (sy + 0x18), 0x28, 1);
    func_801E0DCC(0x30, 1, sx, (sy + 0x40));
    for (i = 0; i < 21; i++) {
        func_801E0DCC(0x31, 1, (sx + 8 + i * 8), (sy + 0x40));
    }
    func_801E0DCC(0x32, 1, (sx + 0xB0), (sy + 0x40));
    UI_DrawText((sx + 0x3E), (sy + 6), 0, 0xFF, (u8*)(FISHING_TEXT_BANK + D_80010078));
    UI_DrawText((sx + 6), (sy + 0x19), 0, 0xFF, (u8*)(FISHING_TEXT_BANK + D_80010082));
}
