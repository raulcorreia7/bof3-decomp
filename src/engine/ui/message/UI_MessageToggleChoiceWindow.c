#include "engine/slus/slus.h"

/* func_80151334 */
/* Clears the message step and toggles the selection flag of the window channel while the panel task is in state 2. */
MATCH void UI_MessageToggleChoiceWindow(void) {
    if (g_UiPanelTasks[0].state == 2) {
        g_UiMessageStep = 0;
        g_UiWindowChannel ^= FRONTEND_FLAG_SELECTION;
    }
}
