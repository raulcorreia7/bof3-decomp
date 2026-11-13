#include "battle_15.h"

MATCH void func_8009F2B0(void) {
    g_Battle.action_type = BATTLE_ACTION_ABILITY;
    g_Battle.action_id   = ABILITY_TYPHOON;
    Battle_ApplyAbilityDamage();
}
