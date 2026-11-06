#include "start_08.h"

MATCH void func_801E9100(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x -= 0x20;
    if ((s16)task->x < 0xB6) {
        task->x     = 0xB6;
        task->state = 0;
    }
}
