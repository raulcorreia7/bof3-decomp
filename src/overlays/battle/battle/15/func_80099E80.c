#include "battle_15.h"

MATCH void func_80099E80(void) {
    u16 packed;
    s32 flags;

    packed = D_80145FAA[(g_BattleMessageSlot[5] & BYTE_MASK) * 0xA0];
    flags  = Item_GetFlags(packed >> 8, packed & BYTE_MASK);
    if ((flags & 0x40) != 0) {
        if ((flags & 0x10) != 0) {
            g_BattleUIStep = 9;
        } else {
            g_BattleUIStep = 8;
        }
        g_BattleUIState = 0;
        SND_PlayCue(EMI_CUE_ID(1, 3));
        return;
    }
    if ((flags & 0x80) != 0) {
        g_BattleMessageTurn->command.target = 0xC0;
    } else if ((flags & 0x10) != 0) {
        if ((flags & 0x20) != 0) {
            g_BattleMessageTurn->command.target = 0x40;
        } else {
            g_BattleMessageTurn->command.target = 0x80;
        }
    } else {
        g_BattleMessageTurn->command.target = g_BattleMessageSlot[5];
    }
    g_BattleUIStep  = 8;
    g_BattleUIState = 3;
}
