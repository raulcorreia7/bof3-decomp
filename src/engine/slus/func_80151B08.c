#include "engine/slus/slus.h"

/* sets bit 3 of g_UiWindowChannel and. */
MATCH void func_80151B08(void) {
    u16* counter = (u16*)&g_UiWindowChannel;

    *counter |= FRONTEND_FLAG_REQUEST_PENDING;
    if (g_MessageChoiceTimer == 0) {
        g_MessageChoiceTimer = 1;
        g_MessageChoiceStep  = g_MessageChoiceStep + 1;
    }
}
