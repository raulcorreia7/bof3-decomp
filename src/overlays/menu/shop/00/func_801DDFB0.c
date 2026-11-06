#include "shop_00.h"

MATCH void func_801DDFB0(s16 x, s16 y, u32 flags, u8 row, u8 variant) {
    s16 left;
    s16 right;
    s16 text_y;
    u16 row_offset;
    u8  color;
    u32 shade;
    u8* texture;

    Menu_DrawFilledPanel(x, y, 7, 4);
    func_801644D8(20, (u16)(x + 7), (u16)(y + 5), 16, 16, 128);
    shade = 0x1C;
    if (variant == 0) {
        shade = 0x1B;
    }
    texture = Resource_GetText(shade);
    left    = (x + 6);
    UI_DrawText((x + 42), (y + 7), 0, 0xFF, texture);

    color = (flags & 1) ? 0 : 7;
    UI_DrawText(left, (y + 25), color, 0xFF, Resource_GetText(0x85));
    right  = (x + 94);
    text_y = (y + 25);
    UI_DrawAsciiString(right, text_y, color, &D_801D0E58);

    color = (flags & 2) ? 0 : 7;
    UI_DrawText(left, (y + 41), color, 0xFF, Resource_GetText(0x85));
    text_y = (y + 41);
    UI_DrawAsciiString(right, text_y, color, &D_801D0E5C);

    row_offset = (row << 4);
    Menu_DrawCursorSprite((x + 8), (row_offset + y + 28), 0);
}
