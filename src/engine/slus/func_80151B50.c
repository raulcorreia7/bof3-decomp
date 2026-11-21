#include "engine/slus/slus.h"

/* with no request pending (g_UiMessageChoiceTimer == 0) steps the shared cue
 * counter D_801490C8 by -2 in mode 2 and +2 otherwise, clamps it to 0 when it
 * crosses (clearing the mode g_UiMessageChoiceMode and bit 3 of g_UiWindowChannel), then arms
 * g_UiMessageChoiceTimer.
 */
MATCH void func_80151B50(void) {
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
