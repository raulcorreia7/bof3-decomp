#include "battle_15.h"

MATCH u8 func_800A41D8(s32 input_mask) {
    func_800A3F28();
    if (func_800A3A10(g_BattleActiveBattler, g_BattleTarget) == 0) {
        func_800A31E0(g_BattleTarget, (u16)input_mask);
        return 0;
    }
    return 1;
}
