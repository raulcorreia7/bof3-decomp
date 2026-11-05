#include "battle_03.h"

MATCH void func_801E567C(void) {
    g_Task->mode = 2u;
    g_Task->step = 0u;
    Battle_ClearSlotPending(g_Task->slot);

    {
        volatile EnemyBattler* enemy = BATTLE_CURRENT_ENEMY_PTR;
        BATTLE_ENEMY_WORD_100(enemy) &= 0xFFFFFDFFu;
        if ((g_BattleState & BATTLE_STATE_REPRISAL_PENDING) == 0u) {
            BATTLE_ENEMY_BYTE_F5(enemy) = 0u;
        }
    }
}
