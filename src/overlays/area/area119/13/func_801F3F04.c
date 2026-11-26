#include "area119_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3F04(s32 steps) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       i;
    s32       phase;
    s32       step;
    s32       spread;
    s32       shade;
    s32       x;
    s32       y;

    phase = (g_FrameCount * 4) & 7;
    step  = phase * steps;
    x     = (TASK(Actor)->pos.x.fixed >> 9) - 0x4000;
    y     = (TASK(Actor)->pos.y.fixed >> 9) - 0x4000;
    i     = 0;
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        g_ScratchPadVectors[0].vx = x;
        D_1F800016                = y;
        D_1F800018                = -0x80 - (step + i * steps * 8);
        RotTransPers(g_ScratchPadVectors, (long*)D_1F800034, &depth, &flag);
        spread   = step / 16 + 4 + ((i < 4) ? i * steps / 2 : steps * 2);
        shade    = 8 - steps;
        shade    = (((7 - i) * 8 + (7 - phase)) << 17) / shade;
        prim->x0 = prim->x2 = (u16)D_1F800034[0] - spread;
        prim->x1 = prim->x3 = (u16)D_1F800034[0] + spread;
        prim->y0 = prim->y1 = (u16)D_1F800034[1] - spread;
        prim->y2 = prim->y3 = (u16)D_1F800034[1] + spread;
        Area_ApplyTileToQuad((shade & 0xF80000) | (0xBAu << 24) | 0x9124u, prim, 1);
        prim->g0 >>= 1;
        i++;
        Area_CellAddPrim(TASK(Actor)->pos.x.fixed, TASK(Actor)->pos.y.fixed, 1, sizeof(POLY_FT4));
    } while (i < 8);
}
#else
INCLUDE_ASM(func_801F3F04);
#endif
