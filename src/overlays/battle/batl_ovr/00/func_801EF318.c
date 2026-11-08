#include "batl_ovr_00.h"

MATCH void func_801EF318(void) {
    TILE* tile;

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 0, FONT_TPAGE_X, FONT_TPAGE_Y), 0);
    GFX_AddPrim(2, sizeof(DR_MODE));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setXY0(tile, 0, 0);
    setWH(tile, 320, 240);
    setRGB0(tile, 0, 0, 0);
    GFX_AddPrim(2, sizeof(TILE));
}
