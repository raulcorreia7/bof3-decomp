#include "battle_15.h"

/* INFERRED: the +0x00 flag word and 0x140-byte row match func_800AFF98. */

/* calls func_800A3F28. When the selection index is below 3, sets
 * flag 0x400 in each active player row and then clears it from the row
 * selected by the current selection index.
 */
MATCH void func_800A1CB4(void) {
    u8 slot;

    func_800A3F28();

    if (BATTLER_IS_PLAYER(D_801462F0_state.selection_index)) {
        if (D_801462F0_state.active_count != 0u) {
            slot = 0;
            do {
                g_BattlePartyBattlers[slot].turn.action_flags.value |= COMBATANT_FLAG_SELECT_EXCLUDED;
                slot++;
            } while (slot < D_801462F0_state.active_count);
        }
        g_BattlePartyBattlers[g_BattleTarget].turn.action_flags.value &= ~COMBATANT_FLAG_SELECT_EXCLUDED;
    }
}
