#include "start_08.h"

MATCH void func_801E8EA8(void) {
    MenuPanelTask* task;

    task = g_UIPanelCurrent;
    task->pos.vx += MENU_PANEL_STEP_X;
    if (task->pos.vx >= 183) {
        task->pos.vx = 182;
        task->state  = 0;
    }
}
