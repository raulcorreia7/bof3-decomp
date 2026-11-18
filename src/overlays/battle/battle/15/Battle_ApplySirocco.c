#include "battle_15.h"

/* func_8009F484 */
MATCH void Battle_ApplySirocco(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_SIROCCO;
    Battle_ApplyAbilityDamage();
}
