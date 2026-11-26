#include "area060_13.h"

#ifdef NON_MATCHING
/* The map reveal: the scrolling backdrop, the shade band and the cell rows around the target. */
NON_MATCHING void func_801F2C90(void) {
    POLY_FT4* poly;
    POLY_G4*  quads;
    RECT*     rect;
    u16*      x_stops;
    u16*      x_next;
    u8        phase;
    s32       i;
    s32       band_offset;
    s32       x;
    s32       col;
    s32       high;
    s32       low;
    s32       fill;
    s32       width;
    s32       y;

    rect = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor += sizeof(RECT);
    rect->x = 0xE0;
    rect->y = 0;
    rect->w = rect->h = 0x20;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x225 : 0x95, rect);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(DR_MODE));

    poly = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(poly);
    SetShadeTex(poly, 1);
    poly->x0    = 0;
    poly->y0    = 0x38;
    poly->x1    = 0x140;
    poly->y1    = 0x38;
    poly->x2    = 0;
    poly->y2    = 0x58;
    poly->x3    = 0x140;
    poly->y3    = 0x58;
    poly->u0    = 0;
    poly->v0    = 0;
    poly->u1    = 0xFF;
    poly->v1    = 0;
    poly->u2    = 0;
    poly->v2    = 0x40;
    poly->u3    = 0xFF;
    poly->v3    = 0x40;
    poly->tpage = (GetGraphType() == 1 || GetGraphType() == 2) ? 0x225 : 0x95;
    poly->clut  = 0x7900;
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_FT4));

    rect = (RECT*)g_GfxPrimCursor;
    g_GfxPrimCursor += sizeof(RECT);
    rect->x = 0;
    rect->y = 0;
    rect->w = rect->h = 0x100;
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x225 : 0x95, rect);
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(DR_MODE));

    for (i = 0; i < 3; i++) {
        poly = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(poly);
        SetShadeTex(poly, 1);
        phase       = g_FrameCount >> 3;
        x           = phase + (i - 1) * 0x100;
        poly->y0    = 0;
        poly->y1    = 0;
        poly->y2    = 0x40;
        poly->y3    = 0x40;
        poly->u0    = 0;
        poly->v0    = 0;
        poly->u1    = 0xFF;
        poly->v1    = 0;
        poly->u2    = 0;
        poly->v2    = 0x40;
        poly->u3    = 0xFF;
        poly->v3    = 0x40;
        poly->x0    = x;
        poly->x1    = x + 0x100;
        poly->x2    = x;
        poly->x3    = x + 0x100;
        poly->tpage = (GetGraphType() == 1 || GetGraphType() == 2) ? 0x229 : 0x99;
        poly->clut  = 0x7980;
        func_801F3288(sizeof(POLY_FT4));
    }

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x2A5 : 0xB5, 0);
    func_801F3288(sizeof(DR_MODE));

    /* The step table's payload: the band's x stops at +8 and its top and bottom rows at +0x14. */
    x_stops     = (u16*)(D_801F3330 + 8);
    band_offset = -((g_AreaScrollTargetX - 0x2D0000) >> 15);
    x_next      = x_stops + 1;
    for (i = 0; i < 4; i++) {
        quads = (POLY_G4*)g_GfxPrimCursor;
        SetPolyG4(quads);
        SetSemiTrans(quads, 1);
        quads->x0 = x_stops[i];
        quads->y0 = 0x40;
        quads->x1 = x_next[i];
        quads->y1 = 0x40;
        quads->x2 = x_stops[i];
        quads->y2 = D_801F3330[0x14 + i] + band_offset;
        quads->x3 = x_next[i];
        quads->y3 = D_801F3330[0x15 + i] + band_offset;
        quads->r0 = 0xFF;
        quads->g0 = 0xFF;
        quads->b0 = 0xFF;
        quads->r1 = 0xFF;
        quads->g1 = 0xFF;
        quads->b1 = 0xFF;
        quads->r2 = 0;
        quads->g2 = 0;
        quads->b2 = 0;
        quads->r3 = 0;
        quads->g3 = 0;
        quads->b3 = 0;
        func_801F3288(sizeof(POLY_G4));
    }

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x2A5 : 0xB5, 0);
    func_801F3288(sizeof(DR_MODE));

    fill = (0x20 << 24) | (0x20 << 16) | (0x20 << 8) | 0x20;
    for (i = 0; i < 10; i++) {
        y    = g_AreaScrollTargetCoordY.part.integer;
        high = ((i + 1) / 2) + 0x20;
        low  = (i / 2) + 0x20;
        for (col = 0x2D; col < 0x31; col++) {
            width                                                                           = ((AreaMapBundle*)MAP_BUNDLE_BASE)->width;
            (((u32*)(MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE)) + (y + 3) * width)[col]       = fill;
            (((u32*)(MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE)) + (y + (i + 4)) * width)[col] = (high << 24) | (high << 16) | (low << 8) | low;
        }
    }
    for (i = 0; i < 14; i++) {
        y    = g_AreaScrollTargetCoordY.part.integer;
        high = (i / 2) + 0x20;
        low  = ((i + 1) / 2) + 0x20;
        for (col = 0x2D; col < 0x31; col++) {
            width                                                                           = ((AreaMapBundle*)MAP_BUNDLE_BASE)->width;
            (((u32*)(MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE)) + (y - 3) * width)[col]       = fill;
            (((u32*)(MAP_BUNDLE_BASE + AREA_MAP_BUNDLE_SIZE)) + (y - (i + 4)) * width)[col] = (high << 24) | (high << 16) | (low << 8) | low;
        }
    }
}
#else
INCLUDE_ASM(func_801F2C90);
#endif
