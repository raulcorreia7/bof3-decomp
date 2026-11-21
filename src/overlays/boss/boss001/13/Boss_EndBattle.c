#include "boss001_13.h"

MATCH void Boss_EndBattle(void) {
    Battle_ShowActorEntry(6);
    Battle_CopyActorEntry(6, (PartyMember*)g_BattleEnemyBattlers, 1);
    TASK_SET(func_800AC754(6));
    Area_SelectSceneRecord(0x5F);
    g_Task->unk_2A = 0;
    g_Task->unk_48 = 0;
    Script_Select(1);
    g_Task->unk_58 = g_BattleEnemyBattlers[0].unk_58;
    g_Task->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
    Battle_ShowActorEntry(7);
    Battle_CopyActorEntry(7, (PartyMember*)&g_BattleEnemyBattlers[1], 1);
    TASK_SET(func_800AC754(7));
    Area_SelectSceneRecord(0x5F);
    g_Task->unk_2A = 0;
    g_Task->unk_48 = 0;
    Script_Select(0);
    g_Task->unk_58 = g_BattleEnemyBattlers[1].unk_58;
    g_Task->unk_5A = g_BattleEnemyBattlers[1].unk_5A;
}
