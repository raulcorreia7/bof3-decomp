#include "engine/slus/slus.h"

/* Once the choice panel is closed, closes the message panel, sets the end state at its confirm step and sets FRONTEND_FLAG_MODE_LATCH. */
MATCH void UI_MessageEndAfterChoice(void) {
    volatile u16* window_flags;

    if (g_UiPanelTasks[1].state == 4) {
        g_UiPanelTasks[0].state = 4;
        g_UiMessageState.state  = 2;
        g_UiMessageStep         = 1;
        window_flags            = &g_UiWindowChannel;
        *window_flags |= FRONTEND_FLAG_MODE_LATCH;
    }
}
