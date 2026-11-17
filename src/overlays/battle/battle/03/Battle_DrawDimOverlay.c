#include "battle_03.h"

/* func_801D9900 */
MATCH void Battle_DrawDimOverlay(void) {
    TILE* tile;

    GFX_AddDrawMode(GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_SUB, FONT_TPAGE_X, FONT_TPAGE_Y));
    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setWH(tile, 960, SCREEN_HEIGHT);
    setXY0(tile, 0, 0);
    setRGB0(tile, 40, 40, 40);
    SetSemiTrans(tile, 1);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(TILE));
}
