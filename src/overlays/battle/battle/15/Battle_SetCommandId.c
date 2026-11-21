#include "battle_15.h"

/* func_80097778 */
MATCH void Battle_SetCommandId(void) {
    u16 kind;

    kind = g_BattleActorTurn->command.id;
    if ((g_Abilities[kind].targeting_flags & ABILITY_TARGET_FLAG_OPPONENT) != 0) {
        g_BattleActorTurn->command.target = Battle_TargetNext(3);
        g_Battle.ui_mode                  = 1u;
    } else {
        if (func_80097EB8() != 0u) {
            g_BattleActorTurn->command.target = 0u;
        } else {
            g_BattleActorTurn->command.target = Battle_TargetNext(0);
        }
        g_Battle.ui_mode = 2u;
    }
    g_InputRepeatButtons     = 0u;
    g_Battle.selection_latch = 1u;
}
