#include "start_08.h"

MATCH void func_801E98B8(void) {
    MenuPanelTask* task;

    task = g_UIPanelCurrent;
    task->pos.vx += MENU_PANEL_STEP_X;
    if (task->pos.vx >= 137) {
        task->pos.vx = 137;
        task->state  = 0;
    }
}
