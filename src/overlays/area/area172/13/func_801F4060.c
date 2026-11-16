#include "area172_13.h"

MATCH void func_801F4060(s16 level) {
    TILE* tile;
    u8    shade;

    if (level < 0) {
        shade = 0;
    } else if (level >= 256) {
        shade = 0xFF;
    } else {
        shade = level;
    }
    GFX_AddDitheredDrawMode(GFX_LAYER_UI, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_ADD, 0x380, 0x100));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    SetSemiTrans(tile, 1);
    tile->w = SCREEN_WIDTH;
    setXY0(tile, 0, 0);
    tile->h = SCREEN_HEIGHT;
    setRGB0(tile, shade, shade, shade);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(TILE));
}
