#include "start_08.h"

MATCH void func_801EA880(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x += MENU_PANEL_STEP_X;
    if ((s16)task->x >= 18) {
        LOH(task->x) = 17;
        task->state  = 0;
    }
}
