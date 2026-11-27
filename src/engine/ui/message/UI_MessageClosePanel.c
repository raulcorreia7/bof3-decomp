#include "engine/slus/slus.h"

/* closes the front-end panel: clears the panel index, arms panel 1
 * with mode 0, marks the panel state, and advances the front-end step.
 */
MATCH void UI_MessageClosePanel(void) {
    u8 count;

    g_UIMessageWindow.selection_index = 0;
    UI_PanelOpenTask(1, 0);
    count                  = g_UIMessageStep;
    g_UIPanelTasks[1].mode = 2;
    g_UIMessageStep        = count + 1;
}
