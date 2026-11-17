#include "battle_15.h"

/* func_80096B24 */
MATCH void Battle_StartAttackTarget(void) {
    u8 value;

    g_BattleActorTurn->command.target = Battle_TargetNext(3);
    value                             = g_BattleUIState;
    g_Battle.selection_latch          = 1;
    g_InputRepeatButtons              = 0;
    g_Battle.ui_mode                  = value + 1;
}
