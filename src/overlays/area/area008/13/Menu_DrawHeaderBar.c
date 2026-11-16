#include "area008_13.h"

#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawHeaderBar(s32 x, s32 y, s32 width, s32 height, u8 window_style) {
    RECT*     window;
    POLY_FT4* prim;
    u16       left;
    u16       top;
    s32       clut_x;
    s32       inner;
    s32       bottom_v;
    s32       bottom_y;
    s32       width1;
    u16       width1_u;
    s32       half;
    u16       half_u;
    s32       odd;
    u16       odd_u;

    window          = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor = (u8*)(window + 1);
    window->y       = 240;
    window->x       = 0;
    setWH(window, 16, 16);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), window);
    GFX_AddPrim(1u, sizeof(DR_MODE));

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    left     = x;
    top      = y;
    clut_x   = (window_style << 5) + 0x10;
    inner    = x + 2;
    prim->x0 = left;
    prim->y0 = top;
    prim->y1 = top;
    prim->x2 = left;
    prim->x1 = inner;
    prim->x3 = inner;
    setUV0(prim, 0u, 0u);
    prim->v1 = 0u;
    prim->u2 = 0u;
    setRGB0(prim, 172, 172, 172);
    bottom_v = height + 1;
    bottom_y = y + bottom_v;
    prim->y2 = bottom_y;
    prim->y3 = bottom_y;
    prim->u1 = 2u;
    prim->v2 = bottom_v;
    prim->u3 = 2u;
    prim->v3 = bottom_v;
    prim->y0 += 2;
    prim->v0 += 2;
    prim->y2 -= 3;
    prim->v2 -= 3;
    prim->clut  = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    width1      = width + 1;
    width1_u    = width1;
    prim->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1u, sizeof(POLY_FT4));

    half = ((s32)width1_u - 4) >> 1;
    prim = (POLY_FT4*)g_GfxPrimCursor;
    odd  = (width - 3) & 1;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    half_u = half;
    setXY4(prim, inner, top, half + inner, top, inner, bottom_y, half + inner, bottom_y);
    setUV4(prim, 0u, 0u, (u8)half_u, 0u, 0u, bottom_v, (u8)half_u, bottom_v);
    setRGB0(prim, 172, 172, 172);
    prim->clut  = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    odd_u       = odd;
    prim->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1u, sizeof(POLY_FT4));

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    prim->y0 = top;
    prim->x0 = x + half + 2;
    prim->x1 = (x + half) + (half + odd + 2);
    prim->y1 = top;
    prim->x2 = x + half + 2;
    prim->y2 = bottom_y;
    prim->x3 = (x + half) + (half + odd + 2);
    prim->y3 = bottom_y;
    setUV4(prim, 0u, 0u, (u8)(half_u + odd_u), 0u, 0u, bottom_v, (u8)(half_u + odd_u), bottom_v);
    setRGB0(prim, 172, 172, 172);
    prim->clut  = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    prim->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1u, sizeof(POLY_FT4));

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetSemiTrans(prim, 1);
    prim->y2 = bottom_y;
    prim->v2 = bottom_v;
    prim->x1 = x + width1;
    prim->y1 = top;
    prim->x3 = x + width1;
    prim->x0 = x + width1 - 2;
    prim->y0 = top;
    prim->x2 = x + width1 - 2;
    prim->y3 = bottom_y;
    setUV0(prim, 0u, 0u);
    prim->u1 = 2u;
    prim->v1 = 0u;
    prim->u2 = 0u;
    prim->u3 = 2u;
    prim->v3 = bottom_v;
    setRGB0(prim, 172, 172, 172);
    prim->y1 += 2;
    prim->y3 -= 3;
    prim->y2 -= 1;
    prim->v1 += 2;
    prim->v2 -= 1;
    prim->v3 -= 3;
    prim->clut  = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    prim->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1u, sizeof(POLY_FT4));

    window          = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor = (u8*)(window + 1);
    window->x       = 0;
    window->y       = 0;
    setWH(window, 256, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), window);
    GFX_AddPrim(1u, sizeof(DR_MODE));
    func_801AEBA0(inner, y + 2, width - 4, height - 4, 0);
}
#else
INCLUDE_ASM(Menu_DrawHeaderBar);
#endif
