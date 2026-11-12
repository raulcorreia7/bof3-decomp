#include "start_08.h"

MATCH void func_801E8F68(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x += 32;
    if ((s16)task->pos.x >= 93) {
        task->pos.x = 92;
        task->state = 0;
    }
}
