#include "engine/slus/slus.h"

/* latches the mode bytes and sets bit 7 of g_UiWindowChannel when D_80148357 is 4.
 */
MATCH void func_80151480(void) {
    volatile u16* h;

    if (D_80148357 == 4) {
        D_80148333[0]           = 4;
        g_MessageState.state_00 = 2;
        g_UiWindowStep          = 1;
        h                       = &g_UiWindowChannel;
        *h |= FRONTEND_FLAG_MODE_LATCH;
    }
}
