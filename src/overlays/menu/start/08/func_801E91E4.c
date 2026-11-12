#include "start_08.h"

MATCH void func_801E91E4(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= 32;
    if ((s16)task->pos.x < 200) {
        task->pos.x = 200;
        task->state = 0;
    }
}
