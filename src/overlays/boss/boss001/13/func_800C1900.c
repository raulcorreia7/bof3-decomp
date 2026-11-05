#include "boss001_13.h"

MATCH void func_800C1900(void) {
    EnemyBattler* work;

    func_8014DAEC();
    func_801E54EC();
    work = g_BattleCurrentEnemy;
    work->damage_flags |= 0x1000;
    g_Task->flags &= ~ACTOR_FLAG_HIDDEN;
    g_Task->mode   = 3;
    g_Task->step   = 0;
    g_Task->unk_03 = 0;
}
