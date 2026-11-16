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
    tpage = getTPage(1, 0, 320, 256);
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, tpage, 0);
    GFX_AddPrim(7, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 0);
    prim->x0 = 0;
    prim->y0 = 0;
    prim->x1 = SCREEN_WIDTH;
    prim->y1 = 0;
    prim->x2 = 0;
    prim->y2 = 200;
    prim->x3 = SCREEN_WIDTH;
    prim->y3 = 200;
    prim->r0 = prim->r1 = 0;
    prim->g0 = prim->g1 = 200;
    prim->b0 = prim->b1 = 255;
    prim->r2 = prim->r3 = 0;
    prim->g2 = prim->g3 = 0;
    prim->b2 = prim->b3 = 32;
    GFX_AddPrim(7, sizeof(POLY_G4));
}
