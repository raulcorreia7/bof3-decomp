#include "area030_04.h"

/* Fills the area's 32-entry CLUT working copy from the palette
 * block selected by g_Game.members[0].unk_27: entries 1-30 come from the selected 0x200-byte
 * block plus the selected 0x40-byte unit, marked opaque, and entries 0 and 31
 * are cleared. It then publishes the palette serial and either selects the
 * late stage (g_AreaTargetCellY >= 0x39) or seeds the panel bytes before stepping the
 * scratchpad state byte 0x03. */
MATCH void func_801D0F5C(void) {
    u8* selected;
    u8* dst;
    u32 palette;
    u32 row;
    u32 offset;
    u8  entry;
    u16 color;
    s32 i;

    i        = 1;
    selected = &g_Game.members[0].unk_27;
    palette  = AREA_PALETTE_WORK;
    dst      = MEM_PTR(u8, 0x80039602u);
    do {
        entry  = *selected;
        offset = i * 2;
        row    = ((entry >> 3) << 9) + palette;
        color  = *(u16*)(offset + (((entry & 0x7) << 6) + row));
        i += 1;
        *(u16*)(dst + 0xC0) = color | 0x8000;
        dst += 2;
    } while (i < 31);

    D_800396C0            = 0;
    D_800396FE            = 0;
    g_GfxPalettePending   = 1;
    FISHING_STATE->unk_5C = 1;

    if (g_AreaTargetCellY >= 0x39) {
        FISHING_STATE->mode_index_02 = 3;
        FISHING_STATE->sub_index_03  = 2;
    } else {
        FISHING_STATE->saved_index_0B = FISHING_STATE->saved_value_27;
        FISHING_STATE->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        FISHING_STATE->saved_value_27 = 0x7B;
        FISHING_STATE->tint_5D        = -0x80;
        FISHING_STATE->tint_5E        = -0x80;
        FISHING_STATE->tint_5F        = -0x80;
        FISHING_STATE->sub_index_03   = (FISHING_STATE->sub_index_03 + 1);
    }
}
