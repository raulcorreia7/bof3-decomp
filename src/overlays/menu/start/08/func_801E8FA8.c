#include "start_08.h"

MATCH void func_801E8FA8(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.y -= 16;
    if ((s16)task->pos.y < 63) {
        task->pos.y = 62;
        task->state = 0;
    }
}
