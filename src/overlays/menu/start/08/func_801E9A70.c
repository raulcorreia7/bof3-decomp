#include "start_08.h"

MATCH void func_801E9A70(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x -= 0x20;
    if ((s16)task->x < -110) {
        LOH(task->x) = -110;
        task->state  = 0;
    }
}
