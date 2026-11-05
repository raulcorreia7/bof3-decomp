#include "boss030_16.h"

MATCH void func_800C1848(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C1AB4, func_800C18A0, D_800C1ACC);
    ACTOR_SET_STEP(2);
    func_8014D978();
}
