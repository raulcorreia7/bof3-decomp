#include "start_08.h"

MATCH void func_801E9100(void) {
    MenuPanelTask* task;

    task = g_UiPanelCurrent;
    task->pos.vx -= MENU_PANEL_STEP_X;
    if (task->pos.vx < 182) {
        task->pos.vx = 182;
        task->state  = 0;
    }
}
