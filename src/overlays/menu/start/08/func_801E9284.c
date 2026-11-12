#include "start_08.h"

MATCH void func_801E9284(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= 32;
    if ((s16)task->pos.x < -0x64) {
        LOH(task->pos.x) = -0x64;
        task->state      = 0;
    }
}
