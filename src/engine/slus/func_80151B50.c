#include "engine/slus/slus.h"

/* with no request pending (g_MessageChoiceTimer == 0) steps the shared cue counter D_801490C8 by -2 in mode 2 and +2 otherwise, clamps it to 0 when it crosses (clearing the mode g_MessageChoiceMode and bit 3 of g_UiWindowChannel). */
MATCH void func_80151B50(void) {
    u16 value;

    if (g_MessageChoiceTimer == 0) {
        if (g_MessageChoiceMode == 2) {
            value      = D_801490C8 - 2;
            D_801490C8 = value;
            if ((value << 0x10) < 0) {
                D_801490C8          = 0;
                g_MessageChoiceMode = 0;
                g_UiWindowChannel &= ~FRONTEND_FLAG_REQUEST_PENDING;
            }
        } else {
            value      = D_801490C8 + 2;
            D_801490C8 = value;
            if ((value << 0x10) > 0) {
                D_801490C8          = 0;
                g_MessageChoiceMode = 0;
                g_UiWindowChannel &= ~FRONTEND_FLAG_REQUEST_PENDING;
            }
        }
        g_MessageChoiceTimer = 1;
    }
}
