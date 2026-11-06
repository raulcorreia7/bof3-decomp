#include "start_08.h"

MATCH void func_801EA880(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x += MENU_PANEL_STEP_X;
    if ((s16)task->pos.x >= 18) {
        LOH(task->pos.x) = 17;
        task->state      = 0;
    }
}
