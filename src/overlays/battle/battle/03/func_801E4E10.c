#include "battle_03.h"

MATCH void func_801E4E10(void) {
    u16*          battle_flags;
    EnemyBattler* enemy;
    u32           expected;

    expected = 4;
    enemy    = g_BattleCurrentEnemy;
    if (enemy->turn.command.type == expected) {
        enemy->ap = enemy->ap - g_Battle.unk_E8;
    }
    battle_flags = &g_Battle.flags;
    *battle_flags |= 0x800;
    g_BattleCurrentEnemy->turn.command.type = 0;
    if ((D_801CA71C[g_Battle.action_id].mask & 0x800u) == 0u) {
        Battle_IsEnemyBlockedOnce();
    }
    SELF(PartyMember)->header.step += 1;
}
