#include "area030_04.h"

/* Draws the AREA030 shop box, its 8/11-cell rows, the two selection strips and the three record words. */
MATCH void func_801E1758(s32 x, s32 y) {
    s16 sx;
    s16 sy;
    s32 i;

    sy = y;
    sx = x;
    UI_DrawWindow(sx, y + 1, 0x64, 0x38, 0x80, g_WindowStyle);
    func_801E0C80(9, 1);
    func_801E0DCC(0x25, 1, sx, sy);
    for (i = 0; i < 8; i++) {
        func_801E0DCC(0x26, 1, sx + 0x20 + i * 8, sy);
    }
    func_801E0DCC(0x27, 1, sx + 0x48, sy);
    func_801E0DCC(0x28, 1, sx + 0x60, sy);
    func_801D799C(sx, sy + 0x18, 0x20, 0);
    func_801D799C(sx + 0x60, sy + 0x18, 0x20, 1);
    func_801E0DCC(0x30, 1, sx, sy + 0x38);
    for (i = 0; i < 11; i++) {
        func_801E0DCC(0x31, 1, sx + 8 + i * 8, sy + 0x38);
    }
    func_801E0DCC(0x32, 1, sx + 0x60, sy + 0x38);
    UI_DrawText(sx + 0x23, sy + 6, 0, 0xFF, (u8*)(FISHING_TEXT_BANK + D_8001007A));
    UI_DrawText(sx + 0xA, sy + 0x19, 0, 0xFF, (u8*)(FISHING_TEXT_BANK + D_8001007C));
    UI_DrawText(sx + 0xA, sy + 0x29, 0, 0xFF, (u8*)(FISHING_TEXT_BANK + D_8001007E));
}
