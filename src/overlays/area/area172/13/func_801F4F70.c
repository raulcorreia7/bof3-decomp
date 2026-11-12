#include "area172_13.h"

MATCH void func_801F4F70(s32 x, s32 y) {
    POLY_G4* poly;

    GFX_AddDitheredDrawMode(1, GetTPage(0, 2, 960, 0));
    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    poly->x0 = x - 0x40;
    poly->y2 = poly->y3 = y + 0x30;
    poly->x1 = poly->x3 = SCREEN_WIDTH;
    poly->x2            = x;
    poly->y0 = poly->y1 = y;
    setRGB0(poly, 0, 0, 0);
    setRGB1(poly, 0xFF, 0xFF, 0xFF);
    setRGB2(poly, 0x40, 0x40, 0x40);
    setRGB3(poly, 0xFF, 0xFF, 0xFF);
    SetSemiTrans(poly, 1);
    SetShadeTex(poly, 0);
    GFX_AddPrim(1, sizeof(POLY_G4));
}
