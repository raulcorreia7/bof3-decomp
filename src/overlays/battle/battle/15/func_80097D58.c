#include "battle_15.h"

MATCH void func_80097D58(void) {
    u16 kind;

    kind = g_BattleMessageTurn->command.id;
    if ((D_801CA718[kind * 0x14] & ABILITY_TARGET_OPPONENT) != 0) {
        g_BattleMessageTurn->command.target = 0x40;
    } else {
        g_BattleMessageTurn->command.target = 0x80;
    }
    g_BattleUIState        = 1;
    g_InputRepeatButtons   = 0;
    g_BattleSelectionLatch = 1;
}
