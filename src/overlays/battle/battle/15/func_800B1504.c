#include "battle_15.h"

MATCH void func_800B1504(void) {
    MenuPanelTask* task;
    s16            x;

    Battle_DrawCommandList();
    task = g_UIPanelCurrent;
    x    = task->pos.vx;
    if (x >= 347) {
        UI_PanelClear();
    } else {
        task->pos.vx = x + 32;
    }
}
