#include "battle_03.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801D9E9C(s32 x, s32 y, s32 width, s32 second_width, u8 second) {
    POLY_FT4* poly;
    u8        u;
    u8        v;
    u8        c;
    s32       flag;

    poly = (POLY_FT4*)g_GfxPrimCursor;
    flag = second;
    SetPolyFT4(poly);
    poly->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    FAKE_BARRIER(); /* FAKE: retail stores tpage before the clut select constant loads. */
    poly->clut = GetClut(!flag ? 0xE0 : 0xB0, STAGE_PALETTE_Y);
    FAKE_BARRIER(); /* FAKE: retail stores clut before the 0x80 colour constant load. */
    u = 0x80;
    setRGB0(poly, u, u, u);
    setXYWH(poly, x, y, width & BYTE_MASK, 7);
    if (flag == 0) {
        u = 0x90;
        v = 0x97;
    } else {
        v = 0x87;
    }
    /* The corner UVs are literals in retail (0x97/0x87 and 0xDF), not u + 7, so setUVWH differs. */
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
    FAKE_BARRIER(); /* FAKE: retail stores tpage in the GetClut delay slot before the clut store. */
    poly->clut = GetClut(0xB0, STAGE_PALETTE_Y);
    setRGB0(poly, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    /* The corner stores interleave with the colour and UV constants, so setXYWH differs. */
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
    /* setUVWH here would drop the shared 0xD8/0xDF temp, so the bytes differ. */
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
