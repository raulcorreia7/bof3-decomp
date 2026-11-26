#include "battle_03.h"

MATCH void func_801E24F8(u32 enemy_index, u32 script_index) {
    volatile PartyMember*  saved_work;
    volatile EnemyBattler* saved_enemy;
    volatile EnemyBattler* enemy;

    saved_work  = SELF(PartyMember);
    saved_enemy = g_BattleCurrentEnemy;
    enemy       = (EnemyBattler*)(g_BattleEnemies) + (enemy_index & BYTE_MASK);
    SELF_SET((enemy));
    g_BattleCurrentEnemy = (EnemyBattler*)enemy;
    Battle_RequestEnemyScript(script_index & BYTE_MASK);
    SELF_SET(saved_work);
    g_BattleCurrentEnemy = (EnemyBattler*)saved_enemy;
}
