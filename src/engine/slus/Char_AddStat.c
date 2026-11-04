#include "engine/slus/slus.h"

/* moves the 16-bit record value toward its 999/0 bounds by delta,
 * clamping at the crossed bound and returning the remaining distance.
 */
MATCH s16 Char_AddStat(u16* value, s16 delta) {
    u16 cur;
    u16 next;
    s16 result;

    cur = *value;
    if (delta > 0) {
        if (cur != 0x3E7) {
            next   = (u16)(cur + delta);
            *value = next;
            if ((u32)next >= 0x3E8U) {
                *value = 0x3E7;
                result = 0x3E7 - cur;
                return result;
            }
        }
        return 0;
    }
    if (delta < 0) {
        if (cur != 0) {
            next   = (u16)(cur + delta);
            *value = next;
            if ((s16)next >= 0) {
                return 0;
            }
            *value = 0;
            result = -cur;
            return result;
        }
    }
    return 0;
}
