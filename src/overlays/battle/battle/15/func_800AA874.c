#include "battle_15.h"

/* Whether the party has already learned the ability `bit_index` (its bit in g_LearnedAbilities). */
MATCH u32 func_800AA874(u32 bit_index) {
    u32 word;
    u32 bit;
    u32 off;

    bit_index &= BYTE_MASK;
    off  = (bit_index >> 5) * 4U;
    bit  = 1U << (bit_index & 0x1F);
    word = *(u32*)((u8*)g_LearnedAbilities + off);
    return ((word & bit) != 0);
}
