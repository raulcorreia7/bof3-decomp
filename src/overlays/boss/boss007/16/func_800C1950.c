#include "boss007_16.h"
#include "area/spad.h"

MATCH void func_800C1950(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    EnemyBattler_SetScript(work, D_800C1D84, func_800C19B4, D_800C1D98);
    g_Task->direction_08 = 0;
    ACTOR_SET_MODE(2);
    func_8014D978();
}
