#include "engine/slus/slus.h"

/* decrements g_UIMessageStateTimer and clears g_UIMessageState when it reaches zero.
 */
MATCH void UI_MessageTickChoiceTimer(void) {
    u8 value;

    value                    = g_UIMessageStateTimer[0] - 1;
    g_UIMessageStateTimer[0] = value;
    if ((value & BYTE_MASK) == 0) {
        g_UIMessageState.state = 0;
    }
}
