#include "game_00.h"

MATCH void UI_DrawWindow(u16 x, u16 y, u16 width, u16 height, s32 style_flags, u8 window_style) {
    RECT*     texture_window;
    POLY_FT4* primitive;
    s32       color;
    s32       style;
    s32       clut_y;
    s32       clut_x;
    u8        flags;

    flags = style_flags;
    style = style_flags & 0xF;
    color = (style == 1) ? 0x48 : 0xAC;

    texture_window    = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor   = (u8*)(texture_window + 1);
    texture_window->y = 240;
    texture_window->x = 0;
    texture_window->w = 16;
    texture_window->h = 16;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, 0xF, texture_window);
    GFX_AddPrim(1, 0xC);

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    if (style == 2) {
        clut_x = (window_style << 5) | 0x10;
        clut_y = 0x1E1;
        PSX_SET_SEMI_TRANSPARENT(primitive);
    } else {
        clut_x = window_style << 5;
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
    primitive->clut = GetClut(clut_x, clut_y);
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    primitive->tpage = 0xF;
    GFX_AddPrim(1, 0x28);
    primitive++;
    if (width < 256) {
        *primitive = primitive[-1];
        setXY4(primitive, x + 4, y, x - 4 + width, y, x + 4, y + height, x - 4 + width, y + height);
        setUV4(primitive, 0, 0, width - 8, 0, 0, height, width - 8, height);
        GFX_AddPrim(1, 0x28);
    } else {
        *primitive = primitive[-1];
        setXY4(primitive, x + 4, y, x + (width >> 1), y, x + 4, y + height, x + (width >> 1), y + height);
        setUV4(primitive, 0, 0, (width >> 1) - 4, 0, 0, height, (width >> 1) - 4, height);
        GFX_AddPrim(1, 0x28);
        primitive++;
        *primitive = primitive[-1];
        setXY4(primitive, x + (width >> 1), y, (x + (width >> 1)) + ((width >> 1) - 4), y, x + (width >> 1), y + height,
               (x + (width >> 1)) + ((width >> 1) - 4), y + height);
        GFX_AddPrim(1, 0x28);
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
    GFX_AddPrim(1, 0x28);

    texture_window    = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor   = (u8*)(texture_window + 1);
    texture_window->x = 0;
    texture_window->y = 0;
    texture_window->h = 256;
    texture_window->w = 256;
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, 0xF, texture_window);
    GFX_AddPrim(1, 0xC);
}
