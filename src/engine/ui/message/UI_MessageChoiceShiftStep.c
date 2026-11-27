#include "engine/slus/slus.h"

/* func_80151DCC */
/* Advances the second cue word by the counter and the carry byte by its high byte; once the byte is non-negative it clears it and the choice mode. */
MATCH void UI_MessageChoiceShiftStep(void) {
    u8* bb;
    s16 delta;
    u8  value;

    bb         = D_801490BB;
    value      = bb[0] + (D_801490CA >> 8);
    delta      = D_801490C8;
    bb[0]      = value;
    D_801490CA = D_801490CA + delta;
    if ((s8)value >= 0) {
        bb[0]                 = 0;
        g_UIMessageChoiceMode = 0;
    }
}
