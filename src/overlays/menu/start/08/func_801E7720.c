#include "start_08.h"

MATCH void func_801E7720(s16 tile_x, s8 tile_kind) {
    TILE* tile;
    s32   tpage;

    tpage = getTPage(1, 2, 704, 256);
    GFX_AddDrawMode(tpage);
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    setXY0(tile, 0, tile_x);
    setWH(tile, 320, 13);
    tile->b0 = tile_kind;
    tile->g0 = tile_kind;
    tile->r0 = tile_kind;
    GFX_AddPrim(1, 0x10);
}
