#include "boss034_16.h"

MATCH void func_800C1860(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C26B8, func_800C1D60, D_800C26C4);
    ACTOR_SET_MODE(2);
    func_8014D978();
}
