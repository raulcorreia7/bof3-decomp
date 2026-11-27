#include "area030_04.h"

/* Fills area palette entries 1-30 from the selected CLUT block,
 * marks them opaque, resets palette state, initializes scratchpad values,
 * and advances the work state before calling func_8014D4E0. */
MATCH void func_801D130C(void) {
    s32           i;
    u8*           selected;
    u16*          dst;
    u32           palette;
    u32           row;
    u32           offset;
    u8            entry;
    u16           color;
    FishingState* state_work;

    i        = 1;
    selected = &g_Game.members[0].unk_27;
    palette  = AREA_PALETTE_WORK;
    dst      = MEM_PTR(u16, 0x80039602u);
    do {
        entry  = *selected;
        offset = i * 2;
        row    = ((entry >> 3) << 9) + palette;
        color  = *(u16*)(offset + (((entry & 0x7) << 6) + row));
        i += 1;
        dst[96] = color | PSX_COLOR_STP_BIT;
        dst += 1;
    } while (i < 31);

    D_800396C0                      = 0;
    D_800396FE                      = 0;
    SELF(FishingState)->saved_index = SELF(FishingState)->saved_value_27;
    SELF(FishingState)->flags |= ACTOR_FLAG_SEMI_TRANSPARENT;
    SELF(FishingState)->saved_value_27 = 0x7B;
    SELF(FishingState)->unk_5C         = 1;
    SELF(FishingState)->tint_5D        = -0x40;
    SELF(FishingState)->tint_5E        = -0x40;
    SELF(FishingState)->tint_5F        = -0x40;
    state_work                         = SELF(FishingState);
    g_GfxPalettePending                = 1;
    state_work->sub_index              = (state_work->sub_index + 1);
    Area_AddActor();
}
