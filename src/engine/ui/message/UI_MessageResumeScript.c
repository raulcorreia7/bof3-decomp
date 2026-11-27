#include "engine/slus/slus.h"

/* Returns the message state to script running once the message panel is open. */
MATCH void UI_MessageResumeScript(void) {
    if (g_UIPanelTasks[0].state == 2) {
        g_UIMessageState.state = 0;
    }
}
