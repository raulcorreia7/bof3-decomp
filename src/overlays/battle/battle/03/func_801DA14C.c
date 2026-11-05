#include "battle_03.h"

/* Queues a 4x4 tile sprite at the origin, textured from the tile table and tinted by the palette row. */
MATCH void func_801DA14C(s16 origin_x, s16 origin_y, s32 tile_offset, s32 clut_index) {
    /* FAKE: retail keeps origin_x in $s2 and origin_y in
     * $s3 (retail `move s2,a0` / `move s3,a1`); gcc 2.7.2 assigns the pair
     * swapped and refuses the in-place `x += 4` (keeps originals in the
     * s-regs, +4 in temps). Declaration order and all four profiles measured
     * no better. */
    MATCH_REG(s16, x, "s2");
    /* FAKE: retail `move s3,a1` and in-place `addiu s3,s3,4`; gcc keeps the original in $s3
     * uncremented and puts origin_y+4 in a temp. */
    MATCH_REG(s16, y, "s3");
    s16       start_y;
    s16       start_x;
    s32       v_delta;
    s32       palette_offset;
    s32       palette_index;
    POLY_FT4* primitive;

    primitive      = (POLY_FT4*)g_GfxPrimCursor;
    x              = origin_x;
    y              = origin_y;
    palette_offset = tile_offset;
    palette_index  = clut_index;
    SetPolyFT4(primitive);
    /* FAKE: the volatile typed store keeps tpage ahead of the palette load. */
    *(volatile u16*)&primitive->tpage = GetTPage(0, 0, 960, 0);
    palette_index &= BYTE_MASK;
    /* FAKE: retail reads D_80144952 as s8. */
    primitive->clut = GetClut((((*(s8*)&D_80144952) * 2) + palette_index) * 16, 481);
    start_x         = x;
    primitive->r0   = 0x80;
    primitive->g0   = 0x80;
    primitive->b0   = 0x80;
    start_y         = y;
    x += 4;
    y += 4;
    palette_offset &= BYTE_MASK;
    palette_offset *= 4;
    primitive->x0 = start_x;
    primitive->y0 = start_y;
    primitive->x1 = x;
    primitive->y1 = start_y;
    primitive->x2 = start_x;
    primitive->y2 = y;
    primitive->x3 = x;
    primitive->y3 = y;
    primitive->u0 = (u8)D_801EAF2C[palette_offset];
    v_delta       = palette_index * 8;
    primitive->v0 = (s8)(D_801EAF2D[palette_offset] - v_delta);
    primitive->u1 = (s8)(D_801EAF2C[palette_offset] + D_801EAF2E[palette_offset]);
    primitive->v1 = (s8)(D_801EAF2D[palette_offset] - v_delta);
    primitive->u2 = (u8)D_801EAF2C[palette_offset];
    primitive->v2 = (s8)(D_801EAF2F[palette_offset] + (D_801EAF2D[palette_offset] - v_delta));
    primitive->u3 = (s8)(D_801EAF2C[palette_offset] + D_801EAF2E[palette_offset]);
    primitive->v3 = (s8)(D_801EAF2F[palette_offset] + (D_801EAF2D[palette_offset] - v_delta));
    SetSemiTrans(primitive, palette_index);
    GFX_AddPrim(1U, 0x28U);
}
