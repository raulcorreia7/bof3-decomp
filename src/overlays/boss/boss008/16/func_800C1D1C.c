#include "boss008_16.h"

MATCH void func_800C1D1C(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C264C, func_800C1D74, D_800C2658);
    g_Task->mode = 2;
    func_8014D978();
}
