#include "batl_ovr_00.h"

MATCH void func_801EF47C(s32 x) {
    TILE*    tile;
    POLY_G4* poly;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 0, 0x3C0, 0), 0);
    GFX_AddPrim(1, sizeof(DR_MODE));

    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setXY0(tile, x + 32, 48);
    setWH(tile, 168, 24);
    setRGB0(tile, 0, 0, 0);
    GFX_AddPrim(1, sizeof(TILE));

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 2, 0x3C0, 0), 0);
    GFX_AddPrim(1, sizeof(DR_MODE));

    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    setRGB0(poly, 0, 0, 0);
    setRGB1(poly, 0xFF, 0xFF, 0xFF);
    setRGB2(poly, 0, 0, 0);
    setRGB3(poly, 0xFF, 0xFF, 0xFF);
    setXY4(poly, x, 48, x + 34, 48, x, 72, x + 34, 72);
    SetSemiTrans(poly, 1);
    GFX_AddPrim(1, sizeof(POLY_G4));
}
