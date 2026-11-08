#include "battle_03.h"

/* The battle-local work pointer cell lives in normal RAM, not scratchpad;
 * reads of the cell itself are ordinary loads in the original code.
 */

/* reports whether the current local work is eligible for the queued
 * branch, optionally applying the reprisal-pending gate and one random threshold.
 */
MATCH u8 func_801DD448(void) {
    PartyMember*  work;
    volatile u16* gate;
    u16           gate_flags;
    u8            threshold;

    gate       = &g_Battle.state;
    gate_flags = *gate;
    if ((gate_flags & BATTLE_STATE_REPRISAL_PENDING) != 0u) {
        *gate = gate_flags & ~BATTLE_STATE_REPRISAL_PENDING;
        return 0u;
    }

    work = g_Game.current;
    if ((work->u.turn.damage_flags.value & COMBATANT_FLAG_COMMAND_ENTERED) != 0u) {
        return 0u;
    }
    if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
        return 0u;
    }
    if (HAS_STATUS(*work, 0x4864u)) {
        return 0u;
    }
    if ((LOBU(g_Battle.action_type) == BATTLE_ACTION_ABILITY) && (LOHU(g_Battle.action_id) == ABILITY_TIMED_BLOW)) {
        return 0u;
    }

    if ((g_Battle.action_lock != 0u) &&
        ((g_Game.current->u.turn.action_flags.value & COMBATANT_FLAG_SUPPRESSION_EXEMPT) == 0u)) {
        return 0u;
    }

    work = g_Game.current;
    if ((work->u.turn.damage_flags.value & COMBATANT_FLAG_REPRISAL) == 0u) {
        threshold = work->chr.stats.reprisal_chance;
        return (RANDOM_PERCENT()) < threshold;
    }
    return 1u;
}
