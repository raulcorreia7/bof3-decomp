#include "battle_15.h"

/* Sets g_UiPanelTasks[17].state to 2, g_BattleMessageState to 1 and increments g_Battle.ui_mode. */
MATCH void func_800A5300(void) {
    u8* counter;
    u8  value;

    counter                  = (u8*)&g_Battle.ui_mode;
    g_UiPanelTasks[17].state = 2;
    value                    = *counter;
    g_BattleMessageState     = 1;
    *counter                 = value + 1;
}
