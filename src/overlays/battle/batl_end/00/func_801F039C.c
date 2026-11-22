#include "batl_end_00.h"

#ifdef NON_MATCHING
NON_MATCHING void func_801F039C(s16 x, s16 y, s32 width, s32 height) {
    TILE* tile;
    u16   color;
    s32   r;
    s32   g;
    s32   b;
    s16   top_y;
    s16   right_x;
    s16   bottom_y;

    GFX_ADD_DRAW_MODE(GetTPage(0, 0, 0x3C0, 0));

    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setXY0(tile, x, y + 2);
    setWH(tile, width, height);
    setRGB0(tile, ((*(volatile u16*)(((u8*)&D_80033A08) + (((*(s8*)&g_WindowStyle << 6) | 0x20))) & 0x1F) << 3),
            ((*(volatile u16*)(((u8*)&D_80033A08) + (((*(s8*)&g_WindowStyle << 6) | 0x20))) >> 2) & 0xF8),
            ((*(volatile u16*)(((u8*)&D_80033A08) + (((*(s8*)&g_WindowStyle << 6) | 0x20))) >> 7) & 0xF8));
    SetSemiTrans(tile, 1);
    GFX_AddPrim(1, 0x10);

    top_y    = y + 2;
    right_x  = x + width - 3;
    bottom_y = y + height + 1;
    color    = *(volatile u16*)(((u8*)&D_80033A08) + (((*(s8*)&g_WindowStyle << 6) | 0x20)));
    r        = (color & 0x1F) << 3;
    g        = (color >> 2) & 0xF8;
    b        = (color >> 7) & 0xF8;

    func_801D9AB4(x, y, 8, 1);
    func_801D9AB4(x, y + height + 2, 9, 1);
    func_801DA5A8(x + 2, top_y, right_x, top_y, r, g, b);
    func_801DA5A8(x + 2, y + 3, x + 2, bottom_y, r, g, b);
    func_801DA4B4(right_x, top_y, right_x, bottom_y, r, g, b);
    func_801DA4B4(x + 2, bottom_y, right_x, bottom_y, r, g, b);
}
#else
INCLUDE_ASM(func_801F039C);
#endif
