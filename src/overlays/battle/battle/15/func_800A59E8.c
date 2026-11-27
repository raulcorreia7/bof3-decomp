#include "battle_15.h"

/* Sets g_UiPanelTasks[21].state to 2, g_UiPanelTasks[21].unk_0A to 1 and increments g_Battle.ui_mode. */
MATCH void func_800A59E8(void) {
    u8* counter = (u8*)&g_Battle.ui_mode;
    u8  value;

    g_UiPanelTasks[21].state  = 2;
    value                     = *counter;
    g_UiPanelTasks[21].unk_0A = 1;
    *counter                  = value + 1;
}
