#include "boss004_13.h"

MATCH void Boss_EndBattle2(void) {
    if (g_Battle.outcome.result & BATTLE_RESULT_DEFEAT) {
        Battle_ShowActorEntry(2);
        Battle_ShowActorEntry(3);
        return;
    }
    Battle_ShowActorEntry(2);
    Battle_CopyActorEntry(2, (PartyMember*)g_BattleEnemyBattlers, 1);
    TASK_SET(func_800AC754(2));
    Area_SelectSceneRecord(0x5F);
    g_Task->unk_48 = 0;
    g_Task->unk_2A = 0;
    Actor_SelectScript(1);
    g_Task->unk_58 = g_BattleEnemyBattlers[0].unk_58;
    g_Task->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
    Battle_ShowActorEntry(3);
    Battle_CopyActorEntry(3, (PartyMember*)&g_BattleEnemyBattlers[1], 1);
    TASK_SET(func_800AC754(3));
    Area_SelectSceneRecord(0x5F);
    g_Task->unk_48 = 0;
    g_Task->unk_2A = 0;
    Actor_SelectScript(1);
    g_Task->unk_58 = g_BattleEnemyBattlers[1].unk_58;
    g_Task->unk_5A = g_BattleEnemyBattlers[1].unk_5A;
}
