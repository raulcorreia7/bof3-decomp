#include "engine/slus/slus.h"

/* Returns the message state to script running once the message panel is open. */
MATCH void UI_MessageResumeScript(void) {
    if (g_UiPanelTasks[0].state == 2) {
        g_UiMessageState.state = 0;
    }
}
