#include "battle_15.h"

/* Sets the bit at bit_index in the D_80144F60 bitmask. */
MATCH void func_800AD074(u32 bit_index) {
    u32  word_index;
    u32* bit_words;

    bit_index &= HALF_MASK;
    word_index = bit_index >> 5;
    bit_words  = (u32*)D_80144F60;
    bit_words[word_index] |= (1U << (bit_index & 0x1F));
}
