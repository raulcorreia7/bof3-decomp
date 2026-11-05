#include "boss021_16.h"

MATCH void func_800C1860(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C1CB0, func_800C198C, D_800C1CC8);
    ACTOR_SET_STEP(2);
    func_8014D978();
}
