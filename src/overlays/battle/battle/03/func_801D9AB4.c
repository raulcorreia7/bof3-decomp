#include "battle_03.h"

MATCH void func_801D9AB4(s16 x, s16 y, s32 shape_index, s32 shade) {
    POLY_F4* prim;
    s8*      selector;

    prim = (POLY_F4*)g_GfxPrimCursor;
    SetPolyF4(prim);
    shape_index = (shape_index & BYTE_MASK) * 0x10;
    setXY4(prim, x + *(s16*)((u8*)&D_801EAD30 + shape_index), y + *(s16*)((u8*)&D_801EAD30 + shape_index + 2),
           x + *(s16*)((u8*)&D_801EAD30 + shape_index + 4), y + *(s16*)((u8*)&D_801EAD30 + shape_index + 6),
           x + *(s16*)((u8*)&D_801EAD30 + shape_index + 8), y + *(s16*)((u8*)&D_801EAD30 + shape_index + 0xA),
           x + *(s16*)((u8*)&D_801EAD30 + shape_index + 0xC), y + *(s16*)((u8*)&D_801EAD30 + shape_index + 0xE));
    shade &= BYTE_MASK;
    selector = &g_WindowStyle;
    /* A halfword read: the palette entry's low five bits are one channel. */
    setRGB0(prim, PSX_COLOR_R(*(volatile u16*)(MEM_PTR(u8, 0x80033A08u) + (((*selector * 2) + shade) << 5))) << 3,
            PSX_COLOR_G(*(volatile u16*)(MEM_PTR(u8, 0x80033A08u) + (((*selector * 2) + shade) << 5))) << 3,
            PSX_COLOR_B(*(volatile u16*)(MEM_PTR(u8, 0x80033A08u) + (((*selector * 2) + shade) << 5))) << 3);
    SetSemiTrans(prim, shade);
    GFX_AddPrim(1, sizeof(POLY_F4));
}
