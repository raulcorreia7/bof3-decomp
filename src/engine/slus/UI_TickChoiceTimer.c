#include "engine/slus/slus.h"

/* decrements D_801490A6 and clears D_801490A0 when it reaches zero.
 */
MATCH void UI_TickChoiceTimer(void) {
    u8 value;

    value         = D_801490A6[0] - 1;
    D_801490A6[0] = value;
    if ((value & BYTE_MASK) == 0) {
        D_801490A0.state_00 = 0;
    }
}
