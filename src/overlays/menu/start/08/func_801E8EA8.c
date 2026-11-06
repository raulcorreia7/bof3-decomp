#include "start_08.h"

MATCH void func_801E8EA8(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x += 0x20;
    if ((s16)task->pos.x >= 0xB7) {
        task->pos.x = 0xB6;
        task->state = 0;
    }
}
