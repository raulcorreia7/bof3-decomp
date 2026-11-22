#include "battle_03.h"

MATCH void func_801E567C(void) {
    BATTLE_WORK->header.mode = 2u;
    BATTLE_WORK->header.step = 0u;
    Battle_ClearSlotPending(BATTLE_WORK->slot);

    {
        volatile EnemyBattler* enemy = BATTLE_CURRENT_ENEMY_PTR;
        enemy->turn.damage_flags.volatile_value &= 0xFFFFFDFFu;
        if ((g_Battle.flags & BATTLE_STATE_REPRISAL_PENDING) == 0u) {
            enemy->turn.command.type = 0u;
        }
    }
}
