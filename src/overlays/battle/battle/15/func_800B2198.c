#include "battle_15.h"

MATCH void func_800B2198(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x += 0x20;
    if ((s16)task->pos.x >= 0x54) {
        task->pos.x = 0x52;
        task->state = 0;
    }
}
