#include "battle_15.h"

MATCH void func_800B0250(void) {
    u8  i;
    u8  j;
    u32 slot;

    g_MenuCurrentPanel->unk_08 = 0x18;
    g_MenuCurrentPanel->unk_09 = 0x11;
    for (i = 0; i < 18; i++) {
        D_800B7088[i][0] = 0;
    }
    for (j = 0; j < BATTLE_PARTY_CHARACTERS_COUNT; j++) {
        for (i = 0; i < 6; i++) {
            if (D_800B7070[j][i] != 0) {
                slot                         = Battle_AllocEffect(0, 9) & BYTE_MASK;
                g_BattleEffects[slot].unk_4B = i + j * 6;
                g_BattleEffects[slot].unk_0B = i + j * 6;
            }
        }
    }
    Battle_AllocEffect(0, 10);
    g_MenuCurrentPanel->state++;
}
