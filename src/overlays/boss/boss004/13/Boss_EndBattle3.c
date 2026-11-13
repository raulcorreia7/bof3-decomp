#include "boss004_13.h"

MATCH void Boss_EndBattle3(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) {
        func_800AC844(4);
        func_800AC844(5);
        return;
    }
    func_800AC844(4);
    func_800AC870(4, (PartyMember*)g_BattleEnemyBattlers, 1);
    TASK_SET(func_800AC754(4));
    Area_SelectSceneRecord(0x5F);
    g_Task->unk_48 = 0;
    g_Task->unk_2A = 1;
    Actor_SelectScript(1);
    g_Task->unk_58 = g_BattleEnemyBattlers[0].unk_58;
    g_Task->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
    func_800AC844(5);
    func_800AC870(5, (PartyMember*)&g_BattleEnemyBattlers[1], 1);
    TASK_SET(func_800AC754(5));
    Area_SelectSceneRecord(0x5F);
    g_Task->unk_48 = 0;
    g_Task->unk_2A = 1;
    Actor_SelectScript(1);
    g_Task->unk_58      = g_BattleEnemyBattlers[1].unk_58;
    g_Task->unk_5A      = g_BattleEnemyBattlers[1].unk_5A;
    g_Task->pos.x.fixed = g_BattleEnemyBattlers[1].pos.x.fixed;
    g_Task->pos.y.fixed = g_BattleEnemyBattlers[1].pos.y.fixed;
    g_Task->pos.z.fixed = g_BattleEnemyBattlers[1].pos.z.fixed;
}
