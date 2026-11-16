#include "battle_03.h"

MATCH void func_801E257C(u32 enemy_index, u32 script_index) {
    volatile EnemyBattler* saved;

    saved                = g_BattleCurrentEnemy;
    g_BattleCurrentEnemy = (EnemyBattler*)(g_BattleEnemies) + (enemy_index & BYTE_MASK);
    Battle_RequestEnemyScript(script_index & BYTE_MASK);
    g_BattleCurrentEnemy = (EnemyBattler*)saved;
}
