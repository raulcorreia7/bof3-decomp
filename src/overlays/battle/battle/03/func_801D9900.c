#include "battle_03.h"

MATCH void func_801D9900(void) {
    TILE* tile;

    GFX_AddDrawMode(GetTPage(0, 2, FONT_TPAGE_X, FONT_TPAGE_Y));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setWH(tile, 960, 240);
    setXY0(tile, 0, 0);
    setRGB0(tile, 40, 40, 40);
    SetSemiTrans(tile, 1);
    GFX_AddPrim(1, sizeof(TILE));
}
