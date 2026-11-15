#include "start_08.h"

MATCH void func_801E9B6C(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= MENU_PANEL_STEP_X;
    if ((s16)task->pos.x < -0x6E) {
        LOH(task->pos.x) = -0x6E;
        task->state      = 0;
    }
}
