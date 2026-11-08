#include "battle_03.h"

/* returns ready immediately when the local work flags allow it;
 * otherwise delegates to the second EXE-side readiness helper.
 */
MATCH u8 func_801DEE4C(void) {
    volatile PartyBattler* battle_work = g_GameState;
    volatile u8*           global_base = ((volatile u8*)&D_80140000);

    if (HAS_STATUS(*battle_work, STATUS_PARALYZED)) {
        return 1u;
    }

    if ((*(global_base + 0x63CE) != 0u) &&
        ((battle_work->u.turn.action_flags.value & COMBATANT_FLAG_SUPPRESSION_EXEMPT) == 0u)) {
        return 1u;
    }

    return func_8014DAEC();
}
