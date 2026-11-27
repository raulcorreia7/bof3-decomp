#include "battle_15.h"

MATCH void func_800B2198(void) {
    MenuPanelTask* task;

    task = g_UIPanelCurrent;
    task->pos.vx += 32;
    if (task->pos.vx >= 84) {
        task->pos.vx = 82;
        task->state  = 0;
    }
}
