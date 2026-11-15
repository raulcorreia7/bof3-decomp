#include "start_08.h"

MATCH void func_801E9100(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= MENU_PANEL_STEP_X;
    if ((s16)task->pos.x < 182) {
        task->pos.x = 182;
        task->state = 0;
    }
}
