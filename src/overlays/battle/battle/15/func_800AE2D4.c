#include "battle_15.h"

/* Selection record at 0x800B65F8: a u16 id followed by the handler word. */

MATCH void func_800AE2D4(u32 selection) {
    volatile u16* flags;
    u8*           row;
    u16           value;

    row   = D_800B6AB0[(selection >> 8) & BYTE_MASK];
    value = g_BattleSelections[row[selection & BYTE_MASK]].id;
    if (value != 0xFFFF) {
        EMI_LoaderStreamInitSlot(value);
        BATTLE_RAISE_STATE(BATTLE_STATE_EFFECT_LOADING);
    }
}
