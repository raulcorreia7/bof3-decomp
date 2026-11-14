#include "battle_15.h"

/* clears the 0x40000 selection flag on every free slot's damage-status
 * row (player rows 0-2, enemy rows indexed by slot-3 up to 10), then sets the
 * same flag on the active battler's row.
 */
MATCH void func_800A26F0(void) {
    u8 slot;

    Battle_MarkDamageApplied();
    for (slot = 0u; slot < BATTLE_PARTY_CHARACTERS_COUNT; slot++) {
        if ((Battle_SlotIsBlocked(slot) & BYTE_MASK) == 0u) {
            g_Game.members[g_Battle.target].u.turn.action_flags.value &= ~COMBATANT_FLAG_SELECTED;
        }
    }

    for (slot = 3u; slot < 11u; slot++) {
        if ((Battle_SlotIsBlocked(slot) & BYTE_MASK) == 0u) {
            ENEMY_COMBATANT(g_Battle.target).turn.action_flags.value &= ~COMBATANT_FLAG_SELECTED;
        }
    }

    if (LOBU(g_Battle.target) < 3u) {
        g_Game.members[LOBU(g_Battle.target)].u.turn.action_flags.value |= COMBATANT_FLAG_SELECTED;
        return;
    }
    ENEMY_COMBATANT(LOBU(g_Battle.target)).turn.action_flags.value |= COMBATANT_FLAG_SELECTED;
}
