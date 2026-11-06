#include "start_08.h"

MATCH void func_801E8F28(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x -= 0x20;
    if ((s16)task->x < 0x5C) {
        task->x = 0x5C;
        task->state  = 0;
    }
}
