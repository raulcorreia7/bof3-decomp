#include "area041_13.h"

/* Draw the six-row sprite quad from the row table's cell pairs and sprite words. */
MATCH void func_801F3704(void) {
    POLY_FT4* prim;
    SVECTOR*  quad;
    u8*       cell_y;
    u8*       cell_x;
    s16       vz;
    s32       i;
    long      depth;
    long      flag;

    i      = 0;
    quad   = g_ScratchPadVectors;
    vz     = -0x88;
    cell_y = D_801F4364 + 1;
    cell_x = cell_y - 1;
    for (; i < 6; i++) {
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        quad[0].vx = quad[1].vx = (*cell_x << 7) - (AREA_CELL_ORIGIN - AREA_CELL_HALF);
        quad[2].vx = quad[3].vx = (*cell_x << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
        quad[0].vy = quad[2].vy = (*cell_y << 7) - (AREA_CELL_ORIGIN - AREA_CELL_HALF);
        quad[1].vy = quad[3].vy = (*cell_y << 7) - (AREA_CELL_ORIGIN + AREA_CELL_HALF);
        quad[0].vz = quad[1].vz = quad[2].vz = quad[3].vz = vz;

        RotTransPers4(&quad[0], &quad[1], &quad[2], &quad[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3, &depth, &flag);
        Area_ApplyTileToQuad((0xBD50u << 16) | D_801F4370[i], prim, 1);
        Area_CellAddPrim(*cell_x << 16, *cell_y << 16, 0, sizeof(POLY_FT4));
        cell_y += 2;
        cell_x += 2;
    }
}
