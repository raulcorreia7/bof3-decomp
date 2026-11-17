#include "battle_03.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D9E9C(s32 x, s32 y, s32 width, s32 second_width, u8 second) {
    POLY_FT4* poly;
    u8        u;
    u8        v;
    u8        c;

    poly = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(poly);
    poly->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    poly->clut  = GetClut(!second ? 0xE0 : 0xB0, STAGE_PALETTE_Y);
    u           = 0x80;
    setRGB0(poly, u, u, u);
    setXY4(poly, x, y, x + (width & BYTE_MASK), y, x, y + 7, x + (width & BYTE_MASK), y + 7);
    if (!second) {
        u = 0x90;
        v = 0x97;
    } else {
        v = 0x87;
    }
    c        = 0xD8;
    poly->v0 = c;
    poly->v1 = c;
    poly->u0 = u;
    poly->u1 = v;
    poly->u2 = u;
    c        = 0xDF;
    poly->v2 = c;
    poly->u3 = v;
    poly->v3 = c;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));

    poly = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(poly);
    poly->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    poly->clut  = GetClut(0xB0, STAGE_PALETTE_Y);
    setRGB0(poly, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    poly->x0 = x + (width & BYTE_MASK);
    poly->x2 = x + (width & BYTE_MASK);
    poly->y2 = y + 7;
    poly->y3 = y + 7;
    poly->x1 = x + (width & BYTE_MASK) + (second_width & BYTE_MASK);
    poly->x3 = x + (width & BYTE_MASK) + (second_width & BYTE_MASK);
    c        = 0xD8;
    poly->v0 = c;
    poly->v1 = c;
    poly->y0 = y;
    poly->y1 = y;
    poly->u0 = 0x98;
    poly->u1 = 0x9F;
    poly->u2 = 0x98;
    c        = 0xDF;
    poly->v2 = c;
    poly->u3 = 0x9F;
    poly->v3 = c;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(func_801D9E9C);
#endif
