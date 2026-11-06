#include "boss055_16.h"

MATCH void func_800C26D4(void) {
    u8* work = TASK_BYTES;

    g_BattleCurrentEnemy = g_BattleEnemyBattlers;
    D_800C35F8[work[1]]();
}
