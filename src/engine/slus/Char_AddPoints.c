#include "engine/slus/slus.h"

/* steps *value toward limit by delta, clamping upward at limit and
 * downward at zero.
 */
MATCH s16 Char_AddPoints(u16* value, u16 limit, s16 delta) {
    u16 cur;
    u16 next;

    cur = *value;
    if (delta > 0) {
        if (cur == limit)
            return 0;
        next   = (u16)(cur + delta);
        *value = next;
        if (limit < next) {
            *value = limit;
            return (s16)(limit - cur);
        }
        return delta;
    }
    if (delta < 0) {
        if (cur == 0)
            return 0;
        next   = (u16)(cur + delta);
        *value = next;
        if ((s16)next < 0) {
            *value = 0;
            return (s16)(0 - cur);
        }
        return delta;
    }
    return 0;
}
