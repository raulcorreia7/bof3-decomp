#include "start_08.h"

MATCH void func_801E9878(void) {
    MenuPanelTask* task;

    task = g_UiPanelCurrent;
    task->pos.x -= MENU_PANEL_STEP_X;
    if ((s16)task->pos.x <= -180) {
        LOH(task->pos.x) = -180;
        task->state      = 0;
    }
}
