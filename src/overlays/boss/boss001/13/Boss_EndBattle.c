#include "boss001_13.h"

MATCH void Boss_EndBattle(void) {
    func_800AC844(6);
    func_800AC870(6, (PartyMember*)g_BattleEnemyBattlers, 1);
    TASK_SET(func_800AC754(6));
    Area_SelectSceneRecord(0x5F);
    g_Task->unk_2A = 0;
    g_Task->unk_48 = 0;
    Actor_SelectScript(1);
    g_Task->unk_58 = g_BattleEnemyBattlers[0].unk_58;
    g_Task->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
    func_800AC844(7);
    func_800AC870(7, (PartyMember*)&g_BattleEnemyBattlers[1], 1);
    TASK_SET(func_800AC754(7));
    Area_SelectSceneRecord(0x5F);
    g_Task->unk_2A = 0;
    g_Task->unk_48 = 0;
    Actor_SelectScript(0);
    g_Task->unk_58 = g_BattleEnemyBattlers[1].unk_58;
    g_Task->unk_5A = g_BattleEnemyBattlers[1].unk_5A;
}
