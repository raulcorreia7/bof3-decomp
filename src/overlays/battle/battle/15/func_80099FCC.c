#include "battle_15.h"

MATCH void func_80099FCC(void) {
    u16 packed;
    u32 flags;

    packed = D_80145FAA[(g_BattleMessageSlot[5] & 0xFF) * 0xA0];
    flags  = Item_GetFlags(packed >> 8, packed & 0xFF);
    if ((flags & 0x20) != 0) {
        D_801EB4D8->command.target = Battle_FindSelectableSlotForward(3);
        g_BattleUIState            = 1;
    } else {
        if (func_8009AF7C() != 0u) {
            D_801EB4D8->command.target = 0u;
        } else {
            D_801EB4D8->command.target = Battle_FindSelectableSlotForward(0);
        }
        g_BattleUIState = 2;
    }
    g_InputRepeatButtons   = 0;
    g_BattleSelectionLatch = 1;
}
