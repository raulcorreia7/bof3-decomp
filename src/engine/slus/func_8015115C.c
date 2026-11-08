#include "engine/slus/slus.h"

MATCH void func_8015115C(void) {
    u8 count;

    g_MessageWindow.selection_index = 0;
    Menu_OpenPanelTask(1, 0);
    count                     = g_UiWindowStep;
    count                     = count + 1;
    D_80148356                = 1;
    g_MenuPanelTasks[0].state = 3;
    g_UiWindowChannel |= FRONTEND_FLAG_SELECTION;
    g_UiWindowStep = count;
}
