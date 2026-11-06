#include "start_08.h"

/* Draws the start-menu row and its two flag indicators. */
MATCH void func_801E14A8(s32 x, s32 y, u8 flags, u8 row, u8 active) {
    u8  color;
    s32 col;
    u8* resource;

    Menu_DrawFilledPanel(x, y, 7, 4);
    func_801644D8(0x14, (x + 7) & 0xFFFF, (y + 5) & 0xFFFF, 0x10, 0x10, 0x80);
    WinDrawCueText((x + 42), (y + 7), active == 0 ? 0x1B : 0x1C);
    color    = -((flags & 1) == 0) & 7;
    resource = Resource_GetText(0x85);
    col      = x + 6;
    UI_DrawText(col, (y + 25), color, 0xFF, resource);
    UI_DrawAsciiString((x + 94), (y + 25), color, D_801D0DC0);
    color = -((flags & 2) == 0) & 7;
    UI_DrawText(col, (y + 41), color, 0xFF, Resource_GetText(0x85));
    UI_DrawAsciiString((x + 94), (y + 41), color, D_801D0DC4);
    Menu_DrawCursorSprite((x + 8) & 0xFFFF, (((row & 0xFF) * 0x10) + y + 0x1C) & 0xFFFF, 0);
}
