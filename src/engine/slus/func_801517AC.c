#include "engine/slus/slus.h"

/* The flag word is reached through the non-volatile MessageState view; the volatile g_UiWindowChannel spelling changes
 * the load/store sequence. */

/* when D_80148357 is 4, arms the mode byte g_UiMessageState with 2, clears
 * g_UiMessageStep and sets bit 7 of g_UiWindowChannel while the shared area request slot
 * g_UiMessageRequest is MESSAGE_NONE; otherwise it increments g_UiMessageStep.
 */
MATCH void func_801517AC(void) {
    if (D_80148357 == 4) {
        if (g_UiMessageRequest == MESSAGE_NONE) {
            g_UiMessageState.state = 2;
            g_UiMessageStep        = 0;
            g_UiMessageState.flags |= 0x80;
            return;
        }
        g_UiMessageStep += 1;
    }
}
