#include "engine/slus/slus.h"

/* draws a draw-mode primitive for blend_mode and a full-screen tint tile shaded by level >> 7, then
 * adds delta to level and returns bit 15 of the sum (the fade ran past 0 or 0x7FFF).
 */
MATCH s32 GFX_StepScreenFade(u16* level, s32 delta, char semi_trans, u32 order, u8 blend_mode) {
    u8* sprite;
    u16 tpage;
    u8  shade;
    u32 mask;
    s32 sum;

    tpage = GetTPage(1, blend_mode, 320, 0);

    SetDrawMode((DR_MODE*)g_GfxPrimCursor, 0, 0, tpage, (RECT*)0);
    GFX_AddPrim(order & BYTE_MASK, 0xC);
    sprite = g_GfxPrimCursor;
    SetTile((TILE*)sprite);
    mask                  = semi_trans & BYTE_MASK;
    shade                 = (u8)(*level >> 7);
    *(s16*)(sprite + 0xC) = 0x140;
    *(s16*)(sprite + 0x8) = 0;
    *(s16*)(sprite + 0xA) = 0;
    *(s16*)(sprite + 0xE) = 0xF0;
    sprite[0x6]           = shade;
    sprite[0x5]           = shade;
    sprite[0x4]           = shade;
    SetSemiTrans(sprite, mask);
    GFX_AddPrim(order & BYTE_MASK, 0x10);
    sum = (s32)*level + delta;
    {
        s32 result = (s32)(((u32)sum << 16) >> 31);
        *level     = (u16)sum;
        return result;
    }
}
