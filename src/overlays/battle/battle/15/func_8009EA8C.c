#include "battle_15.h"

MATCH void func_8009EA8C(void) {
    s16 new_var;
    new_var = Battle_CalcDamage(g_Battle.active_battler, g_Battle.target, BATTLE_ELEMENT_FROM_WEAPON) >> 1;
    g_Battle.target_record->hp_change = new_var;
}
