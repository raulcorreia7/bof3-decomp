#include "start_08.h"

MATCH void func_801EAF58(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x -= MENU_PANEL_STEP_X;
    if ((s16)task->x < 150) {
        task->x     = 150;
        task->state = 0;
    }
}
