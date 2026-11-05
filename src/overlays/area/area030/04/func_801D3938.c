#include "area030_04.h"

/* Advances the local scratch vertical offset and routes the next
 * AREA030 panel draw through the later helper at `0x801D9534`. */
MATCH void func_801D3938(void) {
    s32 val;

    val                        = FISHING_STATE->origin_y_30 - 8;
    FISHING_STATE->origin_y_30 = (u16)val;

    if ((s16)val < -0x19) {
        if (FISHING_STATE->counter_07 != 0u) {
            FISHING_STATE->handler_index_01 = 1u;
        } else {
            FISHING_STATE->handler_index_01 = 0u;
        }
    }

    func_801D9534(0x14, FISHING_STATE->origin_y_30, 0x118, 0x13, 0);
}
