#include "battle_03.h"

/* func_801E2170 */
MATCH void Battle_RunEnemies(void) {
    volatile EnemyBattler* enemy;
    s32                    i;

    for (i = 0; (i & BYTE_MASK) < 8u; i++) {
        if (g_BattleEnemyBattlers[(u8)i].flags != 0u) {
            enemy = &g_BattleEnemyBattlers[(u8)i];
            TASK_SET((PartyBattler*)enemy);
            g_BattleCurrentEnemy = (EnemyBattler*)enemy;
            if (g_BattleEncounter != 0u) {
                if (enemy->mode != 0u) {
                    enemy->unk_E4(2);
                }
                D_801EB298[g_BattleCurrentEnemy->unk_F0]();
            } else {
                D_801EB294[enemy->unk_F0]();
            }
        }
    }
}
