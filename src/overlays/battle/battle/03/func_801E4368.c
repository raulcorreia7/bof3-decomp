#include "battle_03.h"

MATCH u8 func_801E4368(void) {
    if ((BATTLE_CURRENT_ENEMY_PTR->status & (STATUS_PARALYZED | STATUS_CONFUSED | STATUS_SLEEPING | STATUS_KO)) != 0u) {
        return 0u;
    }
    if (BATTLER_IS_PLAYER(g_Battle.active_battler)) {
        if ((LOBU(g_Battle.action_type) == BATTLE_ACTION_ABILITY) && (LOHU(g_Battle.action_id) == ABILITY_TIMED_BLOW)) {
            return 0u;
        }
        if ((g_Battle.action_lock != 0u) && ((BATTLE_CURRENT_ENEMY_PTR->turn.action_flags.value & COMBATANT_FLAG_SUPPRESSION_EXEMPT) == 0u)) {
            return 0u;
        }
        if ((BATTLE_CURRENT_ENEMY_PTR->event_flags & ENEMY_EVENT_REPRISAL) == 0u) {
            return 0u;
        }
        if ((BATTLE_CURRENT_ENEMY_PTR->turn.damage_flags.value & COMBATANT_FLAG_REPRISAL) != 0u) {
            return 1u;
        }
        if ((RANDOM_PERCENT()) < 0x46) {
            return 1u;
        }
    }
    return 0u;
}
