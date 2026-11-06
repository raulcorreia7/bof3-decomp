#include "engine/slus/slus.h"

/* returns the 1-based index of the first set bit in the low nine bits of the
 * 0x14-stride D_801CA71C entry, or 0 when none is set.
 */
MATCH s32 Char_GetAbilityElement(s32 ability_id) {
    s32 flags;
    u32 mask;
    u8  index;
    u16 result;

    flags = (&D_801CA71C)[(ability_id & BYTE_MASK) * 0xA];
    if ((flags & 0x1FF) == 0) {
        return 0;
    }
    mask  = 1;
    index = 1;
    for (;;) {
        if (flags & mask) {
            return index;
        }
        index += 1;
        if (index >= 10) {
            break;
        }
        mask <<= 1;
    }
    result = index;
    return result;
}
