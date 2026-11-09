#include "engine/slus/slus.h"

/* advances D_801490CA by D_801490C8 and steps D_801490BB by the
 * signed high byte of the old sum, clearing both counters when the byte stays
 * non-negative.
 */
MATCH void func_80151DCC(void) {
    u8* bb;
    s16 delta;
    u8  value;

    bb         = D_801490BB;
    value      = bb[0] + (D_801490CA >> 8);
    delta      = D_801490C8;
    bb[0]      = value;
    D_801490CA = D_801490CA + delta;
    if ((s8)value >= 0) {
        bb[0]               = 0;
        g_MessageChoiceMode = 0;
    }
}
