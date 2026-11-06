#include "area175_13.h"

MATCH s32 func_801F4528(u16 handler_x, u16 handler_y) {
    if (handler_x == 0x3F && handler_y == 0xE && g_BattlePartyBattlers[0].facing == 1) {
        if (g_SceneState.scenario_id >= 8) {
            D_801448EB = 0x1A;
        } else {
            D_801448EB = 6;
        }
        return 1;
    }
    return 0;
}
