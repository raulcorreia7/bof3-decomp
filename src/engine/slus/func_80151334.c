#include "engine/slus/slus.h"

/* clears g_UiMessageStep and toggles bit 2 of g_UiWindowChannel when the message panel state is 2.
 */
MATCH void func_80151334(void) {
    if (g_UiPanelTasks[0].state == 2) {
        g_UiMessageStep = 0;
        g_UiWindowChannel ^= FRONTEND_FLAG_SELECTION;
    }
}
