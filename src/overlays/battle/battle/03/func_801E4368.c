#include "battle_03.h"

MATCH u8 func_801E4368(void) {
    if ((BATTLE_CURRENT_ENEMY_PTR->status & (STATUS_PARALYZED | STATUS_CONFUSED | STATUS_SLEEPING | STATUS_KO)) != 0u) {
        return 0u;
    }
    if (BATTLER_IS_PLAYER(g_BattleActiveBattler)) {
        if ((LOBU(g_BattleActionType) == BATTLE_ACTION_ABILITY) && (LOHU(g_BattleActionId) == 0xA1u)) {
            return 0u;
        }
        if ((g_BattleActionLock != 0u) &&
            ((BATTLE_CURRENT_ENEMY_PTR->action_flags & COMBATANT_FLAG_SUPPRESSION_EXEMPT) == 0u)) {
            return 0u;
        }
        if ((BATTLE_CURRENT_ENEMY_PTR->event_flags & 2u) == 0u) {
            return 0u;
        }
        if ((BATTLE_CURRENT_ENEMY_PTR->damage_flags & COMBATANT_FLAG_REPRISAL) != 0u) {
            return 1u;
        }
        if ((rand() % 100) < 0x46) {
            return 1u;
        }
    }
    return 0u;
}
