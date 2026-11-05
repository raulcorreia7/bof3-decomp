#include "battle_03.h"

/* The battle-local work pointer cell lives in normal RAM, not scratchpad;
 * reads of the cell itself are ordinary loads in the original code.
 */

/* reports whether the current local work is eligible for the queued
 * branch, optionally applying the reprisal-pending gate and one random threshold.
 */
MATCH u8 func_801DD448(void) {
    PartyBattler* work;
    volatile u16* gate;
    u16           gate_flags;
    u8            threshold;

    gate       = &g_BattleState;
    gate_flags = *gate;
    if ((gate_flags & BATTLE_STATE_REPRISAL_PENDING) != 0u) {
        *gate = gate_flags & ~BATTLE_STATE_REPRISAL_PENDING;
        return 0u;
    }

    work = g_GameState;
    if ((work->flags_124.value & 1u) != 0u) {
        return 0u;
    }
    if (BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
        return 0u;
    }
    if (HAS_STATUS(*work, 0x4864u)) {
        return 0u;
    }
    if ((LOBU(g_BattleActionType) == 4u) && (LOHU(g_BattleActionId) == 0xA1u)) {
        return 0u;
    }

    if ((g_BattleActionLock != 0u) && ((g_GameState->flags_128.value & COMBATANT_FLAG_SUPPRESSION_EXEMPT) == 0u)) {
        return 0u;
    }

    work = g_GameState;
    if ((work->flags_124.value & COMBATANT_FLAG_REPRISAL) == 0u) {
        threshold = work->stats.reprisal_chance;
        return (rand() % 100) < threshold;
    }
    return 1u;
}
