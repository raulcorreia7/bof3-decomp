#include "area030_04.h"

/* Decays the three AREA030 scratch bytes by 0x10 and, once the first
 * one wraps to -0x80, clears them and the scratch flags before advancing the
 * scratch state byte; any other value defers to the AREA030 handler. */
MATCH void func_801D1434(void) {
    SELF(FishingState)->tint_5D -= 0x10;
    SELF(FishingState)->tint_5E -= 0x10;
    SELF(FishingState)->tint_5F -= 0x10;

    if (SELF(FishingState)->tint_5D == -0x80) {
        SELF(FishingState)->tint_5D = 0;
        SELF(FishingState)->tint_5E = 0;
        SELF(FishingState)->tint_5F = 0;
        SELF(FishingState)->flags &= ~ACTOR_FLAG_SEMI_TRANSPARENT;
        SELF(FishingState)->saved_value_27 = SELF(FishingState)->saved_index;
        SELF(FishingState)->sub_index++;
    } else {
        func_801D11C0();
    }
}
