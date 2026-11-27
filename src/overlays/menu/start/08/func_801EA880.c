#include "start_08.h"

MATCH void func_801EA880(void) {
    MenuPanelTask* task;

    task = g_UiPanelCurrent;
    task->pos.vx += MENU_PANEL_STEP_X;
    if (task->pos.vx >= 18) {
        task->pos.vx = 17;
        task->state  = 0;
    }
}
