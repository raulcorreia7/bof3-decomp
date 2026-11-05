#include "battle_03.h"

MATCH void func_801E24F8(u32 enemy_index, u32 script_index) {
    volatile PartyBattler* saved_work;
    volatile EnemyBattler* saved_enemy;
    volatile EnemyBattler* enemy;

    saved_work  = g_Task;
    saved_enemy = g_BattleCurrentEnemy;
    enemy       = (EnemyBattler*)(g_BattleEnemies) + (enemy_index & BYTE_MASK);
    TASK_SET((enemy));
    g_BattleCurrentEnemy = (EnemyBattler*)enemy;
    func_801E2314(script_index & BYTE_MASK);
    g_Task               = saved_work;
    g_BattleCurrentEnemy = (EnemyBattler*)saved_enemy;
}
