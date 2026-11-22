#include "shop_00.h"

MATCH void func_801D349C(void) {
    g_UiPanelTasks[0].state   = 1;
    g_UiPanelTasks[1].state   = 1;
    g_UiPanelTasks[7].state   = 1;
    g_UiPanelTasks[21].active = 0;
    D_80148654                = 5;
    g_MenuStep.state          = 0;
    g_MenuStep.sub_step += 2;
}
