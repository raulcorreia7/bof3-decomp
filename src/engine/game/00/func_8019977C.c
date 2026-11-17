#include "game_00.h"

MATCH void func_8019977C(void) {
    MenuPanelTask* task;

    g_MenuActionSteps[((MenuPanelTask*)g_MenuCurrentPanel)->state]();
    task = (MenuPanelTask*)g_MenuCurrentPanel;
    func_801D5634(7, task->pos.x, task->pos.y, task->item_table, task->flags, task);
}
