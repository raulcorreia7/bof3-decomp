#include "area077_14.h"

MATCH void func_801F3B48(Point2s* pos, u8 shade) {
    TILE_1* tile = (TILE_1*)g_GfxPrimCursor;

    SetTile1(tile);
    SetSemiTrans(tile, 1);
    setXY0(tile, pos->x, pos->y);
    setRGB0(tile, shade, shade, shade);
    GFX_AddPrim(1, 12);
}
