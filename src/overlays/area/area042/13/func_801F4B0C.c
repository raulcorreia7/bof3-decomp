#include "area042_13.h"

#ifdef NON_MATCHING
/* Draws a window panel in four quads (edges and two halves of the middle), then its frame. */
NON_MATCHING void func_801F4B0C(s16 x, s16 y, s16 width, s16 height, u8 mode) {
    RECT*     texture_window;
    POLY_FT4* primitive;
    s32       color;
    u8        abr;
    s16       half;
    u16       odd;

    color = 0xAC;
    if (mode != 0) {
        color = 0xFF;
    }
    abr = mode != 0;

    texture_window    = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor   = (u8*)(texture_window + 1);
    texture_window->y = 240;
    texture_window->x = 0;
    setWH(texture_window, 16, 16);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, abr, FONT_TPAGE_X, FONT_TPAGE_Y), texture_window);
    width++;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    height++;

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    setXY4(primitive, x, y, x + 2, y, x, y + height, x + 2, y + height);
    setUV4(primitive, 0, 0, 2, 0, 0, height, 2, height);
    setRGB0(primitive, color, color, color);
    primitive->y0 += 2;
    primitive->y2 -= 3;
    primitive->v0 += 2;
    primitive->v2 -= 3;
    primitive->clut  = GetClut((mode << 5) | 0x10, 0x1E1);
    primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, abr, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    odd  = (width - 4) & 1;
    half = ((u16)width - 4) >> 1;

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    setXY4(primitive, x + 2, y, (s16)(x + 2) + half, y, x + 2, y + height, (s16)(x + 2) + half, y + height);
    setUV4(primitive, 0, 0, half, 0, 0, height, half, height);
    setRGB0(primitive, color, color, color);
    primitive->clut  = GetClut((mode << 5) | 0x10, 0x1E1);
    primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, abr, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    setXY4(primitive, x + half + 2, y, x + half + (s16)(half + odd + 2), y, x + half + 2, y + height, x + half + (s16)(half + odd + 2), y + height);
    setUV4(primitive, 0, 0, half + odd, 0, 0, height, half + odd, height);
    setRGB0(primitive, color, color, color);
    primitive->clut  = GetClut((mode << 5) | 0x10, 0x1E1);
    primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, abr, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    primitive->x2 = x + width - 2;
    setRGB0(primitive, color, color, color);
    primitive->x0 = x + width - 2;
    primitive->y2 = y + height;
    primitive->v2 = height;
    primitive->x1 = x + width;
    primitive->x3 = x + width;
    primitive->y1 = y;
    primitive->u1 = 2;
    primitive->u3 = 2;
    primitive->y3 = y + height;
    primitive->u0 = 0;
    primitive->v0 = 0;
    primitive->y0 = y;
    primitive->u2 = 0;
    primitive->v3 = height;
    primitive->v1 = 0;
    primitive->y2 -= 1;
    primitive->v2 -= 1;
    primitive->y1 += 2;
    primitive->y3 -= 3;
    primitive->v1 += 2;
    primitive->v3 -= 3;
    primitive->clut  = GetClut((mode << 5) | 0x10, 0x1E1);
    primitive->tpage = getTPage(TPAGE_DEPTH_4BIT, abr, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    texture_window    = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor   = (u8*)(texture_window + 1);
    texture_window->x = 0;
    texture_window->y = 0;
    texture_window->w = 256;
    texture_window->h = 256;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(TPAGE_DEPTH_4BIT, abr, FONT_TPAGE_X, FONT_TPAGE_Y), texture_window);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(DR_MODE));
    UI_WindowDrawFrame(x + 2, y + 2, width - 5, height - 5, mode);
}
#else
INCLUDE_ASM(func_801F4B0C);
#endif
