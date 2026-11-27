#include "battle_15.h"

/* Sets g_UIPanelTasks[21].state to 2 and increments g_Battle.ui_mode. */
MATCH void func_800A4B08(void) {
    u8* counter;
    u8  value;

    counter                  = (u8*)&g_Battle.ui_mode;
    value                    = *counter;
    g_UIPanelTasks[21].state = 2;
    *counter                 = value + 1;
}
