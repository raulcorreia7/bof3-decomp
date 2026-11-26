#include "engine/slus/slus.h"

/* The flag word is reached through the non-volatile MessageState view; the volatile g_UiWindowChannel spelling changes the load/store sequence. */
/* Once the choice panel is closed, ends the message when no request is pending, else steps on. */
MATCH void UI_MessageWaitChoiceClosed(void) {
    if (g_UiPanelTasks[1].state == 4) {
        if (g_UiMessageRequest == MESSAGE_NONE) {
            g_UiMessageState.state = 2;
            g_UiMessageStep        = 0;
            g_UiMessageState.flags |= FRONTEND_FLAG_MODE_LATCH;
            return;
        }
        g_UiMessageStep += 1;
    }
}
