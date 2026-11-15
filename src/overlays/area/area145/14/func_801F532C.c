#include "area145_14.h"

MATCH void func_801F532C(void) {
    POLY_G4* prim;
    s32      tpage;

    if (g_AreaSceneMode == 0) {
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
    GFX_AddPrim(7, sizeof(POLY_G4));
}
