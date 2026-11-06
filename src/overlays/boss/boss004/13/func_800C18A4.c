#include "boss004_13.h"

MATCH void func_800C18A4(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C2720, func_800C1BBC, D_800C2738);
    ACTOR_SET_MODE(2);
    func_8014D978();
}
