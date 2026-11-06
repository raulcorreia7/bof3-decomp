#include "start_08.h"

MATCH void func_801E7720(s16 tile_x, s8 tile_kind) {
    TILE* tile;
    s32   tpage;

    tpage = getTPage(1, 2, 704, 256);
    GFX_AddDrawMode(tpage);
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    PSX_SET_SEMI_TRANSPARENT(tile);
    tile->w = 320;
    setXY0(tile, 0, tile_x);
    tile->h  = 13;
    tile->b0 = tile_kind;
    tile->g0 = tile_kind;
    tile->r0 = tile_kind;
    GFX_AddPrim(1, 0x10);
}
