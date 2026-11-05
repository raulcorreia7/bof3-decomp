#include "boss028_16.h"

MATCH void func_800C1848(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C2140, func_800C1AF0, D_800C214C);
    ACTOR_SET_STEP(2);
    func_8014D978();
}
