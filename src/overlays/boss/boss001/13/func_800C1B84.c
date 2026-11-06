#include "boss001_13.h"

MATCH void func_800C1B84(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C2194, func_800C1E00, D_800C21B4);
    g_Task->header.mode = 2;
    func_8014D978();
}
