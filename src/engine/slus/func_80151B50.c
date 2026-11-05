#include "engine/slus/slus.h"

/* with no request pending (D_801490AA == 0) steps the shared cue
 * counter D_801490C8 by -2 in mode 2 and +2 otherwise, clamps it to 0 when it
 * crosses (clearing the mode D_801490A2 and bit 3 of g_UiWindowChannel), then arms
 * D_801490AA.
 */
MATCH void func_80151B50(void) {
    u16 value;

    if (D_801490AA == 0) {
        if (D_801490A2 == 2) {
            value      = D_801490C8 - 2;
            D_801490C8 = value;
            if ((value << 0x10) < 0) {
                D_801490C8 = 0;
                D_801490A2 = 0;
                g_UiWindowChannel &= ~FRONTEND_FLAG_REQUEST_PENDING;
            }
        } else {
            value      = D_801490C8 + 2;
            D_801490C8 = value;
            if ((value << 0x10) > 0) {
                D_801490C8 = 0;
                D_801490A2 = 0;
                g_UiWindowChannel &= ~FRONTEND_FLAG_REQUEST_PENDING;
            }
        }
        D_801490AA = 1;
    }
}
