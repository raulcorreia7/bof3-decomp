#include "start_08.h"

MATCH void func_801E9788(void) {
    MenuPanelTask* task;
    u16            next;

    task = g_MenuCurrentPanel;
    next = task->pos.x - MENU_PANEL_STEP_X;
    /* FAKE: the do-while wall keeps the limit load after the x store. */
    ORDER_LOCK(task->pos.x = next);
    if ((s16)next < LOH(D_801483C4) + 120) {
        task->pos.x = LOH(D_801483C4) + 120;
        task->state = 0;
    }
}
