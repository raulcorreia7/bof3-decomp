#include "boss002_16.h"

MATCH void func_800C1848(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C1F9C, func_800C19C8, D_800C1FAC);
    ACTOR_SET_MODE(2);
    func_8014D978();
}
