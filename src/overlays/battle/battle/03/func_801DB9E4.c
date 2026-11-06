#include "battle_03.h"

/* reports whether battler_index's work record (local below 3, enemy otherwise) is available and not
 * suppressed and the mode byte equals neither the record's own mode (2 local, 1 enemy) nor 3. FAKE: the mode byte is
 * copied per arm into a word temporary: each arm re-reads the global and hands the value plus the arm's mode constant
 * to one shared comparison, which keeps the re-read in the arm and the constant in a register at the merged tail.
 */
MATCH u8 func_801DB9E4(u32 battler_index) {
    u8  index;
    u8  mode;
    u32 value;

    index = battler_index;
    if (index < 3u) {
        if (ACTOR_IN_USE(g_BattlePartyBattlers[index]) && !HAS_STATUS(g_BattlePartyBattlers[index], 0x4944u) &&
            (g_BattleActionLock == 0u ||
             (g_BattlePartyBattlers[index].action_flags.value & COMBATANT_FLAG_SUPPRESSION_EXEMPT) != 0u)) {
            value = g_BattleSurprise;
            mode  = 2u;
        } else {
            return false;
        }
    } else {
        index = (battler_index - 3u);
        if ((g_BattleEnemyBattlers[index].header.flags & 1u) != 0u &&
            (g_BattleEnemyBattlers[index].status & 0x4144u) == 0u &&
            (g_BattleActionLock == 0u ||
             (g_BattleEnemyBattlers[index].action_flags & COMBATANT_FLAG_SUPPRESSION_EXEMPT) != 0u)) {
            value = g_BattleSurprise;
            mode  = 1u;
        } else {
            return false;
        }
    }
    if (value == mode || value == 3u) {
        return false;
    }
    return true;
}
