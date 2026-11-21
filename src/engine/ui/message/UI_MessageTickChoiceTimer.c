#include "engine/slus/slus.h"

/* decrements g_UiMessageStateTimer and clears g_UiMessageState when it reaches zero.
 */
MATCH void UI_MessageTickChoiceTimer(void) {
    u8 value;

    value                    = g_UiMessageStateTimer[0] - 1;
    g_UiMessageStateTimer[0] = value;
    if ((value & BYTE_MASK) == 0) {
        g_UiMessageState.state = 0;
    }
}
