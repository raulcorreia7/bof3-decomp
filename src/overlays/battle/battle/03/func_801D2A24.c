#include "battle_03.h"

MATCH void func_801D2A24(void) {
    u16 count;

    if (EMI_IsReady() != 0) {
        if ((g_Battle.state & BATTLE_STATE_COMMAND_ARMED) == 0) {
            count      = D_801463B0;
            D_801463B0 = count - 1;
            if (count != 0) {
                return;
            }
        }
        D_801463B0          = 0;
        g_Battle.phase.step = 0;
        g_Battle.phase.mode += 1;
    }
}
