#include "area189_13.h"

MATCH void func_801F4B64(TILE_1* source) {
    TILE_1* tile;
    s32     i;

    for (i = 0; i < 8; i += 2) {
        tile = (TILE_1*)g_GfxPrimCursor;
        SetTile1(tile);
        SetSemiTrans(tile, 1);
        tile->x0 = source->x0 + D_801F6284[i];
        tile->y0 = source->y0 + D_801F6285[i];
        tile->r0 = source->r0 >> 2;
        tile->g0 = source->g0 >> 2;
        tile->b0 = source->b0 >> 2;
        func_801F497C(sizeof(TILE_1));
    }
}
