#include "battle_15.h"

MATCH void func_8009FF7C(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_MYOLLNIR;
    Battle_ApplyAbilityDamage();
}
