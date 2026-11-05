#include "battle_15.h"

MATCH void func_8009FAE4(void) {
    volatile u16* flags;
    u16           value;
    u8            a;
    u8            b;

    flags      = &g_BattleState;
    value      = *flags;
    a          = g_BattleActiveBattler;
    b          = g_BattleTargetSelector;
    *flags     = value | 0x4000;
    D_801463CA = a;
    D_801463CB = b;
    func_800A3F28();
}
