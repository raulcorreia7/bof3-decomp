#include "start_08.h"

MATCH void func_801E9878(void) {
    MenuPanelTask* task;

    task = g_UiPanelCurrent;
    task->pos.vx -= MENU_PANEL_STEP_X;
    if (task->pos.vx <= -180) {
        task->pos.vx = -180;
        task->state  = 0;
    }
}
