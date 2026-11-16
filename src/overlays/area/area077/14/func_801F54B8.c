#include "area077_14.h"

MATCH void func_801F54B8(void) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       x;
    s32       y;

    prim = (POLY_FT4*)g_GfxPrimCursor;
    x    = g_Task->pos.x.fixed >> 9;
    y    = g_Task->pos.y.fixed >> 9;
    SetPolyFT4(prim);
    SetShadeTex(prim, 0);
    D_1F800014[0].vx = D_1F800014[2].vx = x - 0x4040;
    D_1F800014[1].vx = D_1F800014[3].vx = x - 0x3F40;
    D_1F800014[0].vy = D_1F800014[1].vy = y - 0x4030;
    D_1F800014[2].vy = D_1F800014[3].vy = y - 0x3FD0;
    D_1F800014[0].vz = D_1F800014[1].vz = COORD_INT(g_Task->pos.z) - 0x30;
    D_1F800014[2].vz = D_1F800014[3].vz = COORD_INT(g_Task->pos.z) + 0x30;
    RotTransPers4(&D_1F800014[0], &D_1F800014[1], &D_1F800014[2], &D_1F800014[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
    Area_ApplyTileToQuad(AREA_SPIN_QUAD_WORD, prim, 1);
    Area_AddCellPrim(0x5D0000, 0x340000, 0, 0x28);
}
