#include "batl_ovr_00.h"

MATCH void func_801EF318(void) {
    TILE* tile;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(DR_MODE));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setXY0(tile, 0, 0);
    setWH(tile, SCREEN_WIDTH, SCREEN_HEIGHT);
    setRGB0(tile, 0, 0, 0);
    GFX_AddPrim(GFX_LAYER_EFFECT_FRONT, sizeof(TILE));
}
