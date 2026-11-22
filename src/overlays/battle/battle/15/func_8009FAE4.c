#include "battle_15.h"

MATCH void func_8009FAE4(void) {
    volatile u16* flags;
    u16           value;
    u8            a;
    u8            b;

    flags              = &g_Battle.flags;
    value              = *flags;
    a                  = g_Battle.active_battler;
    b                  = g_Battle.target_selector;
    *flags             = value | 0x4000;
    g_Battle.unk_EA[0] = a;
    g_Battle.unk_EA[1] = b;
    Battle_MarkDamageApplied();
}
