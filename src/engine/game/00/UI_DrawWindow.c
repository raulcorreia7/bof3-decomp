#include "game_00.h"

MATCH void UI_DrawWindow(u16 x, u16 y, u16 width, u16 height, s32 frame_flags, u8 palette) {
    RECT*     texture_window;
    POLY_FT4* primitive;
    s32       color;
    s32       style;
    s32       clut_y;
    s32       clut_x;
    u8        flags;

    flags = frame_flags;
    style = frame_flags & 0xF;
    color = (style == 1) ? 0x48 : 0xAC;

    texture_window    = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor   = (u8*)(texture_window + 1);
    texture_window->y = 240;
    texture_window->x = 0;
    setWH(texture_window, 16, 16);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), texture_window);
    GFX_AddPrim(1, sizeof(DR_MODE));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    if (style == 2) {
        clut_x = (palette << 5) | 0x10;
        clut_y = 0x1E1;
        SetSemiTrans(primitive, 1);
    } else {
        clut_x = palette << 5;
        clut_y = 0x1E1;
    }
    primitive->b0 = color;
    primitive->g0 = color;
    primitive->r0 = color;
    setXY4(primitive, x, y, x + 4, y, x, y + height, x + 4, y + height);
    setUV4(primitive, x, y, x + 4, y, x, y + height, x + 4, y + height);
    if (flags & 0x80) {
        primitive->y0 += 4;
        primitive->v0 += 4;
    }
    if (flags & 0x20) {
        primitive->y2 -= 4;
        primitive->v2 -= 4;
    }
    setClut(primitive, clut_x, clut_y);
    primitive->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1, sizeof(POLY_FT4));
    primitive++;
    if (width < 256) {
        *primitive = primitive[-1];
        setXY4(primitive, x + 4, y, x - 4 + width, y, x + 4, y + height, x - 4 + width, y + height);
        setUV4(primitive, 0, 0, width - 8, 0, 0, height, width - 8, height);
        GFX_AddPrim(1, sizeof(POLY_FT4));
    } else {
        *primitive = primitive[-1];
        setXY4(primitive, x + 4, y, x + (width >> 1), y, x + 4, y + height, x + (width >> 1), y + height);
        setUV4(primitive, 0, 0, (width >> 1) - 4, 0, 0, height, (width >> 1) - 4, height);
        GFX_AddPrim(1, sizeof(POLY_FT4));
        primitive++;
        *primitive = primitive[-1];
        setXY4(primitive, x + (width >> 1), y, (x + (width >> 1)) + ((width >> 1) - 4), y, x + (width >> 1), y + height, (x + (width >> 1)) + ((width >> 1) - 4), y + height);
        GFX_AddPrim(1, sizeof(POLY_FT4));
    }
    primitive++;
    *primitive = primitive[-1];

    setXY4(primitive, x + width - 4, y, x + width, y, x + width - 4, y + height, x + width, y + height);
    setUV4(primitive, x + width - 4, y, x + width, y, x + width - 4, y + height, x + width, y + height);
    if (flags & 0x40) {
        primitive->y1 += 4;
        primitive->v1 += 4;
    }
    if (flags & 0x10) {
        primitive->y3 -= 4;
        primitive->v3 -= 4;
    }
    GFX_AddPrim(1, sizeof(POLY_FT4));

    texture_window    = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor   = (u8*)(texture_window + 1);
    texture_window->x = 0;
    texture_window->y = 0;
    texture_window->h = 256;
    texture_window->w = 256;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), texture_window);
    GFX_AddPrim(1, sizeof(DR_MODE));
}
