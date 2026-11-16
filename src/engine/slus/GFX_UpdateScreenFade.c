#include "engine/slus/slus.h"

/* draws a draw-mode primitive for blend_mode and a full-screen tint tile shaded by level >> 7, then
 * adds delta to level and returns bit 15 of the sum (the fade ran past 0 or 0x7FFF).
 */
MATCH s32 GFX_UpdateScreenFade(u16* level, s32 delta, char semi_trans, u32 order, u8 blend_mode) {
    TILE* sprite;
    u16   tpage;
    u8    shade;
    u32   mask;
    s32   sum;

    tpage = GetTPage(TPAGE_DEPTH_8BIT, blend_mode, 320, 0);

    GFX_ADD_LAYER_DRAW_MODE(order & BYTE_MASK, tpage);
    sprite = (TILE*)g_GfxPrimCursor;
    SetTile(sprite);
    mask       = semi_trans & BYTE_MASK;
    shade      = (*level >> 7);
    sprite->w  = SCREEN_WIDTH;
    sprite->x0 = 0;
    sprite->y0 = 0;
    sprite->h  = SCREEN_HEIGHT;
    sprite->b0 = shade;
    sprite->g0 = shade;
    sprite->r0 = shade;
    SetSemiTrans(sprite, mask);
    GFX_AddPrim(order & BYTE_MASK, sizeof(TILE));
    sum = *level + delta;
    {
        s32 result = (((u32)sum << 16) >> 31);
        *level     = sum;
        return result;
    }
}
