#include "battle_03.h"

MATCH u8 func_801E30F8(void) {
    volatile EnemyBattler* ew            = BATTLE_CURRENT_ENEMY_PTR;
    volatile u8*           battle_global = (u8*)(EFFECT_BANK_80140000);

    if ((ew->status & (STATUS_PARALYZED | STATUS_SLEEPING)) != 0u) {
        return 1u;
    }

    if ((battle_global[0x63CEu] != 0u) && ((ew->turn.action_flags.value & COMBATANT_FLAG_SUPPRESSION_EXEMPT) == 0u)) {
        return 1u;
    }

    return func_8014D978();
}
