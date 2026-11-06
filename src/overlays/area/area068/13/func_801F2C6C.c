#include "area068_13.h"

MATCH void func_801F2C6C(void) {
    Actor* temp_s0;

    temp_s0 = g_Task;
    if (D_80146865 != 0) {
        g_GameState = (GameState*)g_BattlePartyBattlers;
        TASK_SET(g_BattlePartyBattlers);
        D_80145FA8 |= 0x40;
        Actor_SelectScript(0x6FU);
        g_Task = temp_s0;
        g_BattlePartyBattlers[0].unk_07 &= 0x11;
        temp_s0->mode = 2;
    }
}
