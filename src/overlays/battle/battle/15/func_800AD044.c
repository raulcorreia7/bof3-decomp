#include "battle_15.h"

/* @tests a specific bit in the bitmask array at D_80144F60.
 * Uses bit_index & 0xFFFF for index calculation.
 */
MATCH u32 func_800AD044(u32 bit_index) {
    u32 byte_offset;
    u32 bit_mask;
    u32 flags;

    bit_index &= HALF_MASK;
    byte_offset = bit_index >> 5;
    byte_offset <<= 2;
    bit_mask = 1U << (bit_index & 0x1F);
    flags    = *(u32*)(((u8*)D_80144F60 + byte_offset));
    return (flags & bit_mask) != 0;
}
