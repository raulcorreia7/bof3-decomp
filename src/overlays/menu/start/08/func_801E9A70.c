#include "start_08.h"

MATCH void func_801E9A70(void) {
    MenuPanelTask* task;

    task = g_UiPanelCurrent;
    task->pos.vx -= MENU_PANEL_STEP_X;
    if (task->pos.vx < -110) {
        task->pos.vx = -110;
        task->state  = 0;
    }
}
