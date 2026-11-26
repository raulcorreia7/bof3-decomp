#include "area118_13.h"

MATCH void func_801F2EA0(void) {
    POLY_G4* prim;

    if (SELF(Actor)->timer++ >= 16) {
        D_801F59EC         = D_801F511C[D_801F59E8];
        SELF(Actor)->timer = 0;
        if (D_801F59E8++ >= 7) {
            D_801F59E8 = 0;
        }
    }
    GFX_AddDitheredDrawMode(GFX_LAYER_FIELD_SCENE, GetTPage(TPAGE_DEPTH_15BIT, TPAGE_ABR_SUB, 320, 320) & HALF_MASK);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    setRGB0(prim, prim->r1 = D_801F59EC, prim->g1 = 0, prim->b1 = D_801F59EC);
    setRGB2(prim, prim->r3 = D_801F59EC, prim->g3 = 0, prim->b3 = D_801F59EC);
    setXY4(prim, 0, 0, SCREEN_WIDTH, 0, 0, 320, SCREEN_WIDTH, 320);
    SetSemiTrans((POLY_G4*)g_GfxPrimCursor, 1);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(POLY_G4));
}
