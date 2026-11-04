#include "boss002_16.h"

MATCH void Boss_ChooseBattleEnding2(void) {
    if (FIELD(u32, &g_BattleResult, 0) & 6) {
        func_800AC870(0, (PartyBattler*)D_801EB630, 0);
        g_ScriptVars[0] = 0x6D;
        g_SndBgmId      = 0x18;
        func_801DDED8();
    } else {
        func_801DDF00();
    }
}
