#include "engine/slus/slus.h"

/* Adds delta to *value unless already 999, clamps at 999.
 */
MATCH s32 Char_AddCappedStat(u16* value, s32 delta) {
    u16 cur;
    u16 next;

    cur = *value;
    if ((cur & 0xFFFF) == 0x3E7) {
        return 0;
    }
    next   = (cur + delta);
    *value = next;
    if ((next & 0xFFFF) >= 0x3E8U) {
        *value = 0x3E7;
    }
    return 1;
}
