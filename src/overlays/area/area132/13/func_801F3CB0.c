#include "area132_13.h"

/* Draws the area's full-screen blue-green tint quad while the scene draws cell layers. */
/* func_801F3CB0 */
MATCH void func_801F3CB0(void) {
    POLY_G4* prim;
    s32      tpage;

    if (g_AreaSceneMode == 0) {
        Actor_Clear();
    }
    if ((g_AreaDrawFlags & AREA_DRAW_CELL_LAYERS) == 0) {
        return;
    }
    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BACKDROP, tpage);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 0);
    setXY4(prim, 0, 0, SCREEN_WIDTH, 0, 0, 200, SCREEN_WIDTH, 200);
    prim->r0 = prim->r1 = 0;
    prim->g0 = prim->g1 = 200;
    prim->b0 = prim->b1 = 255;
    prim->r2 = prim->r3 = 0;
    prim->g2 = prim->g3 = 0;
    prim->b2 = prim->b3 = 32;
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_G4));
}
