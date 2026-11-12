#include "battle_03.h"

/* Active-enemy flag bytes: element 0 of this stride-0x118 table corresponds to
 * master record slot 3 (the three preceding slots are the party members). */

MATCH void func_801DDB7C(void) {
    PartyMember*  work;
    EnemyBattler* enemy;
    u8            index;

    index = 0u;
    while (index < 3u) {
        if (ACTOR_IN_USE(g_Game.members[index])) {
            work = &g_Game.members[index];
            TASK_SET((work));
            g_GameState = work;
            func_801DDAF0();
        } else {
            Battle_AllocEffect(0u, 0u);
        }
        index += 1u;
    }

    index = 3u;
    while (index < 11u) {
        if ((ENEMY_COMBATANT(index).header.flags & 0x1u) != 0u) {
            enemy = (EnemyBattler*)g_BattleEnemies + index;
            TASK_SET((enemy));
            BATTLE_CURRENT_ENEMY_PTR = enemy;
            func_801DDAF0();
        } else {
            Battle_AllocEffect(0u, 0u);
        }
        index += 1u;
    }
}
