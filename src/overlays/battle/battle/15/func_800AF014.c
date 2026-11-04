#include "battle_15.h"

MATCH void func_800AF014(void) {
    POLY_G4* prim;

    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    if (D_801EB4E0->word_08.byte.unk_08 & 1) {
        setXY4(prim, 0, 0, 319, 0, 0, 239, 319, 239);
    } else {
        prim->x2 = 319;
        prim->x0 = 319;
        prim->y1 = 0;
        prim->y0 = 0;
        prim->x3 = 0;
        prim->x1 = 0;
        prim->y3 = 239;
        prim->y2 = 239;
    }
    prim->r3 = 0x20;
    prim->r0 = 0x20;
    prim->g3 = 0x20;
    prim->g0 = 0x20;
    prim->b3 = 0x20;
    prim->b0 = 0x20;
    prim->r2 = 0x80;
    prim->r1 = 0x80;
    prim->g2 = 0x80;
    prim->g1 = 0x80;
    prim->b2 = 0x80;
    prim->b1 = 0x80;
    GFX_AddPrim(7U, 0x24U);
}
