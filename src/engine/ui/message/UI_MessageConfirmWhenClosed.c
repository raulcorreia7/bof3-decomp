#include "engine/slus/slus.h"

/* Sets FRONTEND_FLAG_CONFIRM once the message panel is closed. */
MATCH void UI_MessageConfirmWhenClosed(void) {
    if (g_UiPanelTasks[0].state == 4) {
        volatile u16* window_flags = &g_UiWindowChannel;
        *window_flags |= FRONTEND_FLAG_CONFIRM;
    }
}
