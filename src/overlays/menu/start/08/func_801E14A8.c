#include "start_08.h"

/* Draws the start-menu row and its two flag indicators. */
MATCH void func_801E14A8(s32 x, s32 y, u8 flags, u8 row, u8 active) {
    u8  color;
    s32 col;
    u8* resource;

    Menu_DrawFilledPanel(x, y, 7, 4);
    func_801644D8(20, (x + 7) & HALF_MASK, (y + 5) & HALF_MASK, 16, 16, 0x80);
    WinDrawCueText((x + 42), (y + 7), active == 0 ? 0x1B : 0x1C);
    color    = -((flags & 0x1) == 0) & 0x7;
    resource = Message_GetText(0x85);
    col      = x + 6;
    UI_DrawText(col, (y + 25), color, TEXT_LENGTH_MAX, resource);
    UI_DrawAsciiString((x + 94), (y + 25), color, D_801D0DC0);
    color = -((flags & 0x2) == 0) & 0x7;
    UI_DrawText(col, (y + 41), color, TEXT_LENGTH_MAX, Message_GetText(0x85));
    UI_DrawAsciiString((x + 94), (y + 41), color, D_801D0DC4);
    Menu_DrawCursorSprite((x + 8) & HALF_MASK, (((row & BYTE_MASK) * 0x10) + y + 0x1C) & HALF_MASK, 0);
}
