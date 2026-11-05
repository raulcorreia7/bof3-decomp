#include "battle_15.h"

MATCH void func_8009EA8C(void) {
    s16 new_var;
    new_var                         = Battle_CalcDamage(g_BattleActiveBattler, g_BattleTarget, 0xFFFF) >> 1;
    ((s16*)g_BattleTargetRecord)[2] = new_var;
}
