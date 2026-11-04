#include "boss013_16.h"

MATCH void func_800C2348(void) {
    if (g_BattleResult & 2) {
        *g_ScriptVars = 0x14;
        D_8014632C    = D_801EB6B6 + D_801EB7CE;
        func_801DDED8();
    } else {
        if (g_BattleBossFlags & 0x40) {
            ((PartyBattler*)g_SpadWork) = &D_801EB860;
            Area_FindSceneRecord(0xF9);
            ((PartyBattler*)g_SpadWork)->unk_24 &= 0xFE;
            ((PartyBattler*)g_SpadWork)->unk_2A = 1;
            Actor_SelectScript(1U);
        }
        *g_ScriptVars = 0x50;
        func_801DDF28();
    }
    g_SndBgmId = 0x31;
    g_GameFlags &= 0xFF7F;
}
