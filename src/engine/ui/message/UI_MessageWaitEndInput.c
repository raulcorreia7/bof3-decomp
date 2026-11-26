#include "engine/slus/slus.h"

/* On a pad press or an advance or latch request, moves the message panel and the step on and sets FRONTEND_FLAG_SELECTION. */
MATCH void UI_MessageWaitEndInput(void) {
    u8  panel_state;
    u8  step;
    u16 window_flags;

    if ((g_PadStates[0].pressed != 0) || ((*(s32*)&g_UiWindowChannel & (FRONTEND_FLAG_ADVANCE_REQUEST | FRONTEND_FLAG_MODE_LATCH)) != 0)) {
        panel_state  = g_UiPanelTasks[0].state;
        /* FAKE: g_UiMessageStep is a one-byte scalar elsewhere; this unit reads it as an array element. */
        step         = MEM(u8, (u32)&g_UiMessageStep);
        window_flags = g_UiWindowChannel;
        panel_state += 1;
        step += 1;
        window_flags |= FRONTEND_FLAG_SELECTION;
        g_UiPanelTasks[0].state        = panel_state;
        MEM(u8, (u32)&g_UiMessageStep) = step;
        g_UiWindowChannel              = window_flags;
    }
}
