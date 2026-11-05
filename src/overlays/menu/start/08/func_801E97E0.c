#include "start_08.h"

MATCH void func_801E97E0(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->y -= 16;
    if ((s16)task->y <= 62) {
        task->y     = 62;
        task->state = 0;
    }
}
