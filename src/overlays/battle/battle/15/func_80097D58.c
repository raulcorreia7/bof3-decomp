#include "battle_15.h"

MATCH void func_80097D58(void) {
    u16 kind;

    kind = D_801EB4D8->command.id;
    if ((D_801CA718[kind * 0x14] & 0x20) != 0) {
        D_801EB4D8->command.target = 0x40;
    } else {
        D_801EB4D8->command.target = 0x80;
    }
    g_BattleUIState        = 1;
    g_InputRepeatButtons   = 0;
    g_BattleSelectionLatch = 1;
}
