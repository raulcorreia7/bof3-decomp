#include "area030_04.h"

/* Adds the signed delta to the halfword at work+0x8E, then clamps
 * the result into [0, work+0x8C]. */
MATCH void func_801E026C(s8 delta) {
    Actor* work;
    s32    value;
    s16    max;
    u16    result;

    value                   = FISHING_ROW->stamina_8E + delta;
    FISHING_ROW->stamina_8E = value;
    work                    = FISHING_ROW;
    result                  = work->stamina_8E;
    if ((s16)value >= 0) {
        max = work->stamina_max_8C;
        if (max < (s16)value) {
            result = max;
        }
    } else {
        /* FAKE: the order lock steers regalloc */
        ORDER_LOCK_BEGIN
            result = 0;
        ORDER_LOCK_END;
    }
    work->stamina_8E = result;
}
