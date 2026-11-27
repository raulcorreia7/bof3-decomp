#include "start_08.h"

MATCH void func_801E9040(void) {
    MenuPanelTask* task;

    task = g_UiPanelCurrent;
    task->pos.vx -= MENU_PANEL_STEP_X;
    if (task->pos.vx <= -0x12C) {
        task->pos.vx = -0x12C;
        task->state  = 0;
    }
}
