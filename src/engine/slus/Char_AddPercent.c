#include "engine/slus/slus.h"

/* moves the 8-bit record value toward its 100/0 bounds by delta,
 * clamping at the crossed bound; a value already at 100 stays put.
 */
MATCH u32 Char_AddPercent(u8* value, u8 delta) {
    u8 cur;

    cur = *value;
    if ((cur & BYTE_MASK) == 0x64) {
        return 0;
    }
    cur    = (u8)(cur + (s8)delta);
    *value = cur;
    if ((s8)cur < 0) {
        *value = 0;
    }
    if ((u32)*value < 0x65U) {
        return 1;
    }
    *value = 0x64;
    return 1;
}
