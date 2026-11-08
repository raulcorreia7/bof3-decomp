#include "battle_03.h"

/* refreshes one local record's activation and reports whether its
 * `0x400` flag is clear.
 */
MATCH u8 func_801DD704(u8 battler_index) {
    u32 flags;

    if (Battle_SlotIsBlocked(battler_index) == 0u) {
        flags = g_BattlePartyBattlers[battler_index].u.turn.action_flags.value & COMBATANT_FLAG_SELECT_EXCLUDED;
        return flags == 0u;
    }
    return 0u;
}
