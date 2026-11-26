#include "engine/slus/slus.h"

/* Queues the glyph sprite UI_TextDrawString prepared: neutral colour, clut, position (x, y + shade), semi-transparent, on the UI layer. */
MATCH void UI_TextQueueGlyph(s16 x, s16 y, u16 clut, u8 shade) {
    SPRT* sprite;
    SPRT* position;

    sprite                       = (SPRT*)g_GfxPrimCursor;
    sprite->r0                   = GFX_COLOR_NEUTRAL;
    sprite->clut                 = clut;
    ((SPRT*)g_GfxPrimCursor)->g0 = GFX_COLOR_NEUTRAL;
    ((SPRT*)g_GfxPrimCursor)->b0 = GFX_COLOR_NEUTRAL;
    position                     = (SPRT*)g_GfxPrimCursor;
    setXY0(position, x, y + shade);
    SetSprt(position);
    PSX_SET_SEMI_TRANSPARENT((SPRT*)g_GfxPrimCursor);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(SPRT));
}
