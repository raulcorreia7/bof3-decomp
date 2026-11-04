#include "engine/slus/slus.h"

/* closes the front-end panel: clears the panel index, arms panel 1
 * with mode 0, marks the panel state, and advances the front-end step.
 */
MATCH void UI_ClosePanel(void) {
    u8 count;

    D_801490BC.selection_index = 0;
    Menu_ArmPanelTask(1, 0);
    count          = g_UiWindowStep;
    D_80148356     = 2;
    g_UiWindowStep = count + 1;
}
