#include "area095_13.h"

MATCH void func_801F2F3C(s32 depth, s32 height) {
    SVECTOR* quad;
    u8*      prim;
    long     p;
    long     flag;
    s32      i;

    i    = 0;
    quad = g_ScratchPadVectors;
    do {
        prim = g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        quad[0].vx = quad[2].vx = (D_801F3694[i].x << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
        quad[0].vy = quad[1].vy = ((D_801F3694[i].y - 0x80) << 7) - (s16)(height + AREA_CELL_HALF);
        quad[1].vx = quad[3].vx = ((D_801F3694[i].x - 0x80) << 7) | AREA_CELL_HALF;
        quad[2].vy = quad[3].vy = ((D_801F3694[i].y - 0x80) << 7) + (s16)(height - AREA_CELL_HALF);
        quad[0].vz = quad[1].vz = quad[2].vz = quad[3].vz = depth;
        RotTransPers4(&quad[0], &quad[1], &quad[2], &quad[3], (long*)(prim + 8), (long*)(prim + 0x10), (long*)(prim + 0x18), (long*)(prim + 0x20), &p, &flag);
        Area_ApplyTileToQuad(AREA095_QUAD_PART_WORD | (height << 16), prim, 1);
        Area_CellAddPrim(D_801F3694[i].x << 16, D_801F3694[i].y << 16, D_801F3694[i].z, sizeof(POLY_FT4));
        i++;
    } while (i < AREA_PAYLOAD_QUAD_COUNT);
}
