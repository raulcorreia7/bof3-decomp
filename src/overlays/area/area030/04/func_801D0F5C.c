#include "area030_04.h"

/* Fills the area's 32-entry CLUT working copy from the palette
 * block selected by g_Game.members[0].clut_select: entries 1-30 come from the selected 0x200-byte
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
        *(u16*)(dst + 0xC0) = color | PSX_COLOR_STP_BIT;
        dst += 2;
    } while (i < 31);

    D_800396C0                 = 0;
    D_800396FE                 = 0;
    g_GfxPalettePending        = 1;
    SELF(FishingState)->unk_5C = 1;

    if (g_AreaCamera.scroll_y.part.integer >= 0x39) {
        SELF(FishingState)->mode_index = 3;
        SELF(FishingState)->sub_index  = 2;
    } else {
        SELF(FishingState)->saved_index = SELF(FishingState)->saved_value_27;
        SELF(FishingState)->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(FishingState)->saved_value_27 = 0x7B;
        SELF(FishingState)->tint_5D        = -0x80;
        SELF(FishingState)->tint_5E        = -0x80;
        SELF(FishingState)->tint_5F        = -0x80;
        SELF(FishingState)->sub_index      = (SELF(FishingState)->sub_index + 1);
    }
}
