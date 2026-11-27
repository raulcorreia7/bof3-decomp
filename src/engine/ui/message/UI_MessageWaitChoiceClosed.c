#include "engine/slus/slus.h"

/* The flag word is reached through the non-volatile MessageState view; the volatile g_UIWindowChannel spelling changes the load/store sequence. */
/* Once the choice panel is closed, ends the message when no request is pending, else steps on. */
MATCH void UI_MessageWaitChoiceClosed(void) {
    if (g_UIPanelTasks[1].state == 4) {
        if (g_UIMessageRequest == MESSAGE_NONE) {
            g_UIMessageState.state = 2;
            g_UIMessageStep        = 0;
            g_UIMessageState.flags |= FRONTEND_FLAG_MODE_LATCH;
            return;
        }
        g_UIMessageStep += 1;
    }
}
