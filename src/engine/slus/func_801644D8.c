#include "engine/slus/slus.h"

/* HAND_ASM: a sprite-quad emitter whose prologue, saved registers and frame the compiler profiles
 * do not reproduce. See docs/toolchain.md#compiler-chain. */
#ifdef NON_MATCHING
/* The 16x16 icon cell at index in the sprite sheet, drawn as a textured quad at (x, y) with the
 * given width, height and shade; the clut row comes from a per-index table. */
HAND_ASM void func_801644D8(s32 index, s32 x, s32 y, s32 width, s32 height, s32 shade) {
    POLY_FT4* prim;
    u8        slot = index;

    if (slot < 12) {
        GFX_AddDrawMode(getTPage(0, 0, 960, 0));
    } else {
        GFX_AddDrawMode(getTPage(0, 0, 896, 256));
    }
    prim = GFX_CURSOR(POLY_FT4);
    SetPolyFT4(prim);
    prim->y2 = prim->y3 = y + (u8)height;
    prim->x1 = prim->x3 = x + (u8)width;
    prim->r0 = prim->g0 = prim->b0 = shade;
    prim->x0 = prim->x2 = x;
    prim->y0 = prim->y1 = y;
    if (slot < 12) {
        prim->v0 = prim->v1 = 0xE8;
        prim->u0 = prim->u2 = 0x38 + slot * 16;
        prim->u1 = prim->u3 = 0x48 + slot * 16;
        prim->v2 = prim->v3 = 0xF8;
        prim->tpage         = getTPage(0, 0, 960, 0);
    } else if (slot < 20) {
        prim->v0 = prim->v1 = 0xD0;
        prim->u0 = prim->u2 = 0x78 + (slot - 12) * 16;
        prim->u1 = prim->u3 = 0x88 + (slot - 12) * 16;
        prim->v2 = prim->v3 = 0xE0;
        prim->tpage         = getTPage(0, 0, 896, 256);
    } else {
        prim->v0 = prim->v1 = 0xF0;
        prim->u0 = prim->u2 = 0xA8;
        prim->u1 = prim->u3 = 0xB7;
        prim->v2 = prim->v3 = 0xFF;
        prim->tpage         = getTPage(0, 0, 896, 256);
    }
    prim->clut = (D_80149C78[slot] & 0x3F) | 0x7800;
    GFX_AddPrim(1, sizeof(POLY_FT4));
}
#else
INCLUDE_ASM(func_801644D8);
#endif
