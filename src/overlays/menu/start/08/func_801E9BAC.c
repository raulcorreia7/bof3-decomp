#include "start_08.h"

MATCH void func_801E9BAC(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x += 0x20;
    if ((s16)task->pos.x >= 0x2E) {
        task->pos.x = 0x2D;
        task->state = 0;
    }
}
