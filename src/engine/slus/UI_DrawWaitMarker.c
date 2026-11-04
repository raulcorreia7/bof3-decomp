#include "engine/slus/slus.h"

/* when the graphics-flag word has bit 0x20, draws an 8x8 flat sprite at the position: draw mode from a new
 * TPage, then the sprite primitive with CLUT, RGB, position, size and semi-transparency, appended to the output
 * table.
 */
MATCH void UI_DrawWaitMarker(s16 x, s16 y) {
    SPRT* prim;

    if (g_FrameCount & 0x20) {
        SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, GetTPage(0, 1, 960, 0) & HALF_MASK, NULL);
        GFX_AddPrim(1, 0xC);
        prim = (SPRT*)g_GfxPrimCursor;
        SetSprt(prim);
        prim->clut = GetClut(192, 480);
        PSX_SET_NEUTRAL_RGB(prim);
        prim->w  = 8;
        prim->h  = 8;
        prim->u0 = 208;
        prim->x0 = x;
        prim->y0 = y;
        prim->v0 = 248;
        PSX_SET_SEMI_TRANSPARENT(prim);
        GFX_AddPrim(1, 0x14);
    }
}
