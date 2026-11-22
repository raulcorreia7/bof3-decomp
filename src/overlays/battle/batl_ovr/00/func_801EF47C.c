#include "batl_ovr_00.h"

MATCH void func_801EF47C(s32 x) {
    TILE*    tile;
    POLY_G4* poly;

    GFX_ADD_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));

    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setXY0(tile, x + 32, 48);
    setWH(tile, 168, 24);
    setRGB0(tile, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(TILE));

    GFX_ADD_DRAW_MODE(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, FONT_TPAGE_X, FONT_TPAGE_Y));

    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    setRGB0(poly, 0, 0, 0);
    setRGB1(poly, 0xFF, 0xFF, 0xFF);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0xFF, 0xFF, 0xFF);
    setXY4(poly, x, 48, x + 34, 48, x, 72, x + 34, 72);
    SetSemiTrans(poly, 1);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_G4));
}
