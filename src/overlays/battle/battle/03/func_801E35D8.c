#include "battle_03.h"

MATCH void func_801E35D8(void) {
    volatile EnemyBattler* enemy;

    enemy = g_BattleCurrentEnemy;
    if ((enemy->turn.damage_flags.value & COMBATANT_FLAG_DEFENDING) != 0u) {
        func_801E2314(8);
    } else {
        func_801E2314(0);
    }
    Battle_IsEnemyBlocked();
    g_Task->header.mode += 1;
}
