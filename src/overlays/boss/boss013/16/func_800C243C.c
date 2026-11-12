#include "boss013_16.h"

MATCH void func_800C243C(void) {
    if (!(g_Battle.outcome.result & BATTLE_RESULT_VICTORY)) {
        if (!(g_Battle.boss_flags & 0x1)) {
            func_800AC844(2);
            TASK_SET(func_800AC754(2));
            Area_FindSceneRecord(0xF9);
            g_Task->unk_24 &= 0xFE;
            if (g_Battle.boss_flags & 0x40) {
                Actor_SelectScript(1);
            } else {
                Actor_BeginScript(5, 4);
            }
            g_Task->unk_2A = 1;
        }
        func_800AC844(1);
        TASK_SET(func_800AC754(1));
        Area_FindSceneRecord(0xEF);
        Actor_SelectScript(0);
        g_Task->unk_58 = g_BattleEnemyBattlers[1].unk_58;
        g_Task->unk_5A = g_BattleEnemyBattlers[1].unk_5A;
        func_800AC844(0);
        TASK_SET(func_800AC754(0));
        Area_FindSceneRecord(0xEE);
        Actor_SelectScript(0);
        g_Task->unk_58 = g_BattleEnemyBattlers[0].unk_58;
        g_Task->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
    }
    func_801C1DF0(1);
    g_Game.members[1].header.flags |= 0x40;
    if (*g_ScriptVars == 0x14) {
        g_Game.battle_order = 6;
    } else {
        g_Game.battle_order = 7;
    }
}
