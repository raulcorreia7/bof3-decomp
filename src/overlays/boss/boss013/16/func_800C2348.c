#include "boss013_16.h"

MATCH void func_800C2348(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_VICTORY) {
        *g_ScriptVars               = 0x14;
        g_Battle.outcome.reward_exp = ENEMY_COMBATANT(3).exp + ENEMY_COMBATANT(4).exp;
        Battle_EndVictory();
    } else {
        if (g_Battle.boss_flags & 0x40) {
            g_Self = &D_801EB860;
            Area_SceneSelectRecord(0xF9);
            SELF(PartyMember)->unk_24 &= 0xFE;
            SELF(PartyMember)->unk_2A = 1;
            Script_Select(1U);
        }
        *g_ScriptVars = 0x50;
        Battle_EndToArea();
    }
    g_SndBGMId = 0x31;
    g_GameFlags &= 0xFF7F;
}
