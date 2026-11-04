#include "start_08.h"

/* Frame-state word owned by the main executable. */

MATCH void Menu_DrawCursorFrame(u16 x, u16 y, s32 width, s32 height, u8 color, s32 mask) {
    u8       rgb[3];
    u8       base;
    u8       i;
    s32      width_copy;
    s32      bit;
    s32      state;
    LINE_F3* line3;
    LINE_F4* line4;

    width_copy = width; /* FAKE: width_copy steers prologue copy order. */
    mask       = (u8)mask;

    if (color != 0) {
        state = g_FrameCount;
        if (state & 8) {
            base = (u8)((state & 6) << 5 | 0x3F);
        } else {
            base = (u8)((~state & 6) << 5 | 0x3F);
        }
    } else {
        base = 0xFF;
    }

    for (bit = 1, i = 0; i < BATTLE_PARTY_SLOT_COUNT; i++, bit <<= 1) {
        if (bit & mask) {
            rgb[i] = base;
        } else {
            rgb[i] = 0;
        }
    }

    line3 = (LINE_F3*)g_GfxPrimCursor;
    SetLineF3(line3);
    line3->x0 = x + 4;
    line3->y0 = y;
    line3->x1 = x;
    line3->y1 = y + 4;
    line3->x2 = x;
    line3->y2 = y + height - 1;
    setRGB0(line3, rgb[2], rgb[1], rgb[0]);
    GFX_AddPrim(1, sizeof(LINE_F3));

    line4 = (LINE_F4*)g_GfxPrimCursor;
    SetLineF4(line4);
    line4->x0 = x + 4;
    line4->y0 = y;
    line4->x3 = x;
    line4->y3 = y + height - 1;
    line4->y1 = y;
    line4->y2 = y + height - 1;
    line4->x1 = (line4->x2 = x + width_copy - 1);
    setRGB0(line4, rgb[2], rgb[1], rgb[0]);
    GFX_AddPrim(1, sizeof(LINE_F4));
}
