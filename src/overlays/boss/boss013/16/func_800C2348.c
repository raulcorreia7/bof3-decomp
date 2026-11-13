#include "boss013_16.h"

MATCH void func_800C2348(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_VICTORY) {
        *g_ScriptVars               = 0x14;
        g_Battle.outcome.reward_exp = ENEMY_COMBATANT(3).exp + ENEMY_COMBATANT(4).exp;
        func_801DDED8();
    } else {
        if (g_Battle.boss_flags & 0x40) {
            g_Task = &D_801EB860;
            Area_SelectSceneRecord(0xF9);
            g_Task->unk_24 &= 0xFE;
            g_Task->unk_2A = 1;
            Actor_SelectScript(1U);
        }
        *g_ScriptVars = 0x50;
        func_801DDF28();
    }
    g_SndBGMId = 0x31;
    g_GameFlags &= 0xFF7F;
}
