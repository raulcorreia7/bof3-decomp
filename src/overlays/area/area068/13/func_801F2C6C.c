#include "area068_13.h"

MATCH void func_801F2C6C(void) {
    Actor* temp_s0;

    temp_s0 = g_SpadWork;
    if (D_80146865 != 0) {
        g_GameState = (GameStateRecord*)g_BattlePartyBattlers;
        g_SpadWork  = (Actor*)g_BattlePartyBattlers;
        D_80145FA8 |= 0x40;
        Actor_SelectScript(0x6FU);
        g_SpadWork = temp_s0;
        D_80145E97 &= 0x11;
        temp_s0->unk_01 = 2;
    }
}
