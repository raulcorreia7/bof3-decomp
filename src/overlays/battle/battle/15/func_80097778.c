#include "battle_15.h"

MATCH void func_80097778(void) {
    u16 kind;

    kind = LOHU(D_801EB4D8[2]);
    if ((D_801CA718[kind * 0x14] & 0x20) != 0) {
        D_801EB4D8[0]   = Battle_FindSelectableSlotForward(3);
        g_BattleUIState = 1u;
    } else {
        if (func_80097EB8() != 0u) {
            D_801EB4D8[0] = 0u;
        } else {
            D_801EB4D8[0] = Battle_FindSelectableSlotForward(0);
        }
        g_BattleUIState = 2u;
    }
    g_InputRepeatButtons   = 0u;
    g_BattleSelectionLatch = 1u;
}
