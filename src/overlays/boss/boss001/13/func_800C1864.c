#include "boss001_13.h"

MATCH void func_800C1864(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C217C, func_800C1AF0, D_800C21AC);
    g_Task->mode = 2;
    func_8014D978();
}
