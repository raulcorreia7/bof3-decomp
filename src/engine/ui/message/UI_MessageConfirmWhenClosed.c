#include "engine/slus/slus.h"

/* Sets FRONTEND_FLAG_CONFIRM once the message panel is closed. */
MATCH void UI_MessageConfirmWhenClosed(void) {
    if (g_UIPanelTasks[0].state == 4) {
        volatile u16* window_flags = &g_UIWindowChannel;
        *window_flags |= FRONTEND_FLAG_CONFIRM;
    }
}
