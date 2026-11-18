#include "battle_15.h"

/* func_8009F60C */
MATCH void Battle_CastJolt(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_JOLT;
    Battle_ApplyAbilityDamage();
}
