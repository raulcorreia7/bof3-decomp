#include "game_00.h"

MATCH void func_8019977C(void) {
    MenuPanelTask* task;

    g_MenuActionSteps[((MenuPanelTask*)g_UiPanelCurrent)->state]();
    task = (MenuPanelTask*)g_UiPanelCurrent;
    func_801D5634(7, task->pos.x, task->pos.y, task->item_table, task->flags, task);
}
