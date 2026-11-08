#include "battle_03.h"

/* func_801E5704 */
MATCH void Battle_TriggerCritical(void) {
    volatile u16* gate;
    u16           half;
    if (((BATTLE_CURRENT_ENEMY_PTR->event_flags & ENEMY_EVENT_CRITICAL) != 0u) && (RANDOM_MASK(1u) != 0u)) {
        gate        = &g_Battle.state;
        half        = (*gate | BATTLE_STATE_CRITICAL);
        *(u16*)gate = half;
        Battle_AllocEffect(0u, 2u);
    }
}
