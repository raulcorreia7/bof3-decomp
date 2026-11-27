#include "engine/slus/slus.h"

/* Counts g_UIMessageStateTimer down, then moves the message panel and the step on and sets FRONTEND_FLAG_SELECTION. */
MATCH void UI_MessageTickBoxEnd(void) {
    u8  ticks;
    u8  panel_state;
    u8  next_step;
    int window_flags;
    u8  next_panel_state;

    ticks                    = g_UIMessageStateTimer[0];
    g_UIMessageStateTimer[0] = ticks + 0xFF;
    if (ticks == 0) {
        next_panel_state = g_UIPanelTasks[0].state + 1;
        next_step        = g_UIMessageStep + 1;
        panel_state      = next_panel_state;
        window_flags     = g_UIWindowChannel;
        window_flags |= FRONTEND_FLAG_SELECTION;
        g_UIPanelTasks[0].state = panel_state;
        g_UIMessageStep         = next_step;
        g_UIWindowChannel       = window_flags;
    }
}
