#include "battle_03.h"

MATCH u8 func_801E4368(void) {
    if ((BATTLE_CURRENT_ENEMY_PTR->status & (STATUS_PARALYZED | STATUS_CONFUSED | STATUS_SLEEPING | STATUS_KO)) != 0u) {
        return 0u;
    }
    if (BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
        if ((LOBU(g_BattleActionType) == BATTLE_ACTION_ABILITY) && (LOHU(g_BattleActionId) == ABILITY_TIMED_BLOW)) {
            return 0u;
        }
        if ((g_BattleActionLock != 0u) &&
            ((BATTLE_CURRENT_ENEMY_PTR->turn.action_flags.value & COMBATANT_FLAG_SUPPRESSION_EXEMPT) == 0u)) {
            return 0u;
        }
        if ((BATTLE_CURRENT_ENEMY_PTR->event_flags & ENEMY_EVENT_REPRISAL) == 0u) {
            return 0u;
        }
        if ((BATTLE_CURRENT_ENEMY_PTR->turn.damage_flags.value & COMBATANT_FLAG_REPRISAL) != 0u) {
            return 1u;
        }
        if ((rand() % 100) < 0x46) {
            return 1u;
        }
    }
    return 0u;
}
