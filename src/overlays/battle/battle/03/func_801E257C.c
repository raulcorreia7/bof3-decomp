#include "battle_03.h"

MATCH void func_801E257C(u32 enemy_index, u32 script_index) {
    volatile EnemyBattler* saved;

    saved                = g_BattleCurrentEnemy;
    g_BattleCurrentEnemy = (EnemyBattler*)(g_BattleEnemies) + (enemy_index & 0xFF);
    func_801E2314(script_index & 0xFF);
    g_BattleCurrentEnemy = (EnemyBattler*)saved;
}
