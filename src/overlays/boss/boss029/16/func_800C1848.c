#include "boss029_16.h"

MATCH void func_800C1848(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C19A8, func_800C18A0, D_800C19B4);
    ACTOR_SET_MODE(2);
    func_8014D978();
}
