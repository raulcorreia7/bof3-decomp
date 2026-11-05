#include "start_08.h"

MATCH void func_801E99B4(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x -= 0x20;
    if ((s16)task->x < 166) {
        task->x     = 166;
        task->state = 0;
    }
}
