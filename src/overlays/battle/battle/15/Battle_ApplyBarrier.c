#include "battle_15.h"

/* func_8009F6B4 */
MATCH void Battle_ApplyBarrier(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_BARRIER;
    Battle_HalveDamage();
}
