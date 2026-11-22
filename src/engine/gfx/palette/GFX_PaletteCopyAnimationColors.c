#include "engine/game/00/game_00.h"

MATCH void GFX_PaletteCopyAnimationColors(GraphicsPaletteAnimation* slot) {
    GraphicsPaletteAnimation* slot_copy;
    Actor*                    owner;
    PaletteAnimationStep*     entry;
    volatile u16*             base;
    u32                       index;
    u32                       stride;
    /* FAKE: retail keeps the dividend in v1. */
    FAKE_REG(u32, value, "v1");
    /* FAKE: retail keeps the divisor in v0. */
    FAKE_REG(u32, divisor, "v0");
    /* FAKE: retail keeps the quotient in t0. */
    FAKE_REG(u32, quotient, "t0");
    u32 remainder;
    u32 flags;
    u32 product;
    u32 dst;
    u32 start;
    u32 src;
    u32 i;

    slot_copy = slot;
    owner     = (Actor*)slot_copy->owner;
    index     = owner->palette_8bit;
    value     = slot_copy->unk_03;
    divisor   = s_PaletteSlotDivisors[index];
    quotient  = value / divisor;
    remainder = value % divisor;
    flags     = owner->active_flags;
    stride    = s_PaletteSlotStrides[index];
    product   = stride * remainder;
    entry     = slot_copy->current_entry;
    dst       = entry->dst_column + product;
    src       = entry->src_column + product;
    if ((flags & 0x4u) != 0u) {
        start = quotient + 0x10u;
    } else {
        start = quotient;
    }
    i = 0u;
    if (entry->count != 0u) {
        base = g_GraphicsPaletteDst + ((start & BYTE_MASK) << 8);
        do {
            base[(dst & BYTE_MASK) + (i & BYTE_MASK)] = base[(src & BYTE_MASK) + (i & BYTE_MASK)];
            i++;
        } while ((i & BYTE_MASK) < slot_copy->current_entry->count);
    }
    g_GfxPalettePending = 1u;
}
