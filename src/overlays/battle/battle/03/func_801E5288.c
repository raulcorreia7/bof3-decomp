#include "battle_03.h"

MATCH void func_801E5288(void) {
    EnemyBattler* enemy;

    func_801E2314(4);
    enemy = g_BattleCurrentEnemy;
    if ((enemy->turn.damage_flags.value & COMBATANT_FLAG_UNK_4) != 0u) {
        func_801E30F8();
    } else if ((enemy->turn.damage_flags.value & COMBATANT_FLAG_UNK_5) != 0u) {
        func_801E3160();
    }
}
