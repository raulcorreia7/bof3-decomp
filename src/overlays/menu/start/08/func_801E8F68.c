#include "start_08.h"

MATCH void func_801E8F68(void) {
    MenuPanelTask* task;

    task = g_UIPanelCurrent;
    task->pos.vx += MENU_PANEL_STEP_X;
    if (task->pos.vx >= 93) {
        task->pos.vx = 92;
        task->state  = 0;
    }
}
