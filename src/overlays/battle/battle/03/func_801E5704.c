#include "battle_03.h"

MATCH void func_801E5704(void) {
    volatile u16* gate;
    u16           half;
    if (((BATTLE_CURRENT_ENEMY_PTR->event_flags & 8u) != 0u) && ((RANDOM_MASK(1u)) != 0u)) {
        gate        = &g_BattleState;
        half        = (*gate | BATTLE_STATE_CRITICAL);
        *(u16*)gate = half;
        Battle_AllocEffect(0u, 2u);
    }
}
