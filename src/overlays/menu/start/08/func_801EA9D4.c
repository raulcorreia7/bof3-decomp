#include "start_08.h"

MATCH void func_801EA9D4(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= MENU_PANEL_STEP_X;
    if ((s16)task->pos.x < 150) {
        task->pos.x = 150;
        task->state = 0;
    }
}
