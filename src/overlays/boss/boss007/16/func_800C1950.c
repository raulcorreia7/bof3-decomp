#include "boss007_16.h"

MATCH void func_800C1950(void) {
    EnemyBattler* work;
    u8*           spad;

    work = g_BattleCurrentEnemy;
    spad = TASK_BYTES;
    EnemyBattler_SetScript(work, D_800C1D84, func_800C19B4, D_800C1D98);
    spad[8] = 0;
    ACTOR_SET_STEP(2);
    func_8014D978();
}
