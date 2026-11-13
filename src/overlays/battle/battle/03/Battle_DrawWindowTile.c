#include "battle_03.h"

/* func_801D9C80 */
MATCH void Battle_DrawWindowTile(s16 x, s16 y, u8 template_index, u8 shade) {
    TILE* tile;
    s8*   selector;

    tile = (TILE*)g_GfxPrimCursor;
    SetTile(tile);
    setXY0(tile, x, y);
    setWH(tile, D_801EAE50[template_index * 2], D_801EAE52[template_index * 2]);
    selector = &g_WindowStyle;
    setRGB0(tile, PSX_COLOR_R(*(volatile u16*)(MEM_PTR(u8, 0x80033A08u) + ((*selector * 2 + shade) << 5))) << 3,
            PSX_COLOR_G(*(volatile u16*)(MEM_PTR(u8, 0x80033A08u) + ((*selector * 2 + shade) << 5))) << 3,
            PSX_COLOR_B(*(volatile u16*)(MEM_PTR(u8, 0x80033A08u) + ((*selector * 2 + shade) << 5))) << 3);
    SetSemiTrans(tile, shade);
    GFX_AddPrim(1, sizeof(TILE));
}
