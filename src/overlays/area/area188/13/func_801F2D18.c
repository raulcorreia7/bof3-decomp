#include "area188_13.h"

MATCH void func_801F2D18(void) {
    POLY_G4* prim;

    GFX_AddDitheredDrawMode(6U, GetTPage(2, 2, 0x140, 0x140) & 0xFFFF);
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    setRGB0(prim, prim->r1 = 0, prim->g1 = 0, prim->b1 = 0);
    setRGB2(prim, prim->r3 = 0, prim->g3 = 0, prim->b3 = 0);
    setXY4(prim, 0, 0, 0x140, 0, 0, 0x140, 0x140, 0x140);
    SetSemiTrans((POLY_G4*)g_GfxPrimCursor, 1);
    GFX_AddPrim(2U, sizeof(POLY_G4));
    if (g_ScriptVars[0] == 1) {
        func_80196070();
    }
}
