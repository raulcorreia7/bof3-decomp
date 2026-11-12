#include "battle_15.h"

MATCH void func_800AF014(void) {
    POLY_G4* prim;

    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    if (g_BattleEffectBattler->facing & 0x1) {
        setXY4(prim, 0, 0, 319, 0, 0, 239, 319, 239);
    } else {
        prim->x2 = 319;
        prim->y1 = 0;
        setXY0(prim, 319, 0);
        prim->x3 = 0;
        prim->x1 = 0;
        prim->y3 = 239;
        prim->y2 = 239;
    }
    prim->r3 = 32;
    prim->r0 = 32;
    prim->g3 = 32;
    prim->g0 = 32;
    prim->b3 = 32;
    prim->b0 = 32;
    prim->r2 = 128;
    prim->r1 = 128;
    prim->g2 = 128;
    prim->g1 = 128;
    prim->b2 = 128;
    prim->b1 = 128;
    GFX_AddPrim(7U, sizeof(POLY_G4));
}
