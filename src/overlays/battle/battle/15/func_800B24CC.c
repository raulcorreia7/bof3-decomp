#include "battle_15.h"

MATCH void func_800B24CC(void) {
    MenuPanelTask* task = g_UiPanelCurrent;
    s16            value;

    value        = task->pos.vx + 0x20;
    task->pos.vx = value;
    if (value >= 0x99) {
        task->pos.vx = 152;
        task->state  = 0;
    }
}
