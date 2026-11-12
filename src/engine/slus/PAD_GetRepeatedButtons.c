#include "engine/slus/slus.h"

/* decodes repeatable pad input: a new press reloads the repeat countdown with 12 frames and snapshots the
 * held buttons, returned this frame; later, while a snapshotted button stays held, it counts down and returns the
 * held buttons again on the 3-frame repeat; 0 when nothing is due.
 */
MATCH s32 PAD_GetRepeatedButtons(s32 button_mask) {
    u16 repeat_mask;
    u16 counter;

    if (button_mask & HALF_MASK) {
        g_InputRepeatDelay   = 12;
        g_InputRepeatButtons = g_InputHeld;
        return g_InputHeld;
    }

    repeat_mask = g_InputRepeatButtons;
    if (repeat_mask & g_InputHeld) {
        counter            = g_InputRepeatDelay - 1;
        g_InputRepeatDelay = counter;
        if ((counter << 16) == 0) {
            g_InputRepeatDelay   = 3;
            g_InputRepeatButtons = g_InputHeld;
            return g_InputHeld;
        }
    }

    return 0;
}
