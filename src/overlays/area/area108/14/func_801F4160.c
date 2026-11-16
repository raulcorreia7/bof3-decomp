#include "area108_14.h"

MATCH void func_801F4160(s32 step, s32 shade) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       size;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    size             = step * 4;
    D_1F800014[0].vx = D_1F800014[2].vx = -0x3500 - size;
    D_1F800014[1].vx = D_1F800014[3].vx = size - 0x3500;
    D_1F800014[0].vy = D_1F800014[1].vy = -0x1F00 - size;
    D_1F800014[2].vy = D_1F800014[3].vy = size - 0x1F00;
    D_1F800014[0].vz = D_1F800014[1].vz = D_1F800014[2].vz = D_1F800014[3].vz = -0x80;
    RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    Area_ApplyTileToQuad(AREA108_QUAD_WORD + ((shade & 0xF8) << 16), prim, 1);
    GFX_AddPrim(5, 0x28);
}
