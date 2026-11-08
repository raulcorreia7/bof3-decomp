#include "area030_04.h"

/* Draws the area status panel and its borders at (x, y + 2). */
MATCH void func_801D90FC(s32 x, s16 y) {
    u16 panel_x;
    s16 sx = x;
    s16 sy = y;
    s32 i;

    panel_x = x;
    UI_DrawWindow(panel_x, (y + 2), 139, 20, 0, g_WindowStyle);
    func_801E0C80(9, 1);
    func_801E0DCC(0x3F, 1, sx, sy);
    func_801E0DCC(0x40, 1, (sx + 8), sy);
    func_801E0DCC(0x41, 1, (sx + 16), sy);
    for (i = 0; i < 8; i++) {
        func_801E0DCC(0x26, 1, (sx + 40 + i * 8), sy);
    }
    func_801E0DCC(0x42, 1, (sx + 104), sy);
    func_801E0DCC(0x43, 1, (sx + 120), sy);
    func_801E0DCC(0x44, 1, (sx + 128), sy);
    func_801D799C(sx, (sy + 24), 120, 0);
    func_801E0DCC(0x46, 1, (sx + 128), (sy + 24));
    func_801D799C((sx + 128), (sy + 40), 104, 4);
    func_801E0DCC(0x2A, 1, sx, (sy + 144));
    for (i = 0; i < 15; i++) {
        func_801E0DCC(0x2B, 1, (sx + 8 + i * 8), (sy + 144));
    }
    func_801E0DCC(0x45, 1, (sx + 128), (sy + 136));
}
