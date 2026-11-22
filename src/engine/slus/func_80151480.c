#include "engine/slus/slus.h"

/* latches the mode bytes and sets bit 7 of g_UiWindowChannel when D_80148357 is 4.
 */
MATCH void func_80151480(void) {
    volatile u16* h;

    if (g_UiPanelTasks[1].state == 4) {
        g_UiPanelTasks[0].state = 4;
        g_UiMessageState.state  = 2;
        g_UiMessageStep         = 1;
        h                       = &g_UiWindowChannel;
        *h |= FRONTEND_FLAG_MODE_LATCH;
    }
}
