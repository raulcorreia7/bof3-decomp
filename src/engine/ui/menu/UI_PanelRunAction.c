#include "engine/game/00/game_00.h"

/* func_8019977C */
/* Runs the action panel step of its state, then draws its item table. */
MATCH void UI_PanelRunAction(void) {
    MenuPanelTask* task;

    g_MenuActionSteps[((MenuPanelTask*)g_UIPanelCurrent)->state]();
    task = (MenuPanelTask*)g_UIPanelCurrent;
    func_801D5634(7, task->pos.vx, task->pos.vy, task->item_table, task->flags, task);
}
