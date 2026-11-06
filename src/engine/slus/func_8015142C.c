#include "engine/slus/slus.h"

/* when the owner mode byte D_80148333 is 2, marks the shared record
 * byte g_MessageStateTimer with 0x10, re-initialises the shared record through
 * Message_StartRequest, and toggles bit 2 of the shared selection word g_UiWindowChannel.
 */
MATCH void func_8015142C(void) {
    if (D_80148333[0] == 2) {
        g_MessageStateTimer[0] = 0x10;
        Message_StartRequest();
        g_UiWindowChannel ^= FRONTEND_FLAG_SELECTION;
    }
}
