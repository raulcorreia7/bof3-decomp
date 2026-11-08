#include "engine/slus/slus.h"

MATCH void func_8014FB80(s16 x, s16 y, u16 clut, u8 shade) {
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
    SetSemiTrans((SPRT*)g_GfxPrimCursor, 1);
    GFX_AddPrim(1, sizeof(SPRT));
}
