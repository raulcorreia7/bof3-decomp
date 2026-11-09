#include "area030_04.h"

/* Decays the three AREA030 scratch bytes by 0x10 and, once the first one wraps to -0x80, clears them and the scratch flags before advancing the scratch state byte. */
MATCH void func_801D1434(void) {
    FISHING_STATE->tint_5D -= 0x10;
    FISHING_STATE->tint_5E -= 0x10;
    FISHING_STATE->tint_5F -= 0x10;

    if (FISHING_STATE->tint_5D == -0x80) {
        FISHING_STATE->tint_5D = 0;
        FISHING_STATE->tint_5E = 0;
        FISHING_STATE->tint_5F = 0;
        FISHING_STATE->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        FISHING_STATE->saved_value_27 = FISHING_STATE->saved_index_0B;
        FISHING_STATE->sub_index_03++;
    } else {
        func_801D11C0();
    }
}
