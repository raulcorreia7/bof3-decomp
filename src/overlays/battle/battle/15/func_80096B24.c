#include "battle_15.h"

MATCH void func_80096B24(void) {
    u8 value;

    *D_801EB4D8            = Battle_FindSelectableSlotForward(3);
    value                  = g_BattleUIState;
    g_BattleSelectionLatch = 1;
    g_InputRepeatButtons   = 0;
    g_BattleUIState        = value + 1;
}
