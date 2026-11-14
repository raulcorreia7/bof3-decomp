#include "battle_03.h"

/* func_801E3160 */
MATCH u8 Battle_IsEnemyBlockedOnce(void) {
    volatile EnemyBattler* ew            = BATTLE_CURRENT_ENEMY_PTR;
    volatile u8*           battle_global = (u8*)(PARTY_STATE_PTR);

    if ((ew->status & (STATUS_PARALYZED | STATUS_SLEEPING)) != 0u) {
        return 1u;
    }

    if ((battle_global[0x63CEu] != 0u) && ((ew->turn.action_flags.value & COMBATANT_FLAG_SUPPRESSION_EXEMPT) == 0u)) {
        return 1u;
    }

    return Actor_StepAnimOnce();
}
