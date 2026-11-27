#include "start_08.h"

MATCH void func_801E9B6C(void) {
    MenuPanelTask* task;

    task = g_UIPanelCurrent;
    task->pos.vx -= MENU_PANEL_STEP_X;
    if (task->pos.vx < -0x6E) {
        task->pos.vx = -0x6E;
        task->state  = 0;
    }
}
