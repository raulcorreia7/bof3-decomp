#include "engine/slus/slus.h"

MATCH void func_8014FB80(s16 x, s16 y, u16 clut, u8 shade) {
    SPRT* sprite;
    SPRT* position;

    sprite                       = (SPRT*)g_GfxPrimCursor;
    sprite->r0                   = 0x80;
    sprite->clut                 = clut;
    ((SPRT*)g_GfxPrimCursor)->g0 = 0x80;
    ((SPRT*)g_GfxPrimCursor)->b0 = 0x80;
    position                     = (SPRT*)g_GfxPrimCursor;
    setXY0(position, x, y + shade);
    SetSprt(position);
    SetSemiTrans((SPRT*)g_GfxPrimCursor, 1);
    GFX_AddPrim(1, 0x14);
}
