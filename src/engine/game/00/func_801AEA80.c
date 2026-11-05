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
    if ((shade_mode & BYTE_MASK) == 0) {
        sprite->r0 = 0x80;
        sprite->g0 = 0x80;
        sprite->b0 = 0x80;
    } else {
        sprite->r0 = 0x40;
        sprite->g0 = 0x40;
        sprite->b0 = 0x40;
    }

    sprite->x0 = sprite_x;
    sprite->y0 = sprite_y;
    sprite->u0 = (((texture_index & BYTE_MASK) * 8) + 56);
    sprite->v0 = 248;
    switch (texture_index & BYTE_MASK) {
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
