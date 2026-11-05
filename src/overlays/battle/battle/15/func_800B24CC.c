#include "battle_15.h"

MATCH void func_800B24CC(void) {
    MenuPanelTask* task = g_MenuCurrentPanel;
    s16            value;

    value   = task->x + 0x20;
    task->x = value;
    if (value >= 0x99) {
        task->x     = 152;
        task->state = 0;
    }
}
