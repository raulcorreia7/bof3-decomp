#include "boss004_13.h"

MATCH void Boss_EndBattle(void) {
    if (g_BattleOutcome.result & 1) {
        func_800AC844(0);
        func_800AC844(1);
        return;
    }
    func_800AC844(0);
    func_800AC870(0, (PartyBattler*)g_BattleEnemyBattlers, 1);
    TASK_SET(func_800AC754(0));
    Area_FindSceneRecord(0x5F);
    g_Task->unk_48 = 0;
    g_Task->unk_2A = 1;
    Actor_SelectScript(1);
    g_Task->unk_58 = g_BattleEnemyBattlers[0].unk_58;
    g_Task->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
    func_800AC844(1);
    func_800AC870(1, (PartyBattler*)&g_BattleEnemyBattlers[1], 1);
    TASK_SET(func_800AC754(1));
    Area_FindSceneRecord(0x5F);
    g_Task->unk_48 = 0;
    g_Task->unk_2A = 1;
    Actor_SelectScript(1);
    g_Task->unk_58 = g_BattleEnemyBattlers[1].unk_58;
    g_Task->unk_5A = g_BattleEnemyBattlers[1].unk_5A;
}
