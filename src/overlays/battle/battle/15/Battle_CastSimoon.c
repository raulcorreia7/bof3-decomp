#include "battle_15.h"

/* func_8009F67C */
MATCH void Battle_CastSimoon(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_SIMOON;
    Battle_ApplyAbilityDamage();
}
