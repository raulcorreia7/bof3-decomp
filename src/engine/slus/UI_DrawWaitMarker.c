#include "engine/slus/slus.h"

/* when the graphics-flag word has bit 0x20, draws an 8x8 flat sprite at the position: draw mode from a new
 * TPage, then the sprite primitive with CLUT, RGB, position, size and semi-transparency, appended to the output
 * table.
 */
MATCH void UI_DrawWaitMarker(s16 x, s16 y) {
    SPRT* prim;

    if (g_FrameCount & 0x20) {
        GFX_AddDrawMode(GetTPage(0, 1, FONT_TPAGE_X, FONT_TPAGE_Y) & HALF_MASK);
        prim = (SPRT*)g_GfxPrimCursor;
        SetSprt(prim);
        setClut(prim, 192, STAGE_PALETTE_Y);
        setRGB0(prim, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
        setWH(prim, 8, 8);
        setXY0(prim, x, y);
        setUV0(prim, 208, 248);
        SetSemiTrans(prim, 1);
        GFX_AddPrim(1, sizeof(SPRT));
    }
}
