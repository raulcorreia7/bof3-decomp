#include "area172_13.h"

MATCH void func_801F4F70(s32 x, s32 y) {
    POLY_G4* poly;

    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, FONT_TPAGE_X, FONT_TPAGE_Y));
    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    poly->x0 = x - 64;
    poly->y2 = poly->y3 = y + 48;
    poly->x1 = poly->x3 = SCREEN_WIDTH;
    poly->x2            = x;
    poly->y0 = poly->y1 = y;
    setRGB0(poly, 0, 0, 0);
    setRGB1(poly, 0xFF, 0xFF, 0xFF);
    setRGB2(poly, 0x40, 0x40, 0x40);
    setRGB3(poly, 0xFF, 0xFF, 0xFF);
    SetSemiTrans(poly, 1);
    SetShadeTex(poly, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
}
