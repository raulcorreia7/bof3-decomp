#include "battle_03.h"

/* func_801E2284 */
MATCH void Battle_UpdateEnemyActors(void) {
    volatile EnemyBattler* enemy;
    u8                     i;

    for (i = 0; i < 8u; i++) {
        if (g_BattleEnemyBattlers[i].header.flags != 0u) {
            enemy = &g_BattleEnemyBattlers[i];
            TASK_SET((PartyMember*)enemy);
            BATTLE_CURRENT_ENEMY_PTR = enemy;
            func_8014D290();
        }
    }
}
