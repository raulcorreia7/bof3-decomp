#include "battle_03.h"

MATCH void func_801E4E10(void) {
    u16*          battle_flags;
    EnemyBattler* enemy;
    u32           expected;

    expected = 4;
    enemy    = g_BattleCurrentEnemy;
    if (enemy->unk_F5 == expected) {
        enemy->ap = enemy->ap - D_801463C8;
    }
    battle_flags = &g_BattleState;
    *battle_flags |= 0x800;
    g_BattleCurrentEnemy->unk_F5 = 0;
    if ((D_801CA71C[g_BattleActionId].mask & 0x800u) == 0u) {
        func_801E3160();
    }
    g_Task->step += 1;
}
