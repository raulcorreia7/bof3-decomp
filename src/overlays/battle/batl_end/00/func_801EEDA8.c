#include "batl_end_00.h"

MATCH u8 func_801EEDA8(void) {
    u8 count = 0;
    u8 slot;

    for (slot = 0; slot < g_Battle.party_count; slot++) {
        if (Battle_SlotIsBlocked(slot) == 0) {
            if ((g_Game.members[slot].u.turn.action_flags.volatile_value & BATTLER_ACTION_SELECT_EXCLUDED) == 0) {
                count++;
            }
        }
    }

    return count;
}
