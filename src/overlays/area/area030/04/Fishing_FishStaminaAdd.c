#include "area030_04.h"

/* Adds the signed delta to the halfword at work+0x8E, then clamps
 * the result into [0, work+0x8C]. */
/* func_801E026C */
MATCH void Fishing_FishStaminaAdd(s8 delta) {
    Actor* work;
    s32    value;
    s16    max;
    u16    result;

    value                            = FISHING_ROW->ext.fishing.stamina + delta;
    FISHING_ROW->ext.fishing.stamina = value;
    work                             = FISHING_ROW;
    result                           = work->ext.fishing.stamina;
    if ((s16)value >= 0) {
        max = work->ext.fishing.stamina_max;
        if (max < (s16)value) {
            result = max;
        }
    } else {
        /* FAKE: the order lock steers regalloc */
        FAKE_ORDER_LOCK_BEGIN
            result = 0;
        FAKE_ORDER_LOCK_END;
    }
    work->ext.fishing.stamina = result;
}
