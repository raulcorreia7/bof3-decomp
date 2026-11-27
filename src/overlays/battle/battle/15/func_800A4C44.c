#include "battle_15.h"

/* Sets g_UIPanelTasks[21].state to 2, clears g_UIPanelTasks[21].unk_0A and increments g_Battle.ui_mode. */
MATCH void func_800A4C44(void) {
    u8* counter = (u8*)&g_Battle.ui_mode;
    u8  count   = *counter;

    g_UIPanelTasks[21].state  = 2;
    g_UIPanelTasks[21].unk_0A = 0;
    *counter                  = (count + 1);
}
