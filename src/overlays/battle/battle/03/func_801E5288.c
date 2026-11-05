#include "battle_03.h"

MATCH void func_801E5288(void) {
    EnemyBattler* enemy;

    func_801E2314(4);
    enemy = g_BattleCurrentEnemy;
    if ((enemy->damage_flags & 0x10u) != 0u) {
        func_801E30F8();
    } else if ((enemy->damage_flags & 0x20u) != 0u) {
        func_801E3160();
    }
}
