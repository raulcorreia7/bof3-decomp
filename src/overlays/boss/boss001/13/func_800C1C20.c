#include "boss001_13.h"

MATCH void func_800C1C20(void) {
    EnemyBattler* work;

    func_8014DAEC();
    func_801E54EC();
    work = g_BattleCurrentEnemy;
    work->flags_100 |= 0x1000;
    g_SpadWork->flags_00 &= 0xBF;
    g_SpadWork->step_01 = 3;
    g_SpadWork->unk_02  = 0;
    g_SpadWork->unk_03  = 0;
}
