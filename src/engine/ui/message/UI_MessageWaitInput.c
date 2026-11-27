#include "engine/slus/slus.h"

/* Draws the wait marker and steps on at a pad press or an advance request. */
MATCH void UI_MessageWaitInput(void) {
    if (g_PadStates[0].pressed != 0 || (g_UIWindowChannel & FRONTEND_FLAG_ADVANCE_REQUEST) != 0) {
        D_801490B8[0] = 0;
        g_UIMessageStep++;
    }
    /* FAKE: retail reads D_8014833A as u8. */
    UI_MessageDrawWaitMarker((g_UIMessageWindow.origin.x + ((*(u8*)D_8014833A) >> 1) - 0xE), (D_801490C8 + (g_UIMessageWindow.text.y + 0xC)));
}
