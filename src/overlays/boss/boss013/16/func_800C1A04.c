#include "boss013_16.h"

MATCH void func_800C1A04(void) {
    EnemyBattler* work;

    work = g_BattleCurrentEnemy;
    if (work->hp == 0) {
        work->hp = 1;
    }
}
