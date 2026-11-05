#include "start_08.h"

MATCH void func_801E9284(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x -= 0x20;
    if ((s16)task->x < -0x64) {
        LOH(task->x) = -0x64;
        task->state  = 0;
    }
}
