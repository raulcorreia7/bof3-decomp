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
    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }
    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BACKDROP, tpage);
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
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_G4));
}
