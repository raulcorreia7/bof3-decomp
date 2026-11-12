#include "battle_15.h"

MATCH void func_800B2198(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x += 32;
    if ((s16)task->pos.x >= 84) {
        task->pos.x = 82;
        task->state = 0;
    }
}
