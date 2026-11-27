#include "boss013_16.h"

MATCH void func_800C243C(void) {
    if (!(g_Battle.outcome.result & BATTLE_RESULT_VICTORY)) {
        if (!(g_Battle.boss_flags & 0x1)) {
            Battle_ShowActorEntry(2);
            SELF_SET(func_800AC754(2));
            Area_SceneSelectRecord(0xF9);
            SELF(PartyMember)->unk_24 &= 0xFE;
            if (g_Battle.boss_flags & 0x40) {
                Script_Select(1);
            } else {
                Script_Begin(5, 4);
            }
            SELF(PartyMember)->unk_2A = 1;
        }
        Battle_ShowActorEntry(1);
        SELF_SET(func_800AC754(1));
        Area_SceneSelectRecord(0xEF);
        Script_Select(0);
        SELF(PartyMember)->unk_58 = g_BattleEnemyBattlers[1].unk_58;
        SELF(PartyMember)->unk_5A = g_BattleEnemyBattlers[1].unk_5A;
        Battle_ShowActorEntry(0);
        SELF_SET(func_800AC754(0));
        Area_SceneSelectRecord(0xEE);
        Script_Select(0);
        SELF(PartyMember)->unk_58 = g_BattleEnemyBattlers[0].unk_58;
        SELF(PartyMember)->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
    }
    Scene_RunScenario(1);
    g_Game.members[1].header.flags |= 0x40;
    if (*g_ScriptVars == 0x14) {
        g_Game.battle_order = 6;
    } else {
        g_Game.battle_order = 7;
    }
}
