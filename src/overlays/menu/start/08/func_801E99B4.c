#include "start_08.h"

MATCH void func_801E99B4(void) {
    MenuPanelTask* task;

    task = g_UIPanelCurrent;
    task->pos.vx -= MENU_PANEL_STEP_X;
    if (task->pos.vx < 166) {
        task->pos.vx = 166;
        task->state  = 0;
    }
}
