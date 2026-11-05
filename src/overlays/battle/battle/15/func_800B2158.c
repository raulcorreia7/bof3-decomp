#include "battle_15.h"

MATCH void func_800B2158(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->x -= 0x20;
    if ((s16)task->x < -0xC8) {
        LOH(task->x) = -0xC8;
        task->state  = 0;
    }
}
