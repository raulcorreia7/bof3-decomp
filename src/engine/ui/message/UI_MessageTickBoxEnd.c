#include "engine/slus/slus.h"

/* Counts g_UiMessageStateTimer down, then moves the message panel and the step on and sets FRONTEND_FLAG_SELECTION. */
MATCH void UI_MessageTickBoxEnd(void) {
    u8  ticks;
    u8  panel_state;
    u8  next_step;
    int window_flags;
    u8  next_panel_state;

    ticks                    = g_UiMessageStateTimer[0];
    g_UiMessageStateTimer[0] = ticks + 0xFF;
    if (ticks == 0) {
        next_panel_state = g_UiPanelTasks[0].state + 1;
        next_step        = g_UiMessageStep + 1;
        panel_state      = next_panel_state;
        window_flags     = g_UiWindowChannel;
        window_flags |= FRONTEND_FLAG_SELECTION;
        g_UiPanelTasks[0].state = panel_state;
        g_UiMessageStep         = next_step;
        g_UiWindowChannel       = window_flags;
    }
}
