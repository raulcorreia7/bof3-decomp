#include "engine/slus/slus.h"

MATCH void func_8015115C(void) {
    u8 count;

    g_UiMessageWindow.selection_index = 0;
    UI_PanelOpenTask(1, 0);
    count                   = g_UiMessageStep;
    count                   = count + 1;
    g_UiPanelTasks[1].mode  = 1;
    g_UiPanelTasks[0].state = 3;
    g_UiWindowChannel |= FRONTEND_FLAG_SELECTION;
    g_UiMessageStep = count;
}
