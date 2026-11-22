#include "batl_ovr_00.h"

MATCH void func_801EF318(void) {
    TILE* tile;

    GFX_ADD_LAYER_DRAW_MODE(GFX_LAYER_EFFECT_FRONT, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setXY0(tile, 0, 0);
    setWH(tile, SCREEN_WIDTH, SCREEN_HEIGHT);
    setRGB0(tile, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(TILE));
}
