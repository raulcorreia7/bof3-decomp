#include "battle_15.h"

/* func_8009F564 */
MATCH void Battle_CastFireblast(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_FIREBLAST;
    Battle_ApplyAbilityDamage();
}
