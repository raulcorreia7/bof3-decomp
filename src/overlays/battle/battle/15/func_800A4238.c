#include "battle_15.h"

MATCH u8 func_800A4238(s32 input_mask) {
    if (Battle_PickAbility(g_Battle.active_battler, g_Battle.target) == 0) {
        func_800A31E0(g_Battle.target, input_mask);
        return false;
    }
    return true;
}
