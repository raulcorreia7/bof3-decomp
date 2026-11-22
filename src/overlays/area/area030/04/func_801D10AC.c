#include "area030_04.h"

/* Grows the three AREA030 scratch bytes by 0x10 and, once the first
 * one reaches -0x40, clears them and the scratch flags before stepping the
 * scratch state, then defers to the AREA030 handler. */
MATCH void func_801D10AC(void) {
    TASK(FishingState)->tint_5D += 0x10;
    TASK(FishingState)->tint_5E += 0x10;
    TASK(FishingState)->tint_5F += 0x10;

    if (TASK(FishingState)->tint_5D >= -0x40) {
        TASK(FishingState)->tint_5D = 0;
        TASK(FishingState)->tint_5E = 0;
        TASK(FishingState)->tint_5F = 0;
        TASK(FishingState)->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        TASK(FishingState)->saved_value_27 = TASK(FishingState)->saved_index;
        TASK(FishingState)->sub_index      = 0;
        TASK(FishingState)->mode_index++;
    }
    func_801D11C0();
}
