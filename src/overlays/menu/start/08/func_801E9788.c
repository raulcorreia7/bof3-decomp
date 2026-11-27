#include "start_08.h"

MATCH void func_801E9788(void) {
    MenuPanelTask* task;
    u16            next;

    task = g_UiPanelCurrent;
    next = task->pos.vx - MENU_PANEL_STEP_X;
    task->pos.vx = next;
    if ((s16)next < g_UiPanelTasks[4].pos.vx + 120) {
        task->pos.vx = g_UiPanelTasks[4].pos.vx + 120;
        task->state  = 0;
    }
}
