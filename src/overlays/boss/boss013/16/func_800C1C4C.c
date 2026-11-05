#include "boss013_16.h"

MATCH void func_800C1C4C(void) {
    EnemyBattler* work;

    if ((g_BattleEncounter == 16) && (g_BattleActiveBattler == 8)) {
        work = g_BattleCurrentEnemy;
        if (work->damage == 0) {
            work->damage = 1;
        }
    }
    work = g_BattleCurrentEnemy;
    if (work->hp == 0) {
        work->hp = 1;
    }
}
