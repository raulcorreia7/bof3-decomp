#include "area140_13.h"

/* Lays the six textured quads of the actor's facing over the neighbouring cells. */
MATCH void func_801F3950(s32 facing, s32 height) {
    POLY_FT4* prim;
    long      depth;
    long      flag;
    s32       cell_x;
    s32       cell_y;
    s32       quad;
    s32       corner;

    for (quad = 0; quad < 6; quad++) {
        cell_x = TO_COORD(SELF(Actor)->pos.x.part.integer + D_801F4824[facing][quad][0]);
        cell_y = TO_COORD(SELF(Actor)->pos.y.part.integer + D_801F4824[facing][quad][1]);
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, (GetGraphType() == 1 || GetGraphType() == 2) ? 0x225 : 0x95, 0);
        Area_CellAddPrim(cell_x, cell_y, 1, sizeof(DR_MODE));
        prim = (POLY_FT4*)g_GfxPrimCursor;
        SetPolyFT4(prim);
        SetShadeTex(prim, 0);
        for (corner = 0; corner < 4; corner++) {
            g_ScratchPadVectors[corner].vx = (((SELF(Actor)->pos.x.part.integer + D_801F4824[facing][quad][0]) - 0x80 + D_801F4800[D_801F4824[facing][quad][2]][corner][0]) * 128) - 0x40;
            g_ScratchPadVectors[corner].vy = (((SELF(Actor)->pos.y.part.integer + D_801F4824[facing][quad][1]) - 0x80 + D_801F4800[D_801F4824[facing][quad][2]][corner][1]) * 128) - 0x40;
            g_ScratchPadVectors[corner].vz = D_801F4854[facing] + D_801F4800[D_801F4824[facing][quad][2]][corner][2] * 128 - height;
        }
        RotTransPers4(&g_ScratchPadVectors[0], &g_ScratchPadVectors[1], &g_ScratchPadVectors[2], &g_ScratchPadVectors[3], (long*)&prim->x0, (long*)&prim->x1, (long*)&prim->x2, (long*)&prim->x3,
                      &depth, &flag);
        Area_ApplyTileToQuad((0x12 << 24) + (D_801F4858[D_801F4824[facing][quad][2]] << 16) + D_801F4824[facing][quad][3], prim, 1);
        Area_CellAddPrim(cell_x, cell_y, 1, sizeof(POLY_FT4));
    }
}
