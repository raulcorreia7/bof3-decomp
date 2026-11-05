#include "battle_03.h"

MATCH void func_801E35D8(void) {
    volatile EnemyBattler* enemy;

    enemy = g_BattleCurrentEnemy;
    if ((enemy->damage_flags & 2u) != 0u) {
        func_801E2314(8);
    } else {
        func_801E2314(0);
    }
    func_801E30F8();
    g_Task->mode += 1;
}
