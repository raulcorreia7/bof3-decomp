#include "battle_15.h"

MATCH void func_800B2158(void) {
    MenuPanelTask* task;

    task = g_UIPanelCurrent;
    task->pos.vx -= 32;
    if (task->pos.vx < -0xC8) {
        task->pos.vx = -0xC8;
        task->state  = 0;
    }
}
