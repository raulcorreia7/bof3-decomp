#include "area171_13.h"

MATCH void func_801F33D8(void) {
    POLY_F4* prim;
    s32      mode;

    if (GetGraphType() == 1) {
        mode = 0x2A5;
    } else if (GetGraphType() == 2) {
        mode = 0x2A5;
    } else {
        mode = 0xB5;
    }
    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, mode, 0);
    GFX_AddPrim(3, sizeof(DR_MODE));
    prim = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, 0, 0, SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    setRGB0(prim, 0, 0x30, D_801F3F88[g_Task->header.step] * 8);
    GFX_AddPrim(3, sizeof(POLY_F4));
    if ((g_FrameCount & 7) == 0) {
        g_Task->header.step = (g_Task->header.step + 1) & 3;
    }
}
