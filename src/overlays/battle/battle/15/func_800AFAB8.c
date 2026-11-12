#include "battle_15.h"

MATCH void func_800AFAB8(u8* record) {
    u8 slot;
    /* FAKE: retail keeps the frame index in v1. */
    FAKE_REG(u32, index, "v1");
    /* FAKE: retail keeps the divisor in v0. */
    FAKE_REG(u32, divisor, "v0");
    /* FAKE: retail keeps the quotient in a3. */
    FAKE_REG(u32, quotient, "a3");
    u8            flags;
    u8            scale;
    u32           remainder;
    u32           row;
    s32           product;
    volatile u16* clut;

    slot      = record[0x28];
    index     = record[0x27];
    divisor   = s_BattleCellRowDivisor[slot];
    quotient  = index / divisor;
    remainder = index % divisor;
    flags     = record[0x24];
    scale     = s_BattleCellRowScale[slot];
    product   = scale * remainder;
    row       = quotient;
    if (flags & 0x4) {
        row = quotient + 0x10;
    }
    clut                               = g_GraphicsPaletteDst + ((row & BYTE_MASK) << 8);
    clut[(product & BYTE_MASK) + 0x1F] = 0;
    g_GfxPalettePending                = 1;
}
