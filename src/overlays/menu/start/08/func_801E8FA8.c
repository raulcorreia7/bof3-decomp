#include "start_08.h"

MATCH void func_801E8FA8(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->y -= 0x10;
    if ((s16)task->y < 0x3F) {
        task->y = 0x3E;
        task->state  = 0;
    }
}
