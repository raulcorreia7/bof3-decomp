#include "battle_15.h"

MATCH void func_8009EA8C(void) {
    s16 new_var;
    new_var = Battle_CalcDamage(g_BattleActiveBattler, g_BattleTarget, BATTLE_ELEMENT_FROM_WEAPON) >> 1;
    g_BattleTargetRecord->hp_change = new_var;
}
