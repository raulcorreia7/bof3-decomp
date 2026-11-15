#include "boss036_16.h"

MATCH void func_800C1980(void) {
    PartyMember* work;

    if (--g_Task->unk_09 == 0) {
        Battle_PlayEnemyCue(*g_BattleCurrentEnemy->unk_E8);
    }
    g_Task->pos.x.fixed += g_Task->unk_0C;
    if (g_Task->pos.x.fixed == g_Task->unk_18) {
        Battle_MarkDamaged(g_Battle.target_selector);
        Battle_TriggerCritical();
        work = g_Task;
        work->header.mode++;
        work->unk_18 -= 0x30000;
        g_Task->header.step = 0;
    }
    Battle_IsEnemyBlocked();
}
