#include "area077_14.h"

MATCH void func_801F3B48(Point2s* pos, u8 shade) {
    TILE_1* tile = (TILE_1*)g_GfxPrimCursor;

    SetTile1(tile);
    SetSemiTrans(tile, 1);
    tile->x0 = pos->x;
    tile->y0 = pos->y;
    tile->r0 = shade;
    tile->g0 = shade;
    tile->b0 = shade;
    GFX_AddPrim(1, 12);
}
