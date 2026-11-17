#include "battle_03.h"

MATCH void func_801E567C(void) {
    g_Task->header.mode = 2u;
    g_Task->header.step = 0u;
    Battle_ClearSlotPending(g_Task->slot);

    {
        volatile EnemyBattler* enemy = BATTLE_CURRENT_ENEMY_PTR;
        enemy->turn.damage_flags.volatile_value &= 0xFFFFFDFFu;
        if ((g_Battle.flags & BATTLE_STATE_REPRISAL_PENDING) == 0u) {
            enemy->turn.command.type = 0u;
        }
    }
}
