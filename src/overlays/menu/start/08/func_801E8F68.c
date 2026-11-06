#include "start_08.h"

MATCH void func_801E8F68(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x += 0x20;
    if ((s16)task->pos.x >= 0x5D) {
        LOH(task->pos.x) = 0x5C;
        task->state      = 0;
    }
}
