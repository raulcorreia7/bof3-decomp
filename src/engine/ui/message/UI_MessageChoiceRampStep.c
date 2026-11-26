#include "engine/slus/slus.h"

/* func_80151B50 */
/* Moves the cue counter by 2 (down in choice mode 2, up otherwise) until it crosses zero, then clears the mode and the pending flag. */
MATCH void UI_MessageChoiceRampStep(void) {
    u16 value;

    if (g_UiMessageChoiceTimer == 0) {
        if (g_UiMessageChoiceMode == 2) {
            value      = D_801490C8 - 2;
            D_801490C8 = value;
            if ((value << 0x10) < 0) {
                D_801490C8            = 0;
                g_UiMessageChoiceMode = 0;
                g_UiWindowChannel &= ~FRONTEND_FLAG_REQUEST_PENDING;
            }
        } else {
            value      = D_801490C8 + 2;
            D_801490C8 = value;
            if ((value << 0x10) > 0) {
                D_801490C8            = 0;
                g_UiMessageChoiceMode = 0;
                g_UiWindowChannel &= ~FRONTEND_FLAG_REQUEST_PENDING;
            }
        }
        g_UiMessageChoiceTimer = 1;
    }
}
