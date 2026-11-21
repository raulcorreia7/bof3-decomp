#include "engine/slus/slus.h"

/* shifts D_801490C8 left by four, copies g_UiMessageChoiceTimer into D_801490CA
 * and bumps g_UiMessageChoiceStep.
 */
MATCH void func_80151D8C(void) {
    u16* counter;
    u16  value;
    u8   next;

    counter               = (u16*)&D_801490C8;
    next                  = g_UiMessageChoiceStep + 1;
    value                 = *counter << 4;
    *counter              = value;
    D_801490CA            = g_UiMessageChoiceTimer;
    g_UiMessageChoiceStep = next;
}
