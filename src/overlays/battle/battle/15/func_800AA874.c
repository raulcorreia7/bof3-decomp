#include "battle_15.h"

/* @tests a specific bit in the bitmask array at D_80144F80.
 * Extracts the bit index and tests it.
 */
MATCH u32 func_800AA874(u32 bit_index) {
    u32 word;
    u32 bit;
    u32 off;

    bit_index &= BYTE_MASK;
    off  = (bit_index >> 5) * 4U;
    bit  = 1U << (bit_index & 0x1F);
    word = *(u32*)((u8*)D_80144F80 + off);
    return ((word & bit) != 0);
}
