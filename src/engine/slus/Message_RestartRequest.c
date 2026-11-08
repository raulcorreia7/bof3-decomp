#include "engine/slus/slus.h"

/* when the owner mode byte the message panel state is 2, marks the shared record
 * byte g_MessageStateTimer with 0x10, re-initialises the shared record through
 * Message_StartRequest, and toggles bit 2 of the shared selection word g_UiWindowChannel.
 */
/* func_8015142C */
MATCH void Message_RestartRequest(void) {
    if (g_MenuPanelTasks[0].state == 2) {
        g_MessageStateTimer[0] = 0x10;
        Message_StartRequest();
        g_UiWindowChannel ^= FRONTEND_FLAG_SELECTION;
    }
}
