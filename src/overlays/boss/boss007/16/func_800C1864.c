#include "boss007_16.h"

MATCH void func_800C1864(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C1D78, func_800C18BC, D_800C1D90);
    ACTOR_SET_MODE(2);
    func_8014D978();
}
