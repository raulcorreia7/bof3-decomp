#include "start_08.h"

MATCH void func_801E9040(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= 32;
    if ((s16)task->pos.x <= -0x12C) {
        LOH(task->pos.x) = -0x12C;
        task->state      = 0;
    }
}
