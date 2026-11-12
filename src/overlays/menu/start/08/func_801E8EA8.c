#include "start_08.h"

MATCH void func_801E8EA8(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x += 32;
    if ((s16)task->pos.x >= 183) {
        task->pos.x = 182;
        task->state = 0;
    }
}
