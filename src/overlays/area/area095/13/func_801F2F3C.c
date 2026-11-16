#include "area095_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2F3C(s32 depth, s32 height) {
    POLY_FT4* prim;
    SVECTOR*  quad;
    u8*       cell_y;
    u8*       cell_x;
    s32       i;
    long      p;
    long      flag;

    i      = 0;
    quad   = D_1F800014;
    cell_y = D_801F3695;
    cell_x = cell_y - 1;
    do {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        quad[0].vx = quad[2].vx = (*cell_x << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
        quad[0].vy = quad[1].vy = ((*cell_y - 0x80) << 7) - height - AREA_CELL_HALF;
        quad[1].vx = quad[3].vx = ((*cell_x - 0x80) << 7) | AREA_CELL_HALF;
        quad[0].vz = quad[1].vz = quad[2].vz = quad[3].vz = depth;
        quad[2].vy = quad[3].vy = ((*cell_y - 0x80) << 7) + (height - AREA_CELL_HALF);
        RotTransPers4(&quad[0], &quad[1], &quad[2], &quad[3], (s32*)((u8*)prim + 8), (s32*)((u8*)prim + 0x10), (s32*)((u8*)prim + 0x18), (s32*)((u8*)prim + 0x20), &p, &flag);
        Area_ApplyTileToQuad(AREA095_QUAD_PART_WORD | (height << 16), prim, 1);
        Area_AddCellPrim(*cell_x << 16, *cell_y << 16, D_801F3696[i * 3], sizeof(POLY_FT4));
        i++;
        cell_y += 3;
        cell_x += 3;
    } while (i < 15);
}
#else
INCLUDE_ASM(func_801F2F3C);
#endif
