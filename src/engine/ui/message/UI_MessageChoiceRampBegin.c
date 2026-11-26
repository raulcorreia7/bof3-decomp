#include "engine/slus/slus.h"

/* func_80151B08 */
/* Raises the request-pending flag and, with no request pending, arms the choice timer and moves to the ramp step. */
MATCH void UI_MessageChoiceRampBegin(void) {
    u16* counter = (u16*)&g_UiWindowChannel;

    *counter |= FRONTEND_FLAG_REQUEST_PENDING;
    if (g_UiMessageChoiceTimer == 0) {
        g_UiMessageChoiceTimer = 1;
        g_UiMessageChoiceStep  = g_UiMessageChoiceStep + 1;
    }
}
