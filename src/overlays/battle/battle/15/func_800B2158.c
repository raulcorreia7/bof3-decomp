#include "battle_15.h"

MATCH void func_800B2158(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= 32;
    if ((s16)task->pos.x < -0xC8) {
        LOH(task->pos.x) = -0xC8;
        task->state      = 0;
    }
}
