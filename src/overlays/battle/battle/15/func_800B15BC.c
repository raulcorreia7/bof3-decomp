#include "battle_15.h"

MATCH void func_800B15BC(void) {
    s32 offset;
    s32 slot;
    s32 row;

    for (row = 0; (u32)(row & BYTE_MASK) < 3U; row++) {
        for (slot = 0; (u32)(slot & BYTE_MASK) < 3U; slot++) {
            offset                         = Battle_AllocEffect(0, 0xE) & BYTE_MASK;
            g_BattleEffects[offset].unk_0A = slot;
            g_BattleEffects[offset].unk_09 = row;
        }
    }
    g_MenuCurrentPanel->unk_14 = 0xC;
    g_MenuCurrentPanel->state  = (u8)(g_MenuCurrentPanel->state + 1);
}
