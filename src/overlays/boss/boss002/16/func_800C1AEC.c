#include "boss002_16.h"

MATCH void func_800C1AEC(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C1F9C, func_800C1C08, D_800C1FAC);
    ACTOR_SET_STEP(2);
    func_8014D978();
}
