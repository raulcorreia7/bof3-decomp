#include "engine/slus/slus.h"

/* Draws the wait marker and steps on at a pad press or an advance request. */
MATCH void UI_MessageWaitInput(void) {
    if (g_PadStates[0].pressed != 0 || (g_UiWindowChannel & FRONTEND_FLAG_ADVANCE_REQUEST) != 0) {
        D_801490B8[0] = 0;
        g_UiMessageStep++;
    }
    /* FAKE: retail reads D_8014833A as u8. */
    UI_MessageDrawWaitMarker((g_UiMessageWindow.origin.x + ((*(u8*)D_8014833A) >> 1) - 0xE), (D_801490C8 + (g_UiMessageWindow.text.y + 0xC)));
}
