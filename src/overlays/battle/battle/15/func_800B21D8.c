#include "battle_15.h"

MATCH void func_800B21D8(void) {
    MenuPanelTask* task;

    task = g_UIPanelCurrent;
    task->pos.vx -= 32;
    if (task->pos.vx < 83) {
        task->pos.vx = 82;
        task->state  = 0;
    }
}
