#include "area098_13.h"

MATCH void func_801F331C(void) {
    TrailDot* dot;
    TILE_1*   tile;
    u16       i;
    u8        timer;

    dot = AREA_TRAIL_DOTS;
    for (i = 0; i < D_801F651C; dot++, i++) {
        if (dot->active != 0) {
            if (SELF(Actor)->unk_06 == 0) {
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
            setXY0(tile, dot->x, dot->y);
            setRGB0(tile, (dot->color & 0x1F) << 3, (dot->color & 0x3E0) >> 2, (dot->color & 0x7C00) >> 7);
            GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(TILE_1));
        }
        dot->active ^= 1;
    }
    ACTOR_COUNT_DOWN(SELF(Actor), timer, timer);
    if (timer == 0) {
        Actor_Clear();
    }
}
