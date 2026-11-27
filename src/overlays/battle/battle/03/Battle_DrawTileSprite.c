#include "battle_03.h"

/* Queues a 4x4 tile sprite at the origin, textured from the tile table and tinted by the palette row. */
/* func_801DA14C */
MATCH void Battle_DrawTileSprite(s32 origin_x, s32 origin_y, s32 tile_offset, s32 clut_index) {
    s32       x;
    s32       y;
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
    *(volatile u16*)&primitive->tpage = GetTPage(TPAGE_DEPTH_4BIT, TPAGE_ABR_HALF, FONT_TPAGE_X, FONT_TPAGE_Y);
    palette_index &= BYTE_MASK;
    /* FAKE: retail reads g_WindowStyle as s8. */
    setClut(primitive, (((*(s8*)&g_WindowStyle) * 2) + palette_index) * 16, STAGE_PALETTE_Y + 1);
    start_x = x;
    setRGB0(primitive, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL, GFX_COLOR_NEUTRAL);
    start_y = y;
    x += 4;
    y += 4;
    palette_offset &= BYTE_MASK;
    palette_offset *= 4;
    setXY4(primitive, start_x, start_y, x, start_y, start_x, y, x, y);
    v_delta = palette_index * 8;
    setUV0(primitive, D_801EAF2C[palette_offset], (D_801EAF2D[palette_offset] - v_delta));
    primitive->u1 = (D_801EAF2C[palette_offset] + D_801EAF2E[palette_offset]);
    primitive->v1 = (D_801EAF2D[palette_offset] - v_delta);
    primitive->u2 = D_801EAF2C[palette_offset];
    primitive->v2 = (D_801EAF2F[palette_offset] + (D_801EAF2D[palette_offset] - v_delta));
    primitive->u3 = (D_801EAF2C[palette_offset] + D_801EAF2E[palette_offset]);
    primitive->v3 = (D_801EAF2F[palette_offset] + (D_801EAF2D[palette_offset] - v_delta));
    SetSemiTrans(primitive, palette_index);
    GFX_AddPrim(GFX_LAYER_UI, sizeof(POLY_FT4));
}
