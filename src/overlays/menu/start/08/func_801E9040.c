#include "start_08.h"

MATCH void func_801E9040(void) {
    MenuPanelTask* task;

    task = g_UiPanelCurrent;
    task->pos.x -= MENU_PANEL_STEP_X;
    if ((s16)task->pos.x <= -0x12C) {
        LOH(task->pos.x) = -0x12C;
        task->state      = 0;
    }
}
