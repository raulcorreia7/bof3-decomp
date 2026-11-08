#include "area030_04.h"

/* Draws the AREA030 shop box, its 8/11-cell rows, the two selection strips and the three record words. */
MATCH void func_801E1758(s32 x, s32 y) {
    s16 sx;
    s16 sy;
    s32 i;

    sy = y;
    sx = x;
    UI_DrawWindow(sx, y + 1, 100, 56, 0x80, g_WindowStyle);
    func_801E0C80(9, 1);
    func_801E0DCC(0x25, 1, sx, sy);
    for (i = 0; i < 8; i++) {
        func_801E0DCC(0x26, 1, sx + 32 + i * 8, sy);
    }
    func_801E0DCC(0x27, 1, sx + 72, sy);
    func_801E0DCC(0x28, 1, sx + 96, sy);
    func_801D799C(sx, sy + 24, 32, 0);
    func_801D799C(sx + 96, sy + 24, 32, 1);
    func_801E0DCC(0x30, 1, sx, sy + 56);
    for (i = 0; i < 11; i++) {
        func_801E0DCC(0x31, 1, sx + 8 + i * 8, sy + 56);
    }
    func_801E0DCC(0x32, 1, sx + 96, sy + 56);
    UI_DrawText(sx + 35, sy + 6, 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MSG_FISH));
    UI_DrawText(sx + 10, sy + 25, 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MSG_RETRY));
    UI_DrawText(sx + 10, sy + 41, 0, 0xFF, MESSAGE_TABLE_TEXT(AREA_MESSAGE_TABLE, FISHING_MSG_EXIT));
}
