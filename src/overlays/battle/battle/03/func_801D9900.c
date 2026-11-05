#include "battle_03.h"

MATCH void func_801D9900(void) {
    TILE* tile;

    GFX_AddDrawMode(GetTPage(0, 2, FONT_TPAGE_X, FONT_TPAGE_Y));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    tile->w  = 960;
    tile->h  = 240;
    tile->x0 = 0;
    tile->y0 = 0;
    setRGB0(tile, 40, 40, 40);
    PSX_SET_SEMI_TRANSPARENT(tile);
    GFX_AddPrim(1, 0x10);
}
