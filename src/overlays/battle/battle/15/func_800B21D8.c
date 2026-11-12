#include "battle_15.h"

MATCH void func_800B21D8(void) {
    MenuPanelTask* task;

    task = g_MenuCurrentPanel;
    task->pos.x -= 32;
    if ((s16)task->pos.x < 83) {
        task->pos.x = 82;
        task->state = 0;
    }
}
