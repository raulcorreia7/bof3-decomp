#include "battle_03.h"

/* func_801E2284 */
MATCH void Battle_UpdateEnemyActors(void) {
    volatile EnemyBattler* enemy;
    u8                     i;

    for (i = 0; i < 8u; i++) {
        if (D_801EB630[i].flags != 0u) {
            enemy                                 = &D_801EB630[i];
            SP_REF(volatile PartyBattler*, 0x44u) = (PartyBattler*)enemy;
            BATTLE_CURRENT_ENEMY_PTR              = enemy;
            func_8014D290();
        }
    }
}
