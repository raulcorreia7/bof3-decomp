#include "engine/slus/slus.h"

/* Adds delta to *value unless already 99, clamps at 99.
 * delta is unsigned: a decrement is not representable in this path, so a
 * negative delta would wrap to a large byte and clamp to 99.
 */
MATCH s32 Char_AddWillpower(u8* value, u16 delta) {
    u8 cur;
    u8 next;

    cur = *value;
    if ((cur & BYTE_MASK) == 0x63) {
        return 0;
    }
    next   = (u8)(cur + delta);
    *value = next;
    if ((u32)(next & BYTE_MASK) >= 0x64U) {
        *value = 0x63;
    }
    return 1;
}
