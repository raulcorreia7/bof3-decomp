#include "battle_03.h"

/* returns ready immediately when the local work flags allow it;
 * otherwise delegates to the first EXE-side readiness helper.
 */
MATCH u8 func_801DEDE4(void) {
    volatile PartyMember* battle_work   = g_Game.current;
    volatile u8*          battle_global = (u8*)(PARTY_STATE_PTR);

    if (HAS_STATUS(*battle_work, STATUS_PARALYZED)) {
        return 1u;
    }

    if ((battle_global[0x63CEu] != 0u) &&
        ((battle_work->u.turn.action_flags.value & COMBATANT_FLAG_SUPPRESSION_EXEMPT) == 0u)) {
        return 1u;
    }

    return Actor_StepAnimLoop();
}
