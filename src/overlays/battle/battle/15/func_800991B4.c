#include "battle_15.h"

MATCH void func_800991B4(void) {
    if (Item_GetFlags(D_8014857A, D_801C893C[D_8014857A][D_8014857C]) & 0x20u) {
        g_BattleMessageTurn->command.target = 0x40;
    } else {
        g_BattleMessageTurn->command.target = 0x80;
    }
    g_BattleUIState        = 1;
    g_InputRepeatButtons   = 0;
    g_BattleSelectionLatch = 1;
}
