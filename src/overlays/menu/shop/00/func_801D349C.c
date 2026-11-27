#include "shop_00.h"

MATCH void func_801D349C(void) {
    g_UIPanelTasks[0].state   = 1;
    g_UIPanelTasks[1].state   = 1;
    g_UIPanelTasks[7].state   = 1;
    g_UIPanelTasks[21].active = 0;
    D_80148654                = 5;
    g_MenuStep.state          = 0;
    g_MenuStep.sub_step += 2;
}
