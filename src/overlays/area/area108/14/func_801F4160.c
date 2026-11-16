#include "area108_14.h"

MATCH void func_801F4160(s32 step, s32 shade) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       size;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    size                      = step * 4;
    g_ScratchPadVectors[0].vx = g_ScratchPadVectors[2].vx = -0x3500 - size;
    g_ScratchPadVectors[1].vx = g_ScratchPadVectors[3].vx = size - 0x3500;
    g_ScratchPadVectors[0].vy = g_ScratchPadVectors[1].vy = -0x1F00 - size;
    g_ScratchPadVectors[2].vy = g_ScratchPadVectors[3].vy = size - 0x1F00;
    g_ScratchPadVectors[0].vz = g_ScratchPadVectors[1].vz = g_ScratchPadVectors[2].vz = g_ScratchPadVectors[3].vz = -0x80;
    RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth,
                  &flag);
    Area_ApplyTileToQuad(AREA108_QUAD_WORD + ((shade & 0xF8) << 16), prim, 1);
    GFX_AddPrim(5, 0x28);
}
