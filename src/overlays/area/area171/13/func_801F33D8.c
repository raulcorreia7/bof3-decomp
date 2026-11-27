#include "area171_13.h"

MATCH void func_801F33D8(void) {
    POLY_F4* prim;
    s32      mode;

    mode = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_ADD, 320, 256);
    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT, mode);
    prim = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(prim);
    SetSemiTrans(prim, 1);
    setXY4(prim, 0, 0, SCREEN_WIDTH, 0, 0, SCREEN_HEIGHT, SCREEN_WIDTH, SCREEN_HEIGHT);
    setRGB0(prim, 0, 0x30, D_801F3F88[SELF(Actor)->header.step] * 8);
    GFX_AddPrim(GFX_LAYER_EFFECT, sizeof(POLY_F4));
    if ((g_FrameCount & 7) == 0) {
        SELF(Actor)->header.step = (SELF(Actor)->header.step + 1) & 3;
    }
}
