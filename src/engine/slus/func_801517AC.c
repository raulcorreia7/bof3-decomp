#include "engine/slus/slus.h"

/* The flag word is reached through the non-volatile MessageState view; the volatile g_UiWindowChannel spelling changes
 * the load/store sequence. */

/* when D_80148357 is 4, arms the mode byte g_MessageState with 2, clears
 * g_UiWindowStep and sets bit 7 of g_UiWindowChannel while the shared area request slot
 * g_MessageRequest is MESSAGE_NONE; otherwise it increments g_UiWindowStep.
 */
MATCH void func_801517AC(void) {
    if (D_80148357 == 4) {
        if (g_MessageRequest == MESSAGE_NONE) {
            g_MessageState.state_00 = 2;
            g_UiWindowStep          = 0;
            g_MessageState.flags_04 |= 0x80;
            return;
        }
        g_UiWindowStep += 1;
    }
}
