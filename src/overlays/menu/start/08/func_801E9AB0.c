#include "start_08.h"

MATCH void func_801E9AB0(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x += 32;
    if ((s16)task->pos.x >= 46) {
        task->pos.x = 45;
        task->state = 0;
    }
}
