#include "battle_15.h"

MATCH u8 func_800A4238(s32 input_mask) {
    if (func_800A3A10(g_Battle.active_battler, g_Battle.target) == 0) {
        func_800A31E0(g_Battle.target, input_mask);
        return false;
    }
    return true;
}
