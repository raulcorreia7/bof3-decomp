#include "battle_15.h"

MATCH void func_800B21D8(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x -= 0x20;
    if ((s16)task->x < 0x53) {
        task->x     = 0x52;
        task->state = 0;
    }
}
