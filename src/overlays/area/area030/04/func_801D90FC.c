#include "area030_04.h"

/* Draws the area status panel and its borders at (x, y + 2). */
MATCH void func_801D90FC(s32 x, s16 y) {
    u16 panel_x;
    s16 sx = x;
    s16 sy = y;
    s32 i;

    panel_x = x;
    UI_DrawWindow(panel_x, (y + 2), 0x8B, 0x14, 0, g_SaveData.window_style);
    func_801E0C80(9, 1);
    func_801E0DCC(0x3F, 1, sx, sy);
    func_801E0DCC(0x40, 1, (sx + 8), sy);
    func_801E0DCC(0x41, 1, (sx + 0x10), sy);
    for (i = 0; i < 8; i++) {
        func_801E0DCC(0x26, 1, (sx + 0x28 + i * 8), sy);
    }
    func_801E0DCC(0x42, 1, (sx + 0x68), sy);
    func_801E0DCC(0x43, 1, (sx + 0x78), sy);
    func_801E0DCC(0x44, 1, (sx + 0x80), sy);
    func_801D799C(sx, (sy + 0x18), 0x78, 0);
    func_801E0DCC(0x46, 1, (sx + 0x80), (sy + 0x18));
    func_801D799C((sx + 0x80), (sy + 0x28), 0x68, 4);
    func_801E0DCC(0x2A, 1, sx, (sy + 0x90));
    for (i = 0; i < 15; i++) {
        func_801E0DCC(0x2B, 1, (sx + 8 + i * 8), (sy + 0x90));
    }
    func_801E0DCC(0x45, 1, (sx + 0x80), (sy + 0x88));
}
