#include "boss024_16.h"

MATCH void func_800C1848(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C1B44, func_800C18A0, D_800C1B50);
    ACTOR_SET_STEP(2);
    func_8014D978();
}
