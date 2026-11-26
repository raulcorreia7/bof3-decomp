#include "engine/slus/slus.h"

/* func_80151D8C */
/* Shifts the cue counter left by four, copies the choice timer beside it and moves to the shift step. */
MATCH void UI_MessageChoiceShiftBegin(void) {
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
