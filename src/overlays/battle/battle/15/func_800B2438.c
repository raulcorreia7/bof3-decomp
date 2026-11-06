#include "battle_15.h"

MATCH void func_800B2438(void) {
    MenuPanelTask* task = g_MenuCurrentPanel;
    s16            value;

    value       = task->pos.x + 0x20;
    task->pos.x = value;
    if (value >= 0x63) {
        task->pos.x = 98;
        task->state = 0;
    }
}
