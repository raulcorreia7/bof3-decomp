#include "area199_13.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F3398(void) {
    POLY_FT4* prim;
    POLY_FT4* cell;
    s32       actor_row;
    s32       column;
    s32       index;
    s32       i;
    s32       row;
    s32       next_row;
    s32       x;
    s32       y;
    s32       texture_row;

    for (actor_row = 0; actor_row < 2; actor_row++) {
        row = D_801F44B4[actor_row];
        x   = (g_Actors[1 + actor_row].pos.x.fixed + 0x4000) >> 16;
        index = (row * 6) + (actor_row * 3);
        if (x >= D_801F54D0[index]) {
            next_row = (row + 1) & 0x1F;
            index    = (next_row * 6) + (actor_row * 3);
            D_801F54D0[index]     = x;
            D_801F54D0[index + 1] = g_Actors[1 + actor_row].pos.y.part.integer;
            D_801F54D0[index + 2] = (D_801F54D0[(row * 6) + (actor_row * 3) + 2] - 1) & 1;
            D_801F44B4[actor_row] = next_row;
        }

        texture_row = actor_row * 2;
        for (i = 0, index = actor_row * 3; i < 0x20; i++, index += 6) {
            cell = Area_CellFindQuad(D_801F54D0[index], D_801F54D0[index + 1]);
            if (cell == NULL) {
                continue;
            }
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            prim->x0 = cell->x0;
            prim->x1 = cell->x1;
            prim->x2 = cell->x2;
            prim->x3 = cell->x3;
            Area_ApplyTileToQuad(D_801F44B4[0x90 + texture_row] + 0x25808000 + D_801F54D0[index + 2], prim, 1);
            Area_CellAddPrim(D_801F54D0[index] << 16, D_801F54D0[index + 1] << 16, 0, sizeof(POLY_FT4));

            y    = D_801F54D0[index + 1] + D_801F44B4[0x94 + actor_row];
            cell = Area_CellFindQuad(D_801F54D0[index], y);
            if (cell == NULL) {
                continue;
            }
            prim = (POLY_FT4*)g_GfxPrimCursor;
            SetPolyFT4(prim);
            SetShadeTex(prim, 1);
            prim->x0 = cell->x0;
            prim->x1 = cell->x1;
            prim->x2 = cell->x2;
            prim->x3 = cell->x3;
            Area_ApplyTileToQuad(D_801F44B4[0x91 + texture_row] + 0x25808000 + D_801F54D0[index + 2], prim, 1);
            Area_CellAddPrim(D_801F54D0[index] << 16, y << 16, 0, sizeof(POLY_FT4));
        }
    }
}
#else
INCLUDE_ASM(func_801F3398);
#endif
