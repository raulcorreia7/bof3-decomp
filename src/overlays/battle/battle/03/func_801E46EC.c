#include "battle_03.h"

MATCH void func_801E46EC(void) {
    if (Battle_IsEnemyBlockedOnce() != 0u) {
        g_Task->unk_03 += 1;
        if ((g_BattleCurrentEnemy->turn.damage_flags.value & COMBATANT_FLAG_DEFENDING) != 0u) {
            func_801E2314(8);
        } else {
            func_801E2314(0);
        }
    }
}
