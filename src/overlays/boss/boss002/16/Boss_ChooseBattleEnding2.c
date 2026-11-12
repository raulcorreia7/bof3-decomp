#include "boss002_16.h"

MATCH void Boss_ChooseBattleEnding2(void) {
    if (FIELD(u32, &g_Battle.outcome.result, 0x0) & 0x6) {
        func_800AC870(0, (PartyMember*)g_BattleEnemyBattlers, 0);
        g_ScriptVars[0] = 0x6D;
        g_SndBGMId      = 0x18;
        func_801DDED8();
    } else {
        func_801DDF00();
    }
}
