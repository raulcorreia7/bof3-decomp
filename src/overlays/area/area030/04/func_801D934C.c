#include "area030_04.h"

MATCH void func_801D934C(u16 x, u16 y, u16 width, u16 height) {
    POLY_F4* poly;
    TILE*    tile;
    u32      palette_offset;
    u16      color;
    s8       style;
    u8       red;
    u8       green;
    u8       blue;

    style          = MEM(s8, &g_WindowStyle);
    palette_offset = (style << 6) | 0x20;
    color          = MEM(u16, AREA_PALETTE_ARENA_33A00 + 8u + palette_offset);
    red            = PSX_COLOR_R(color) << 3;
    green          = PSX_COLOR_G(color) << 3;
    blue           = PSX_COLOR_B(color) << 3;
    Fishing_SetDrawMode(6, 2);

    poly = GFX_CURSOR(POLY_F4);
    SetPolyF4(poly);
    poly->x0 = x + 2;
    poly->x1 = x + width - 2;
    poly->x2 = x;
    poly->x3 = x + width;
    poly->y0 = y;
    poly->y1 = y;
    poly->y2 = y + 2;
    poly->y3 = y + 2;
    poly->r0 = red;
    poly->g0 = green;
    poly->b0 = blue;
    SetSemiTrans(poly, 1);
    GFX_AddPrim(2, sizeof(POLY_F4));

    tile = GFX_CURSOR(TILE);
    SetTile(tile);
    tile->x0 = x;
    tile->y0 = y + 2;
    tile->w  = width;
    tile->h  = height - 4;
    tile->r0 = red;
    tile->g0 = green;
    tile->b0 = blue;
    SetSemiTrans(tile, 1);
    GFX_AddPrim(2, sizeof(TILE));

    poly = GFX_CURSOR(POLY_F4);
    SetPolyF4(poly);
    poly->x0 = x;
    poly->x1 = x + width;
    poly->x2 = x + 2;
    poly->x3 = x + width - 2;
    poly->y0 = y + height - 2;
    poly->y1 = y + height - 2;
    poly->y2 = y + height;
    poly->y3 = y + height;
    poly->r0 = red;
    poly->g0 = green;
    poly->b0 = blue;
    SetSemiTrans(poly, 1);
    GFX_AddPrim(2, sizeof(POLY_F4));
}
