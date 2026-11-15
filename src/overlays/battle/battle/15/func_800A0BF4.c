#include "battle_15.h"

MATCH void func_800A0BF4(void) {
    ((volatile BattleTurn*)g_Battle.target_record)->hp_change = Battle_CalcHeal(g_Battle.active_battler, g_Battle.target);
    func_800A36F0(g_Battle.target, 0xBFC);
}
