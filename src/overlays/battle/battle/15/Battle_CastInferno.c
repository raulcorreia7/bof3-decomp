#include "battle_15.h"

/* func_8009F414 */
MATCH void Battle_CastInferno(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_INFERNO;
    Battle_ApplyAbilityDamage();
}
