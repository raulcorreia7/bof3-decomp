#include "engine/slus/slus.h"

/* func_80151334 */
/* Clears the message step and toggles the selection flag of the window channel while the panel task is in state 2. */
MATCH void UI_MessageToggleChoiceWindow(void) {
    if (g_UIPanelTasks[0].state == 2) {
        g_UIMessageStep = 0;
        g_UIWindowChannel ^= FRONTEND_FLAG_SELECTION;
    }
}
