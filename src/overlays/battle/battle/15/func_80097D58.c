#include "battle_15.h"

MATCH void func_80097D58(void) {
    u16 kind;

    kind = g_BattleActorTurn->command.id;
    if ((D_801CA718[kind * 0x14] & ABILITY_TARGET_OPPONENT) != 0) {
        g_BattleActorTurn->command.target = BATTLE_TARGET_ENEMY_SIDE;
    } else {
        g_BattleActorTurn->command.target = BATTLE_TARGET_PARTY_SIDE;
    }
    g_Battle.ui_state        = 1;
    g_InputRepeatButtons     = 0;
    g_Battle.selection_latch = 1;
}
