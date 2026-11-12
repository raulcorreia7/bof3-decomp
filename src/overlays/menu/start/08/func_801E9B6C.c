#include "start_08.h"

MATCH void func_801E9B6C(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= 32;
    if ((s16)task->pos.x < -0x6E) {
        LOH(task->pos.x) = -0x6E;
        task->state      = 0;
    }
}
