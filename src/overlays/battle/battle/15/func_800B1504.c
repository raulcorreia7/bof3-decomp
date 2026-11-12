#include "battle_15.h"

MATCH void func_800B1504(void) {
    MenuPanelTask* task;
    s16            x;

    Battle_DrawCommandList();
    task = g_MenuCurrentPanel;
    x    = task->pos.x;
    if (x >= 347) {
        func_80158E20();
    } else {
        task->pos.x = x + 32;
    }
}
