#include "start_08.h"

MATCH void func_801E8F28(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= MENU_PANEL_STEP_X;
    if ((s16)task->pos.x < 92) {
        task->pos.x = 92;
        task->state = 0;
    }
}
