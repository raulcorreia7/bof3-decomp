#include "engine/slus/slus.h"

/* On a pad press or an advance or latch request, moves the message panel and the step on and sets FRONTEND_FLAG_SELECTION. */
MATCH void UI_MessageWaitEndInput(void) {
    u8  panel_state;
    u8  step;
    u16 window_flags;

    if ((g_PadStates[0].pressed != 0) || ((*(s32*)&g_UIWindowChannel & (FRONTEND_FLAG_ADVANCE_REQUEST | FRONTEND_FLAG_MODE_LATCH)) != 0)) {
        panel_state  = g_UIPanelTasks[0].state;
        /* FAKE: g_UIMessageStep is a one-byte scalar elsewhere; this unit reads it as an array element. */
        step         = MEM(u8, (u32)&g_UIMessageStep);
        window_flags = g_UIWindowChannel;
        panel_state += 1;
        step += 1;
        window_flags |= FRONTEND_FLAG_SELECTION;
        g_UIPanelTasks[0].state        = panel_state;
        MEM(u8, (u32)&g_UIMessageStep) = step;
        g_UIWindowChannel              = window_flags;
    }
}
