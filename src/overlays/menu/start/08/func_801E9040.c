#include "start_08.h"

MATCH void func_801E9040(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x -= 0x20;
    if ((s16)task->x <= -0x12C) {
        LOH(task->x) = -0x12C;
        task->state  = 0;
    }
}
