#include "battle_03.h"

MATCH void func_801E5288(void) {
    EnemyBattler* enemy;

    Battle_RequestEnemyScript(4);
    enemy = g_BattleCurrentEnemy;
    if ((enemy->turn.damage_flags.value & BATTLER_DAMAGE_UNK_4) != 0u) {
        Battle_IsEnemyBlocked();
    } else if ((enemy->turn.damage_flags.value & BATTLER_DAMAGE_UNK_5) != 0u) {
        Battle_IsEnemyBlockedOnce();
    }
}
