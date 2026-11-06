#include "battle_15.h"

MATCH void func_80098B44(void) {
    u32 flags;

    flags = Item_GetFlags(D_8014857A, D_801C893C[D_8014857A][D_8014857C]);
    if ((flags & 0x20u) != 0u) {
        D_801EB4D8->command.target = Battle_FindSelectableSlotForward(3);
        g_BattleUIState            = 1u;
    } else if (func_8009AF7C() != 0u) {
        D_801EB4D8->command.target = 0u;
        g_BattleUIState            = 2u;
    } else {
        D_801EB4D8->command.target = Battle_FindSelectableSlotForward(0);
        g_BattleUIState            = 2u;
    }
    g_InputRepeatButtons   = 0;
    g_BattleSelectionLatch = 1u;
}
