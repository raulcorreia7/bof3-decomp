#include "area144_13.h"

MATCH void func_801F3124(u8* data) {
    POLY_G3* poly;
    u8       half_color;

    GFX_ADD_DITHERED_DRAW_MODE(data[0x1B], GetTPage(0, 1, 0x380, 0x100));

    poly = (POLY_G3*)g_GfxPrimCursor;
    SetPolyG3(poly);
    SetSemiTrans(poly, 1);
    *(DVECTOR*)&poly->x0 = **(DVECTOR**)(data + 0x10);
    *(DVECTOR*)&poly->x1 = **(DVECTOR**)(data + 0x00);
    *(DVECTOR*)&poly->x2 = **(DVECTOR**)(data + 0x04);
    poly->r0             = data[0x14];
    poly->g0             = data[0x15];
    poly->b0             = data[0x16];
    half_color           = data[0x14] >> 1;
    poly->r2             = half_color;
    poly->r1             = half_color;
    half_color           = data[0x15] >> 1;
    poly->g2             = half_color;
    poly->g1             = half_color;
    half_color           = data[0x16] >> 1;
    poly->b2             = half_color;
    poly->b1             = half_color;
    GFX_AddPrim(data[0x1B], sizeof(POLY_G3));

    poly = (POLY_G3*)g_GfxPrimCursor;
    SetPolyG3(poly);
    SetSemiTrans(poly, 1);
    *(DVECTOR*)&poly->x0 = **(DVECTOR**)(data + 0x10);
    *(DVECTOR*)&poly->x1 = **(DVECTOR**)(data + 0x04);
    *(DVECTOR*)&poly->x2 = **(DVECTOR**)(data + 0x0C);
    poly->r0             = data[0x14];
    poly->g0             = data[0x15];
    poly->b0             = data[0x16];
    half_color           = data[0x14] >> 1;
    poly->r2             = half_color;
    poly->r1             = half_color;
    half_color           = data[0x15] >> 1;
    poly->g2             = half_color;
    poly->g1             = half_color;
    half_color           = data[0x16] >> 1;
    poly->b2             = half_color;
    poly->b1             = half_color;
    GFX_AddPrim(data[0x1B], sizeof(POLY_G3));

    poly = (POLY_G3*)g_GfxPrimCursor;
    SetPolyG3(poly);
    SetSemiTrans(poly, 1);
    *(DVECTOR*)&poly->x0 = **(DVECTOR**)(data + 0x10);
    *(DVECTOR*)&poly->x1 = **(DVECTOR**)(data + 0x0C);
    *(DVECTOR*)&poly->x2 = **(DVECTOR**)(data + 0x08);
    poly->r0             = data[0x14];
    poly->g0             = data[0x15];
    poly->b0             = data[0x16];
    half_color           = data[0x14] >> 1;
    poly->r2             = half_color;
    poly->r1             = half_color;
    half_color           = data[0x15] >> 1;
    poly->g2             = half_color;
    poly->g1             = half_color;
    half_color           = data[0x16] >> 1;
    poly->b2             = half_color;
    poly->b1             = half_color;
    GFX_AddPrim(data[0x1B], sizeof(POLY_G3));

    poly = (POLY_G3*)g_GfxPrimCursor;
    SetPolyG3(poly);
    SetSemiTrans(poly, 1);
    *(DVECTOR*)&poly->x0 = **(DVECTOR**)(data + 0x10);
    *(DVECTOR*)&poly->x1 = **(DVECTOR**)(data + 0x08);
    *(DVECTOR*)&poly->x2 = **(DVECTOR**)(data + 0x00);
    poly->r0             = data[0x14];
    poly->g0             = data[0x15];
    poly->b0             = data[0x16];
    half_color           = data[0x14] >> 1;
    poly->r2             = half_color;
    poly->r1             = half_color;
    half_color           = data[0x15] >> 1;
    poly->g2             = half_color;
    poly->g1             = half_color;
    half_color           = data[0x16] >> 1;
    poly->b2             = half_color;
    poly->b1             = half_color;
    GFX_AddPrim(data[0x1B], sizeof(POLY_G3));
}
