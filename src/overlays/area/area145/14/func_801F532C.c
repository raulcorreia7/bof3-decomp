#include "area145_14.h"

MATCH void func_801F532C(void) {
    POLY_G4* prim;
    s32      tpage;

    if (g_AreaSceneMode == 0) {
        return;
    }
    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_HALF, 320, 256);
    GFX_ADD_DITHERED_DRAW_MODE(GFX_LAYER_BACKDROP, tpage);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    SetSemiTrans(prim, 0);
    prim->x0 = 0;
    prim->y0 = 0;
    prim->x1 = SCREEN_WIDTH;
    prim->y1 = 0;
    prim->x2 = 0;
    prim->y2 = SCREEN_HEIGHT;
    prim->x3 = SCREEN_WIDTH;
    prim->y3 = SCREEN_HEIGHT;
    prim->r0 = prim->r1 = 0;
    prim->g0 = prim->g1 = 0xC8;
    prim->b0 = prim->b1 = 0xFF;
    prim->r2 = prim->r3 = 0;
    prim->g2 = prim->g3 = 0;
    prim->b2 = prim->b3 = 0x20;
    GFX_AddPrim(GFX_LAYER_BACKDROP, sizeof(POLY_G4));
}
