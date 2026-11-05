#include "start_08.h"

MATCH void func_801E9B6C(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x -= 0x20;
    if ((s16)task->x < -0x6E) {
        LOH(task->x) = -0x6E;
        task->state  = 0;
    }
}
