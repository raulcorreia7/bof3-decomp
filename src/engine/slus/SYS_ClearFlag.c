#include "engine/slus/slus.h"

/* clears bit bit_index in the byte array at bits.
 */
MATCH void SYS_ClearFlag(void* bits, u8 bit_index) {
    u8* p;

    p = (u8*)bits + ((bit_index & BYTE_MASK) >> 3);
    *p &= ~(1 << (bit_index & 7));
}
