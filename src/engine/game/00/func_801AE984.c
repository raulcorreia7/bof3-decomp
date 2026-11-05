#include "game_00.h"

MATCH void func_801AE984(s32 sprite_x, s32 sprite_y, s32 texture_index, s32 dimmed) {
    SPRT_8* sprite;

    /* GetGraphType() is probed twice; the second result is unused. */
    if (GetGraphType() != 1) {
        GetGraphType();
    }
    GFX_AddDrawMode(0xF);
    sprite = (SPRT_8*)g_GfxPrimCursor;
    SetSprt8(sprite);
    if ((dimmed & BYTE_MASK) == 0) {
        sprite->r0 = 0x7F;
        sprite->g0 = 0x7F;
        sprite->b0 = 0x7F;
    } else {
        sprite->r0 = 0x28;
        sprite->g0 = 0x28;
        sprite->b0 = 0x28;
    }

    sprite->x0   = (u16)(sprite_x + 1);
    sprite->y0   = (u16)sprite_y;
    sprite->u0   = (u8)(((texture_index & BYTE_MASK) * 8) - 56);
    sprite->v0   = 248;
    sprite->clut = GetClut(192, 480);
    GFX_AddPrim(1U, 0x10U);
}
