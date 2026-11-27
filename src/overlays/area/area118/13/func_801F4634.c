#include "area118_13.h"

/* Lays the textured quad over the neighbouring cells at the actor's position. */
MATCH void func_801F4634(s32 tile, s32 height) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       x;
    s32       y;
    s32       x1;
    s32       y1;
    SVECTOR*  vectors;

    vectors       = g_ScratchPadVectors;
    vectors[0].vx = vectors[1].vx = vectors[2].vx = vectors[3].vx = (((SELF(Actor)->pos.x.fixed >> 16) - 0x80) << 7) + 0x40;
    vectors[0].vy = vectors[2].vy = (((SELF(Actor)->pos.y.fixed >> 16) - 0x80) << 7) + height - 8;
    vectors[1].vy = vectors[3].vy = (((SELF(Actor)->pos.y.fixed >> 16) - 0x80) << 7) - height + 8;
    x                             = (vectors[0].vx + 0x4000) << 9;
    y                             = (vectors[0].vy + 0x4000) << 9;
    vectors[0].vz                 = -Area_HeightSample(x, y) / 2 - SELF(Actor)->pos.z.part.integer - height + 8;
    vectors[2].vz                 = -Area_HeightSample(x, y) / 2 - SELF(Actor)->pos.z.part.integer + height;
    x1                            = (vectors[1].vx + 0x4000) << 9;
    y1                            = (vectors[1].vy + 0x4000) << 9;
    vectors[1].vz                 = -Area_HeightSample(x1, y1) / 2 - SELF(Actor)->pos.z.part.integer - height + 8;
    vectors[3].vz                 = -Area_HeightSample(x1, y1) / 2 - SELF(Actor)->pos.z.part.integer + height;
    prim                          = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    RotTransPers4(&vectors[0], &vectors[1], &vectors[2], &vectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    Area_ApplyTileToQuad(((0x2850 << 16) | 0xF3) + tile, prim, 1);
    Area_CellAddPrim(SELF(Actor)->pos.x.fixed, SELF(Actor)->pos.y.fixed, 1, sizeof(POLY_FT4));
}
