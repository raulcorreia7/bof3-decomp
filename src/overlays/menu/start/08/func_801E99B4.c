#include "start_08.h"

MATCH void func_801E99B4(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= MENU_PANEL_STEP_X;
    if ((s16)task->pos.x < 166) {
        task->pos.x = 166;
        task->state = 0;
    }
}
