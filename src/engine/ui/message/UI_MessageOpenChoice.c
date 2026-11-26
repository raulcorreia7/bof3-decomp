#include "engine/slus/slus.h"

/* Opens the choice panel, starts the message panel closing and steps on. */
MATCH void UI_MessageOpenChoice(void) {
    u8 next_step;

    g_UiMessageWindow.selection_index = 0;
    UI_PanelOpenTask(1, 0);
    next_step               = g_UiMessageStep;
    next_step               = next_step + 1;
    g_UiPanelTasks[1].mode  = 1;
    g_UiPanelTasks[0].state = 3;
    g_UiWindowChannel |= FRONTEND_FLAG_SELECTION;
    g_UiMessageStep = next_step;
}
