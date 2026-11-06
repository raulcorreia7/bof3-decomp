#include "game_00.h"

MATCH void func_801AEA80(s32 sprite_x, s32 sprite_y, s32 texture_index, s32 shade_mode) {
    SPRT_8* sprite;
    s16     clut;

    /* GetGraphType() is probed twice; the second result is unused. */
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    GFX_AddDrawMode(0xF);
    sprite = (SPRT_8*)g_GfxPrimCursor;
    SetSprt8(sprite);
    if ((shade_mode & 0xFF) == 0) {
        setRGB0(sprite, 0x80, 0x80, 0x80);
    } else {
        setRGB0(sprite, 0x40, 0x40, 0x40);
    }

    setXY0(sprite, sprite_x, sprite_y);
    setUV0(sprite, (((texture_index & 0xFF) * 8) + 56), 248);
    switch (texture_index & 0xFF) {
        case 1:
        case 3:
        case 0xF:
            clut = 0x780E;
            break;
        default:
            clut = 0x780C;
            break;
    }
    sprite->clut = clut;
    GFX_AddPrim(1U, 0x10U);
}
