#include "boss013_16.h"

MATCH void func_800C1C4C(void) {
    EnemyBattler* work;

    if ((g_BattleEncounter == 16) && (g_BattleActiveBattler == 8)) {
        work = g_BattleCurrentEnemy;
        if (work->damage_F8 == 0) {
            work->damage_F8 = 1;
        }
    }
    work = g_BattleCurrentEnemy;
    if (work->hp_94 == 0) {
        work->hp_94 = 1;
    }
}
