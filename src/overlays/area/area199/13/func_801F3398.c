#include "area199_13.h"

#define AREA199_TRAIL_PART_WORD ((0x2580u << 16) | 0x8000u)

/* Stages each member's walked cells and draws both trail rows at every live cell. */
MATCH void func_801F3398(void) {
    POLY_FT4* prim;
    POLY_FT4* quad;
    POLY_FT4* below;
    s32       member;
    s32       slot;
    s32       i;
    s32       x;

    for (member = 0; member < 2; member++) {
        if (g_Area199TrailCells[D_801F44B4[member]][member].x > (x = (g_Actors[member + 1].pos.x.fixed + 0x4000) >> 16)) {
            slot                                   = (D_801F44B4[member] + 1) & 0x1F;
            g_Area199TrailCells[slot][member].x    = x;
            g_Area199TrailCells[slot][member].y    = COORD_INT(g_Actors[member + 1].pos.y);
            g_Area199TrailCells[slot][member].flag = (g_Area199TrailCells[D_801F44B4[member]][member].flag - 1) & 1;
            D_801F44B4[member]                     = slot;
        }

        for (i = 0; i < 0x20; i++) {
            quad = Area_CellFindQuad(g_Area199TrailCells[i][member].x, g_Area199TrailCells[i][member].y);
            if (quad == NULL) {
                continue;
            }
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            LOWU(prim->x0) = LOWU(quad->x0);
            LOWU(prim->x1) = LOWU(quad->x1);
            LOWU(prim->x2) = LOWU(quad->x2);
            LOWU(prim->x3) = LOWU(quad->x3);
            Area_ApplyTileToQuad(AREA199_TRAIL_PART_WORD + D_801F4544[member * 2] + g_Area199TrailCells[i][member].flag, prim, 1);
            Area_CellAddPrim(g_Area199TrailCells[i][member].x << 16, g_Area199TrailCells[i][member].y << 16, 0, sizeof(POLY_FT4));

            below = Area_CellFindQuad(g_Area199TrailCells[i][member].x, g_Area199TrailCells[i][member].y + (s8)D_801F4548[member]);
            if (below == NULL) {
                continue;
            }
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            LOWU(prim->x0) = LOWU(below->x0);
            LOWU(prim->x1) = LOWU(below->x1);
            LOWU(prim->x2) = LOWU(below->x2);
            LOWU(prim->x3) = LOWU(below->x3);
            Area_ApplyTileToQuad(AREA199_TRAIL_PART_WORD + D_801F4545[member * 2] + g_Area199TrailCells[i][member].flag, prim, 1);
            Area_CellAddPrim(g_Area199TrailCells[i][member].x << 16, (g_Area199TrailCells[i][member].y + (s8)D_801F4548[member]) << 16, 0, sizeof(POLY_FT4));
        }
    }
}
