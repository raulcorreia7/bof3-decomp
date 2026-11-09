#include "engine/slus/slus.h"

/* decrements g_MessageStateTimer and clears g_MessageState when it reaches zero.
 */
MATCH void UI_TickChoiceTimer(void) {
    u8 value;

    value                  = g_MessageStateTimer[0] - 1;
    g_MessageStateTimer[0] = value;
    if ((value & BYTE_MASK) == 0) {
        g_MessageState.state_00 = 0;
    }
}
