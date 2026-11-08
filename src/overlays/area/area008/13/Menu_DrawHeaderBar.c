#include "area008_13.h"

/* NOTE: not byte-matching (293/339 insn, 1352 bytes — 1 insn short; first diff
 * +0x00D0, insn 52). The re-lift reproduces the original's 120-byte frame, the
 * a0-a3 spills to 24/32/40/48(sp), and the block-3 x1/x3 association
 * `base + (half_width + odd_width + 2)`. Residual: a register domino —
 * bottom_v/bottom_y/half_width land in s1/s2/s3 instead of s2/s3/s1, one
 * `move v0,s1` replaces the hoisted `sll v0,s2,5` clut_x setup, and the
 * reload of width_plus_1 loses the redundant original `andi v0,s1,0xffff`.
 */
#ifdef NON_MATCHING
NON_MATCHING void Menu_DrawHeaderBar(s16 x, s16 y, s32 width, s32 height, u8 window_style) {
    RECT*     texture_window;
    POLY_FT4* primitive;
    s16       bottom_y;
    u8        bottom_v;
    s32       clut_x;
    s16       odd_h;
    s32       width_plus_1;
    s32       odd_width;

    u16 x;
    s32 r_s1;
    u16 r_s4;
    s32 r_s8;

    texture_window    = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor   = (u8*)(texture_window + 1);
    texture_window->y = 240;
    texture_window->x = 0;
    setWH(texture_window, 16, 16);

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), texture_window);
    GFX_AddPrim(1u, sizeof(DR_MODE));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    x      = (u16)x;
    r_s8   = (s16)(x + 2);
    clut_x = ((s32)window_style << 5) + 0x10;
    setXY0(primitive, (s16)x, (s16)(u16)y);
    primitive->y1 = (s16)(u16)y;
    primitive->x2 = (s16)x;
    primitive->x1 = (s16)r_s8;
    primitive->x3 = (s16)r_s8;
    setUV0(primitive, 0u, 0u);
    primitive->v1 = 0u;
    primitive->u2 = 0u;
    setRGB0(primitive, 0xACu, 0xACu, 0xACu);
    bottom_v      = (u8)(height + 1);
    bottom_y      = (s16)((s32)(u16)y + bottom_v);
    primitive->y2 = bottom_y;
    primitive->y3 = bottom_y;
    primitive->u1 = 2u;
    primitive->v2 = bottom_v;
    primitive->u3 = 2u;
    primitive->v3 = bottom_v;
    primitive->y0 += 2;
    primitive->y2 -= 3;
    primitive->v0 += 2;
    primitive->v2 -= 3;
    primitive->clut = GetClut(clut_x, STAGE_PALETTE_Y + 1);
    width_plus_1    = (s32)(width + 1);

    primitive->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1u, sizeof(POLY_FT4));

    /* FAKE: pin signed shift matches original sra computation. */
    r_s1 = (s32)(u16)width_plus_1;
    r_s1 = ((s32)(u16)r_s1 - 4) >> 1;
    r_s4 = r_s1;

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    odd_width = (width - 3) & 1;
    odd_h     = (s16)odd_width;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    setXY4(primitive, (s16)r_s8, (s16)(u16)y, (s16)(r_s1 + r_s8), (s16)(u16)y, (s16)r_s8, bottom_y, (s16)(r_s1 + r_s8),
           bottom_y);
    setUV4(primitive, 0u, 0u, (u8)r_s4, 0u, 0u, bottom_v, (u8)r_s4, bottom_v);
    setRGB0(primitive, 0xACu, 0xACu, 0xACu);
    primitive->clut = GetClut(clut_x, STAGE_PALETTE_Y + 1);

    primitive->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1u, sizeof(POLY_FT4));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    primitive->y0 = (s16)(u16)y;
    primitive->x0 = (s16)((s32)x + r_s1 + 2);
    primitive->x1 = (s16)(((s32)x + r_s1) + (r_s1 + odd_width + 2));
    primitive->y1 = (s16)(u16)y;
    primitive->x2 = (s16)((s32)x + r_s1 + 2);
    primitive->y2 = bottom_y;
    primitive->x3 = (s16)(((s32)x + r_s1) + (r_s1 + odd_width + 2));
    primitive->y3 = bottom_y;
    setUV4(primitive, 0u, 0u, (u8)(r_s4 + odd_h), 0u, 0u, bottom_v, (u8)(r_s4 + odd_h), bottom_v);
    setRGB0(primitive, 0xACu, 0xACu, 0xACu);
    primitive->clut = GetClut(clut_x, STAGE_PALETTE_Y + 1);

    primitive->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1u, sizeof(POLY_FT4));

    primitive = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(primitive);
    SetSemiTrans(primitive, 1);
    primitive->y2 = bottom_y;
    primitive->v2 = bottom_v;
    primitive->x1 = (s16)((s32)x + width_plus_1);
    primitive->y1 = (s16)(u16)y;
    primitive->x3 = (s16)((s32)x + width_plus_1);
    setXY0(primitive, (s16)((s32)x + width_plus_1 - 2), (s16)(u16)y);
    primitive->x2 = (s16)((s32)x + width_plus_1 - 2);
    primitive->y3 = bottom_y;
    setUV0(primitive, 0u, 0u);
    primitive->u1 = 2u;
    primitive->v1 = 0u;
    primitive->u2 = 0u;
    primitive->u3 = 2u;
    primitive->v3 = bottom_v;
    setRGB0(primitive, 0xACu, 0xACu, 0xACu);
    primitive->y1 += 2;
    primitive->y3 -= 3;
    primitive->y2 -= 1;
    primitive->v1 += 2;
    primitive->v2 -= 1;
    primitive->v3 -= 3;
    primitive->clut = GetClut(clut_x, STAGE_PALETTE_Y + 1);

    primitive->tpage = getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y);
    GFX_AddPrim(1u, sizeof(POLY_FT4));

    texture_window    = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor   = (u8*)(texture_window + 1);
    texture_window->x = 0;
    texture_window->y = 0;
    setWH(texture_window, 256, 256);

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, getTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), texture_window);
    GFX_AddPrim(1u, sizeof(DR_MODE));
    func_801AEBA0((s16)r_s8, (s16)((s32)(u16)y + 2), (s16)(width - 4), (s16)(height - 4), 0);
}
#else
INCLUDE_ASM(Menu_DrawHeaderBar);
#endif
