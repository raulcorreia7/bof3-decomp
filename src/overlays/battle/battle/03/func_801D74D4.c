#include "battle_03.h"

MATCH void func_801D74D4(void) {
    volatile u8* counter;
    u8           value;

    if (WINDOW_EFFECT_IDLE()) {
        counter         = &g_Battle.phase.sub_step;
        value           = *counter;
        g_AreaDrawFlags = 0;
        *counter        = value - 1;
    }
}
