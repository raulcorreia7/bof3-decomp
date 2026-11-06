#include "start_08.h"

MATCH void func_801E97E0(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.y -= 16;
    if ((s16)task->pos.y <= 62) {
        task->pos.y = 62;
        task->state = 0;
    }
}
