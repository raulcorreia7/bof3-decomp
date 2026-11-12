#include "battle_03.h"

/* reports whether one battler slot is selectable: checks its group (local below three, enemy otherwise)
 * against that group's flag byte, gate halfword and stage word, and accepts only when the selection byte is neither
 * the slot's own group nor 3.
 */
MATCH u8 func_801DB844(u32 battler_index) {
    u8  index;
    u32 offset;
    u8  group;

    index = battler_index & BYTE_MASK;
    if (index < 3u) {
        offset = index * 320u;
        if (!ACTOR_IN_USE(g_Game.members[index])) {
            return false;
        }
        if (HAS_STATUS(g_Game.members[index], 0x4964u)) {
            return false;
        }
        if (g_Battle.action_lock != 0u && (g_Game.members[index].u.turn.action_flags.value & COMBATANT_FLAG_SUPPRESSION_EXEMPT) == 0u) {
            return false;
        }
        if ((g_Game.members[index].u.turn.action_flags.value & (COMBATANT_FLAG_DRAGON_FORM_QUEUED | COMBATANT_FLAG_CHARGING | COMBATANT_FLAG_DRAGON_FORM_BERSERK)) != 0u) {
            return false;
        }
        group = 2u;
        if (g_Battle.outcome.surprise != group && g_Battle.outcome.surprise != 3u) {
            return true;
        }
    } else {
        index  = (battler_index - 3u) & BYTE_MASK;
        offset = index * 280u;
        if ((g_BattleEnemyBattlers[index].header.flags & 0x1u) == 0u) {
            return false;
        }
        if ((g_BattleEnemyBattlers[index].status & (STATUS_PARALYZED | STATUS_CONFUSED | STATUS_SLEEPING | STATUS_UNK_8 | STATUS_KO)) != 0u) {
            return false;
        }
        if (g_Battle.action_lock != 0u && (g_BattleEnemyBattlers[index].turn.action_flags.value & COMBATANT_FLAG_SUPPRESSION_EXEMPT) == 0u) {
            return false;
        }
        if ((g_BattleEnemyBattlers[index].turn.action_flags.value & COMBATANT_FLAG_CHARGING) != 0u) {
            return false;
        }
        group = 1u;
        if (g_Battle.outcome.surprise != group && g_Battle.outcome.surprise != 3u) {
            return true;
        }
    }
    return false;
}
