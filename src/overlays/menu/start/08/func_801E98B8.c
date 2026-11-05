#include "start_08.h"

MATCH void func_801E98B8(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x += 0x20;
    if ((s16)task->x >= 137) {
        task->x     = 137;
        task->state = 0;
    }
}
