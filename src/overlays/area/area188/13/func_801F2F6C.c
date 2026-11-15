#include "area188_13.h"

MATCH void func_801F2F6C(void) {
    POLY_G4* prim;
    u8       elapsed;
    u8       index;

    elapsed       = g_Task->timer;
    g_Task->timer = elapsed + 1;
    if (elapsed >= 16) {
        D_801F68A0    = D_801F4DF0[D_801F689C];
        g_Task->timer = 0;

        index      = D_801F689C;
        D_801F689C = index + 1;
        if (index != 0) {
            D_801F689C = 0;
        }
    }

    GFX_AddDitheredDrawMode(6U, GetTPage(2, 2, 320, 320) & HALF_MASK);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    setRGB0(prim, prim->r1 = D_801F68A0, prim->g1 = 0, prim->b1 = 0);
    setRGB2(prim, prim->r3 = D_801F68A0, prim->g3 = 0, prim->b3 = 0);
    setXY4(prim, 0, 0, SCREEN_WIDTH, 0, 0, 320, SCREEN_WIDTH, 320);
    SetSemiTrans((POLY_G4*)g_GfxPrimCursor, 1);
    GFX_AddPrim(2U, sizeof(POLY_G4));
}
