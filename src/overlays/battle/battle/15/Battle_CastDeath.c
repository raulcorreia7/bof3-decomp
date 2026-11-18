#include "battle_15.h"

/* func_800A2404 */
MATCH void Battle_CastDeath(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_DEATH;
    func_800A0378();
}
