#include "boss013_16.h"

MATCH void func_800C1860(void) {
    g_BattleCurrentEnemy->script = &D_800C25D8;
    g_BattleCurrentEnemy->unk_E4 = func_800C18FC;
    g_BattleCurrentEnemy->unk_E8 = &D_800C2608;
    g_Task->header.mode          = 2;
    if (g_Battle.encounter == 0xD) {
        g_BattleCurrentEnemy->base.max_hp  = 0xFFFF;
        g_BattleCurrentEnemy->stats.max_hp = 0xFFFF;
        g_BattleCurrentEnemy->hp           = 65535;
    }
    Area_SelectSceneRecord(0xEE);
    Actor_SelectScript(0U);
    g_Task->unk_2A = 1;
}
