#include "batl_end_00.h"

MATCH u8 func_801EEDA8(void) {
    u8 count = 0;
    u8 slot;

    for (slot = 0; slot < g_BattlePartyCount; slot++) {
        if (func_801DB524(slot) == 0) {
            if ((g_BattlePartyBattlers[slot].turn.action_flags.volatile_value & COMBATANT_FLAG_SELECT_EXCLUDED) == 0) {
                count++;
            }
        }
    }

    return count;
}
