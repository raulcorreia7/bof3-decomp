#include "boss034_16.h"

MATCH void func_800C22D0(void) {
    func_800AC844(0);
    TASK_SET(func_800AC754(0));
    Area_SelectSceneRecord(0x1C1);
    Actor_SelectScript(8);
    g_Task->unk_2A = 1;
    g_Task->unk_58 = g_BattleEnemyBattlers[0].unk_58;
    g_Task->unk_5A = g_BattleEnemyBattlers[0].unk_5A;
}
