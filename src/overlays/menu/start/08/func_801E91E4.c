#include "start_08.h"

MATCH void func_801E91E4(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x -= 0x20;
    if ((s16)task->x < 0xC8) {
        task->x     = 0xC8;
        task->state = 0;
    }
}
