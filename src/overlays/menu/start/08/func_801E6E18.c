#include "start_08.h"

/* Draws one 16-row sprite at (x, y), first as an additive-blend halo when blend is set, then the plain sprite. */
MATCH void func_801E6E18(s16 x, s16 y, s32 row, s32 shade, u8 blend) {
    SPRT* sprite;
    u8    widths[2] = {0x80, 0x90};
    u8    gray;
    u8    col;

    col  = row;
    gray = shade;
    if (blend != 0) {
        GFX_AddDrawMode(GetTPage(0, 2, 896, 0) & HALF_MASK);
        sprite = (SPRT*)g_GfxPrimCursor;
        SetSprt(sprite);
        sprite->v0 = row * 16;
        setXY0(sprite, x, y);
        sprite->u0 = 0;
        setWH(sprite, widths[col], 16);
        sprite->clut = GetClut(0, 491);
        setRGB0(sprite, shade * 2, shade * 2, shade * 2);
        SetSemiTrans(sprite, blend);
        GFX_AddPrim(1, 0x14);
    }
    GFX_AddDrawMode(GetTPage(0, 1, 896, 0) & HALF_MASK);
    sprite = (SPRT*)g_GfxPrimCursor;
    SetSprt(sprite);
    sprite->v0 = row * 16;
    setXY0(sprite, x, y);
    sprite->u0 = 0;
    setWH(sprite, widths[col], 16);
    sprite->clut = GetClut(32, 483);
    setRGB0(sprite, gray, gray, gray);
    SetSemiTrans(sprite, blend);
    GFX_AddPrim(1, 0x14);
}
