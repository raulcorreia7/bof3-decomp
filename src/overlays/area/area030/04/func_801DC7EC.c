#include "area030_04.h"

/* When halfword `g_UiWindowEffectBusy` is clear, initializes the scratchpad
 * work object: byte 0x02 = 1, byte 0x03 = 0, byte 0x04 = 0. */
MATCH void func_801DC7EC(void) {
    if (WINDOW_EFFECT_IDLE()) {
        SELF(FishingState)->mode_index = 1;
        SELF(FishingState)->sub_index  = 0;
        SELF(FishingState)->flag_04    = 0;
    }
}
