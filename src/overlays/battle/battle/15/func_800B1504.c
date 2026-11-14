#include "battle_15.h"

MATCH void func_800B1504(void) {
    MenuPanelTask* task;
    s16            x;

    Battle_DrawCommandList();
    task = g_MenuCurrentPanel;
    x    = task->pos.x;
    if (x >= 347) {
        Menu_ClearPanel();
    } else {
        task->pos.x = x + 32;
    }
}
