#include "area121_14.h"

MATCH void func_801F6390(void) {
    s32      tpage;
    POLY_G4* poly;

    if (g_AreaSceneMode == 0) {
        return;
    }
    if (g_AreaSceneMode >= 3) {
        return;
    }
    if ((g_AreaDrawFlags & 4) == 0) {
        return;
    }
    if (GetGraphType() == 1) {
        tpage = 0x225;
    } else if (GetGraphType() == 2) {
        tpage = 0x225;
    } else {
        tpage = 0x95;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(7, sizeof(DR_MODE));
    poly = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(poly);
    SetSemiTrans(poly, 0);
    setXY4(poly, 0, 0, 320, 0, 0, D_801F68B8[g_AreaSceneMode], 320, D_801F68B8[g_AreaSceneMode]);
    poly->r1 = 0x48;
    poly->r0 = 0x48;
    poly->g1 = 0x38;
    poly->g0 = 0x38;
    poly->b1 = 0xFF;
    poly->b0 = 0xFF;
    poly->b3 = 0xFF;
    poly->b2 = 0xFF;
    poly->g3 = 0xFF;
    poly->g2 = 0xFF;
    poly->r3 = 0xFF;
    poly->r2 = 0xFF;
    GFX_AddPrim(7, sizeof(POLY_G4));
}
