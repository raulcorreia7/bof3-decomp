#include "area188_13.h"

MATCH void func_801F2D18(void) {
    POLY_G4* prim;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, GetTPage(2, 2, 0x140, 0x140) & 0xFFFF, NULL);
    GFX_AddPrim(6U, 0xCU);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    prim->r0 = prim->r1 = 0;
    prim->g0 = prim->g1 = 0;
    prim->b0 = prim->b1 = 0;
    prim->r2 = prim->r3 = 0;
    prim->g2 = prim->g3 = 0;
    prim->b2 = prim->b3 = 0;
    setXY4(prim, 0, 0, 0x140, 0, 0, 0x140, 0x140, 0x140);
    SetSemiTrans((POLY_G4*)g_GfxPrimCursor, 1);
    GFX_AddPrim(2U, 0x24U);
    if (g_ScriptVars[0] == 1) {
        func_80196070();
    }
}
