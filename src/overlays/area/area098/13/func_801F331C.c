#include "area098_13.h"

/* Steps the dot trail: moves and draws each live dot, then clears the actor once
 * the countdown reaches zero. */
MATCH void func_801F331C(void) {
    SceneDot* dot;
    TILE_1*   tile;
    u16       i;

    dot = SCENE_DOT_TRAIL;
    for (i = 0; i < D_801F651C; dot++, i++) {
        if (dot->active != 0) {
            if (g_Task->unk_06 == 0) {
                if (dot->life != 0) {
                    dot->x += dot->dx;
                    dot->y += dot->dy;
                    dot->life--;
                }
            } else if (dot->life != 0) {
                dot->life--;
            } else {
                dot->x += dot->dx;
                dot->y += dot->dy;
            }
            tile = (TILE_1*)g_GfxPrimCursor;
            SetTile1(tile);
            tile->x0 = dot->x;
            tile->y0 = dot->y;
            tile->r0 = (dot->color & 0x1F) << 3;
            tile->g0 = (dot->color & 0x3E0) >> 2;
            tile->b0 = (dot->color & 0x7C00) >> 7;
            GFX_AddPrim(2, sizeof(TILE_1));
        }
        dot->active ^= 1;
    }
    if (--g_Task->timer == 0) {
        Actor_Clear();
    }
}
