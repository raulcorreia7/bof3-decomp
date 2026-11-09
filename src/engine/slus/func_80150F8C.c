#include "engine/slus/slus.h"

/* when the pad word is nonzero or bit 6 of the selection counter is set, clears D_801490B8 and steps the handler index g_UiWindowStep. */
MATCH void func_80150F8C(void) {
    if (g_InputPressed != 0 || (g_UiWindowChannel & FRONTEND_FLAG_ADVANCE_REQUEST) != 0) {
        D_801490B8[0] = 0;
        g_UiWindowStep++;
    }
    /* FAKE: retail reads D_8014833A as u8. */
    UI_DrawWaitMarker((g_MessageWindow.origin.x + ((*(u8*)D_8014833A) >> 1) - 0xE),
                      (D_801490C8 + (g_MessageWindow.text.y + 0xC)));
}
