#include "area144_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3124(u8* data) {
    POLY_G3* poly;
    u8       half_color;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(0, 1, 0x380, 0x100), 0);
    GFX_AddPrim(data[0x1B], sizeof(DR_MODE));

    poly = (POLY_G3*)g_GfxPrimCursor;
    SetPolyG3(poly);
    SetSemiTrans(poly, 1);
    *(DVECTOR*)((u8*)poly + 0x08) = **(DVECTOR**)(data + 0x10);
    *(DVECTOR*)((u8*)poly + 0x10) = **(DVECTOR**)(data + 0x00);
    *(DVECTOR*)((u8*)poly + 0x18) = **(DVECTOR**)(data + 0x04);
    poly->r0                      = data[0x14];
    poly->g0                      = data[0x15];
    poly->b0                      = data[0x16];
    half_color                    = data[0x14] >> 1;
    poly->r2                      = half_color;
    poly->r1                      = half_color;
    half_color                    = data[0x15] >> 1;
    poly->g2                      = half_color;
    poly->g1                      = half_color;
    half_color                    = data[0x16] >> 1;
    poly->b2                      = half_color;
    poly->b1                      = half_color;
    GFX_AddPrim(data[0x1B], sizeof(POLY_G3));

    poly = (POLY_G3*)g_GfxPrimCursor;
    SetPolyG3(poly);
    SetSemiTrans(poly, 1);
    *(DVECTOR*)((u8*)poly + 0x08) = **(DVECTOR**)(data + 0x10);
    *(DVECTOR*)((u8*)poly + 0x10) = **(DVECTOR**)(data + 0x04);
    *(DVECTOR*)((u8*)poly + 0x18) = **(DVECTOR**)(data + 0x0C);
    poly->r0                      = data[0x14];
    poly->g0                      = data[0x15];
    poly->b0                      = data[0x16];
    half_color                    = data[0x14] >> 1;
    poly->r2                      = half_color;
    poly->r1                      = half_color;
    half_color                    = data[0x15] >> 1;
    poly->g2                      = half_color;
    poly->g1                      = half_color;
    half_color                    = data[0x16] >> 1;
    poly->b2                      = half_color;
    poly->b1                      = half_color;
    GFX_AddPrim(data[0x1B], sizeof(POLY_G3));

    poly = (POLY_G3*)g_GfxPrimCursor;
    SetPolyG3(poly);
    SetSemiTrans(poly, 1);
    *(DVECTOR*)((u8*)poly + 0x08) = **(DVECTOR**)(data + 0x10);
    *(DVECTOR*)((u8*)poly + 0x10) = **(DVECTOR**)(data + 0x0C);
    *(DVECTOR*)((u8*)poly + 0x18) = **(DVECTOR**)(data + 0x08);
    poly->r0                      = data[0x14];
    poly->g0                      = data[0x15];
    poly->b0                      = data[0x16];
    half_color                    = data[0x14] >> 1;
    poly->r2                      = half_color;
    poly->r1                      = half_color;
    half_color                    = data[0x15] >> 1;
    poly->g2                      = half_color;
    poly->g1                      = half_color;
    half_color                    = data[0x16] >> 1;
    poly->b2                      = half_color;
    poly->b1                      = half_color;
    GFX_AddPrim(data[0x1B], sizeof(POLY_G3));

    poly = (POLY_G3*)g_GfxPrimCursor;
    SetPolyG3(poly);
    SetSemiTrans(poly, 1);
    *(DVECTOR*)((u8*)poly + 0x08) = **(DVECTOR**)(data + 0x0C);
    *(DVECTOR*)((u8*)poly + 0x10) = **(DVECTOR**)(data + 0x08);
    *(DVECTOR*)((u8*)poly + 0x18) = **(DVECTOR**)(data + 0x00);
    poly->r0                      = data[0x14];
    poly->g0                      = data[0x15];
    poly->b0                      = data[0x16];
    half_color                    = data[0x14] >> 1;
    poly->r2                      = half_color;
    poly->r1                      = half_color;
    half_color                    = data[0x15] >> 1;
    poly->g2                      = half_color;
    poly->g1                      = half_color;
    half_color                    = data[0x16] >> 1;
    poly->b2                      = half_color;
    poly->b1                      = half_color;
    GFX_AddPrim(data[0x1B], sizeof(POLY_G3));
}
#else
INCLUDE_ASM(func_801F3124);
#endif
