#include "sisyou_00.h"

MATCH void Menu_DrawSelectionBox(s32 x, s32 y, s32 width, s32 height, u8 color, u8 mask) {
    LINE_F3* line3;
    LINE_F4* line4;
    u8       rgb[3];
    u32      shade;
    u8       bit;
    u8       i;
    s32      x_corner;
    s32      y_corner;
    s32      y_bottom;

    if (color != 0) {
        shade = (((g_FrameCount & 0x8) ? (g_FrameCount & 0x6) : (~g_FrameCount & 0x6)) << 5) | 0x3F;
    } else {
        shade = 0xFF;
    }
    bit = 1;
    for (i = 0; i < BATTLE_PARTY_CHARACTERS_COUNT; i++) {
        if (mask & bit) {
            rgb[i] = shade;
        } else {
            rgb[i] = 0;
        }
        bit <<= 1;
    }

    line3 = (LINE_F3*)g_GfxPrimCursor;
    SetLineF3(line3);
    x_corner = x + 4;
    y_bottom = y + height - 1;
    y_corner = y + 4;
    setXY3(line3, x_corner, y, x, y_corner, x, y_bottom);
    setRGB0(line3, rgb[2], rgb[1], rgb[0]);
    GFX_AddPrim(1, sizeof(LINE_F3));

    line4 = (LINE_F4*)g_GfxPrimCursor;
    SetLineF4(line4);
    /* DIAG(1): the original stores the quad corners x0,y0,x3,y3,y1,y2,x2,x1;
     * the scheduler preserves statement order here, so spell that order. */
    setXY0(line4, x_corner, y);
    line4->x3 = x;
    line4->y3 = y_bottom;
    line4->y1 = y;
    line4->y2 = y_bottom;
    line4->x1 = (line4->x2 = x + width - 1);
    setRGB0(line4, rgb[2], rgb[1], rgb[0]);
    GFX_AddPrim(1, sizeof(LINE_F4));
}
