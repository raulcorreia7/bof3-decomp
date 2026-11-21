#include "engine/slus/slus.h"

/* sets bit 3 of g_UiWindowChannel and, when no request is pending, arms
 * g_UiMessageChoiceTimer and bumps g_UiMessageChoiceStep.
 */
MATCH void func_80151B08(void) {
    u16* counter = (u16*)&g_UiWindowChannel;

    *counter |= FRONTEND_FLAG_REQUEST_PENDING;
    if (g_UiMessageChoiceTimer == 0) {
        g_UiMessageChoiceTimer = 1;
        g_UiMessageChoiceStep  = g_UiMessageChoiceStep + 1;
    }
}
