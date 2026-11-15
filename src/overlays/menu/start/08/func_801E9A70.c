#include "start_08.h"

MATCH void func_801E9A70(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= MENU_PANEL_STEP_X;
    if ((s16)task->pos.x < -110) {
        LOH(task->pos.x) = -110;
        task->state      = 0;
    }
}
