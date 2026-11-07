#include "battle_15.h"

MATCH void func_80097778(void) {
    u16 kind;

    kind = g_BattleActorTurn->command.id;
    if ((D_801CA718[kind * 0x14] & ABILITY_TARGET_OPPONENT) != 0) {
        g_BattleActorTurn->command.target = Battle_FindSelectableSlotForward(3);
        g_BattleUIState                   = 1u;
    } else {
        if (func_80097EB8() != 0u) {
            g_BattleActorTurn->command.target = 0u;
        } else {
            g_BattleActorTurn->command.target = Battle_FindSelectableSlotForward(0);
        }
        g_BattleUIState = 2u;
    }
    g_InputRepeatButtons   = 0u;
    g_BattleSelectionLatch = 1u;
}
