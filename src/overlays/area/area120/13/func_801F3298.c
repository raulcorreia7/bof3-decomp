#include "area120_13.h"

/* Steps the rising tiles: pulse the colour, grow the height, then drop the tile past its limit. */
MATCH void func_801F3298(void) {
    AreaRiseTile* tile;
    TILE_1*       prim;
    u16           y;
    u8            flags;
    u8            timer;
    u8            missed;
    u16           i;

    missed = 1;
    tile   = MEM_PTR(AreaRiseTile, AREA_WORK + 0x2D00u);
    i      = 0;
    g_Actors[2].header.flags |= ACTOR_FLAG_HIDDEN;
    if (D_801F4FD4 != 0) {
        do {
            flags = tile->flags;
            if ((flags & 0x1) != 0) {
                switch (flags & 0xF0) {
                    case 0:
                        timer       = tile->timer - 1;
                        tile->timer = timer;
                        if (timer == 0) {
                            tile->flags += 0x10;
                            tile->timer = 0x10;
                        }
                        break;
                    case 0x10:
                        tile->step += 2;
                        y       = tile->y + tile->step;
                        tile->y = y;
                        if (D_801F4F34[tile->limit] < (s16)y) {
                            tile->flags = 0;
                        }
                        break;
                }
                prim = (TILE_1*)g_GfxPrimCursor;
                SetTile1(prim);
                prim->x0 = (s16)tile->x >> 4;
                prim->y0 = (s16)tile->y >> 4;
                prim->r0 = (tile->color & 0x1F) << 3;
                prim->g0 = (tile->color & 0x3E0) >> 2;
                prim->b0 = (tile->color & 0x7C00) >> 7;
                GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(TILE_1));
                missed = 0;
            }
            tile++;
            i++;
        } while (i < D_801F4FD4);
    }
    if (missed != 0) {
        Actor_Clear();
    }
}
