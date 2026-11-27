#include "area030_04.h"

/* Returns 1 and arms the scratchpad work object (byte 0x02 = 8,
 * byte 0x03 = 0) after entering local mode 2 when mask `request` intersects the
 * state halfword `g_PadStates[0].pressed`; returns 0 otherwise. */
MATCH s32 func_801DDF7C(u16 request) {
    if ((g_PadStates[0].pressed & request) != 0) {
        UI_ModeSet(2);
        SELF(FishingState)->mode_index = 8;
        SELF(FishingState)->sub_index  = 0;
        return 1;
    }
    return 0;
}
