#include "battle_03.h"

MATCH void func_801D9900(void) {
    TILE* tile;

    GFX_AddDrawMode(GetTPage(0, 2, FONT_TPAGE_X, FONT_TPAGE_Y));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setWH(tile, 960, 240);
    setXY0(tile, 0, 0);
    setRGB0(tile, 40, 40, 40);
    PSX_SET_SEMI_TRANSPARENT(tile);
    GFX_AddPrim(1, 0x10);
}
