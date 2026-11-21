#include "engine/slus/slus.h"

/* when the owner mode byte the message panel state is 2, marks the shared record
 * byte g_UiMessageStateTimer with 0x10, re-initialises the shared record through
 * UI_MessageStartRequest, and toggles bit 2 of the shared selection word g_UiWindowChannel.
 */
/* func_8015142C */
MATCH void UI_MessageRestartRequest(void) {
    if (g_UiPanelTasks[0].state == 2) {
        g_UiMessageStateTimer[0] = 0x10;
        UI_MessageStartRequest();
        g_UiWindowChannel ^= FRONTEND_FLAG_SELECTION;
    }
}
