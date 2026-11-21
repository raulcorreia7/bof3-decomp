#include "start_08.h"

MATCH void func_801E7720(s16 tile_x, s8 tile_type) {
    TILE* tile;
    s32   tpage;

    tpage = getTPage(TPAGE_DEPTH_8BIT, TPAGE_ABR_SUB, 704, 256);
    GFX_AddDrawMode(tpage);
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    PSX_SET_SEMI_TRANSPARENT(tile);
    setXY0(tile, 0, tile_x);
    setWH(tile, SCREEN_WIDTH, 13);
    tile->b0 = tile_type;
    tile->g0 = tile_type;
    tile->r0 = tile_type;
    GFX_AddPrim(GFX_LAYER_UI, sizeof(TILE));
}
