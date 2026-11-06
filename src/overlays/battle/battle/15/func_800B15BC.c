#include "battle_15.h"

MATCH void func_800B15BC(void) {
    s32 offset;
    s32 slot;
    s32 row;

    for (row = 0; (row & 0xFF) < 3U; row++) {
        for (slot = 0; (slot & 0xFF) < 3U; slot++) {
            offset                         = Battle_AllocEffect(0, 0xE) & 0xFF;
            g_BattleEffects[offset].unk_0A = slot;
            g_BattleEffects[offset].unk_09 = row;
        }
    }
    g_MenuCurrentPanel->unk_14 = 0xC;
    g_MenuCurrentPanel->state  = (g_MenuCurrentPanel->state + 1);
}
