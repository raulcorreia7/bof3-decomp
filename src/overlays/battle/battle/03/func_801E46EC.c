#include "battle_03.h"

MATCH void func_801E46EC(void) {
    if (Battle_IsEnemyBlockedOnce() != 0u) {
        SELF(PartyMember)->unk_03 += 1;
        if ((g_BattleCurrentEnemy->turn.damage_flags.value & BATTLER_DAMAGE_DEFENDING) != 0u) {
            Battle_RequestEnemyScript(8);
        } else {
            Battle_RequestEnemyScript(0);
        }
    }
}
