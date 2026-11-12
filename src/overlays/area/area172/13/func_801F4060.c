#include "area172_13.h"

MATCH void func_801F4060(s16 level) {
    TILE* tile;
    u8    shade;

    if (level < 0) {
        shade = 0;
    } else if (level >= 0x100) {
        shade = 0xFF;
    } else {
        shade = level;
    }
    GFX_AddDitheredDrawMode(1, GetTPage(0, 1, 0x380, 0x100));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    tile->w = SCREEN_WIDTH;
    setXY0(tile, 0, 0);
    tile->h  = SCREEN_HEIGHT;
    tile->r0 = shade;
    tile->g0 = shade;
    tile->b0 = shade;
    GFX_AddPrim(1, sizeof(TILE));
}
