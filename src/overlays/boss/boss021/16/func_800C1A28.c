#include "boss021_16.h"

MATCH void func_800C1A28(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C1CBC, func_800C1A80, D_800C1CD0);
    ACTOR_SET_MODE(2);
    func_8014D978();
}
