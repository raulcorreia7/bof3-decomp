#include "battle_15.h"

/* clears the 0x40000 selection flag on every free slot's damage-status
 * row (player rows 0-2, enemy rows indexed by slot-3 up to 10), then sets the
 * same flag on the active battler's row.
 */
MATCH void func_800A26F0(void) {
    u8 slot;

    func_800A3F28();
    for (slot = 0u; slot < BATTLE_PARTY_SLOT_COUNT; slot++) {
        if ((Battle_SlotIsBlocked(slot) & BYTE_MASK) == 0u) {
            g_BattlePartyBattlers[g_BattleTarget].turn.action_flags.value &= ~0x40000u;
        }
    }

    for (slot = 3u; slot < 11u; slot++) {
        if ((Battle_SlotIsBlocked(slot) & BYTE_MASK) == 0u) {
            ENEMY_COMBATANT(g_BattleTarget).turn.action_flags.value &= ~0x40000u;
        }
    }

    if (LOBU(g_BattleTarget) < 3u) {
        g_BattlePartyBattlers[LOBU(g_BattleTarget)].turn.action_flags.value |= 0x40000u;
        return;
    }
    ENEMY_COMBATANT(LOBU(g_BattleTarget)).turn.action_flags.value |= 0x40000u;
}
