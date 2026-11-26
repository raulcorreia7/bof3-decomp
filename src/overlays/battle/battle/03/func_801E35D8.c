#include "battle_03.h"

MATCH void func_801E35D8(void) {
    volatile EnemyBattler* enemy;

    enemy = g_BattleCurrentEnemy;
    if ((enemy->turn.damage_flags.value & BATTLER_DAMAGE_DEFENDING) != 0u) {
        Battle_RequestEnemyScript(8);
    } else {
        Battle_RequestEnemyScript(0);
    }
    Battle_IsEnemyBlocked();
    SELF(PartyMember)->header.mode += 1;
}
