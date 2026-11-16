#include "area096_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F2ECC(s32 depth, s32 height) {
    SVECTOR* vectors;
    u8*      prim;
    s32      p;
    s32      flag;
    s32      i;

    i       = 0;
    vectors = D_1F800014;
    do {
        prim = g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        /* Cell coordinates into area view space: 128 units per cell (<<7); 0x4040 is the grid
         * origin plus half a cell, which has no name in the tree. */
        vectors[0].vx = vectors[2].vx = (D_801F3624[i].x << 7) - 0x4040;
        vectors[0].vy = vectors[1].vy = ((D_801F3624[i].y - 0x80) << 7) - height - 0x40;
        vectors[1].vx = vectors[3].vx = ((D_801F3624[i].x - 0x80) << 7) | AREA_CELL_HALF;
        vectors[2].vy = vectors[3].vy = ((D_801F3624[i].y - 0x80) << 7) + height - 0x40;
        vectors[0].vz = vectors[1].vz = vectors[2].vz = vectors[3].vz = depth;
        RotTransPers4(&vectors[0], &vectors[1], &vectors[2], &vectors[3], (s32*)(prim + 8), (s32*)(prim + 0x10), (s32*)(prim + 0x18), (s32*)(prim + 0x20), &p, &flag);
        Area_ApplyTileToQuad(AREA_QUAD_PART_WORD | (height << 16), prim, 1);
        Area_AddCellPrim(D_801F3624[i].x << 16, D_801F3624[i].y << 16, D_801F3624[i].z, sizeof(POLY_FT4));
        i++;
    } while (i < AREA_PAYLOAD_QUAD_COUNT);
}
#else
INCLUDE_ASM(func_801F2ECC);
#endif
