#include "area082_13.h"

MATCH void func_801F5428(s32 arg0) {
    POLY_G4* prim;
    s32      mode;
    u32      c = arg0;
    u8       r0, g0, b0, r1, g1, b1;

    if (GetGraphType() == 1) {
        mode = 0x225;
    } else if (GetGraphType() == 2) {
        mode = 0x225;
    } else {
        mode = 0x95;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 1, mode, 0);
    GFX_AddPrim(6, sizeof(DR_MODE));
    prim = (POLY_G4*)g_GfxPrimCursor;
    SetPolyG4(prim);
    r0 = (c & 31) << 3;
    g0 = (c >> 2) & 0xF8;
    b0 = (c >> 7) & 0xF8;
    r1 = (c >> 13) & 0xF8;
    g1 = (c >> 18) & 0xF8;
    b1 = (c >> 23) & 0xF8;
    setXY4(prim, 0, 0, SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    prim->r0 = prim->r1 = r0;
    prim->g0 = prim->g1 = g0;
    prim->b0 = prim->b1 = b0;
    prim->r2 = prim->r3 = r1;
    prim->g2 = prim->g3 = g1;
    prim->b2 = prim->b3 = b1;
    GFX_AddPrim(6, sizeof(POLY_G4));
    if (GetGraphType() == 1) {
        mode = 0x225;
    } else if (GetGraphType() == 2) {
        mode = 0x225;
    } else {
        mode = 0x95;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, mode, 0);
    GFX_AddPrim(6, sizeof(DR_MODE));
}
