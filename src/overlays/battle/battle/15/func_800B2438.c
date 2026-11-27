#include "battle_15.h"

MATCH void func_800B2438(void) {
    MenuPanelTask* task = g_UiPanelCurrent;
    s16            value;

    value        = task->pos.vx + 0x20;
    task->pos.vx = value;
    if (value >= 0x63) {
        task->pos.vx = 98;
        task->state  = 0;
    }
}
