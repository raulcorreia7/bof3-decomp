#include "start_08.h"

MATCH void func_801E8EA8(void) {
    MenuPanelTask* task;

    task = g_UiPanelCurrent;
    task->pos.x += MENU_PANEL_STEP_X;
    if ((s16)task->pos.x >= 183) {
        task->pos.x = 182;
        task->state = 0;
    }
}
