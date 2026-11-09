#include "engine/slus/slus.h"

/* closes the front-end panel. */
MATCH void UI_ClosePanel(void) {
    u8 count;

    g_MessageWindow.selection_index = 0;
    Menu_OpenPanelTask(1, 0);
    count          = g_UiWindowStep;
    D_80148356     = 2;
    g_UiWindowStep = count + 1;
}
